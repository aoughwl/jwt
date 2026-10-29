## Public entry point: parse and verify a compact JWT
## (base64url(header) "." base64url(payload) "." base64url(signature)).
##
## Supports HS256/384/512 (HMAC) and ES384 (ECDSA P-384/SHA-384, the
## algorithm this library was originally built for - Minecraft Bedrock's
## login-chain JWTs). RS* (RSA) is not implemented; see README.md.

import base64url, minijson, hmac, sha2, ecdsa, bignum

type
  JwtVerifyResult* = object
    ok*: bool
    header*: nil JsonValue
    payload*: nil JsonValue
    error*: string

proc failResult(msg: string): JwtVerifyResult =
  JwtVerifyResult(ok: false, header: nil, payload: nil, error: msg)

proc splitToken(token: string): (bool, string, string, string) =
  var parts: seq[string] = @[]
  var cur = ""
  for c in token:
    if c == '.':
      parts.add(cur)
      cur = ""
    else:
      cur.add(c)
  parts.add(cur)
  if parts.len != 3:
    return (false, "", "", "")
  (true, parts[0], parts[1], parts[2])

proc bytesToSeq(s: string): seq[byte] =
  result = newSeq[byte](s.len)
  for i, c in s:
    result[i] = byte(c)

proc getAlg(header: nil JsonValue): string =
  if header == nil: return ""
  let a = objGet(header, "alg")
  if a == nil or a.kind != jkString: return ""
  a.strVal

proc verifyJwt*(token: string, key: openArray[byte]): JwtVerifyResult =
  ## Verifies `token` against `key`, dispatching on the header's `alg`.
  ## For HS*, `key` is the shared HMAC secret. For ES384, `key` must be
  ## the 97-byte SEC1-uncompressed P-384 public key (0x04 || X || Y).
  let (ok, headerB64, payloadB64, sigB64) = splitToken(token)
  if not ok:
    return failResult("malformed token: expected 3 dot-separated segments")

  let headerJson = decodeB64Url(headerB64)
  let payloadJson = decodeB64Url(payloadB64)
  let sig = decodeB64Url(sigB64)

  let headerParse = parseJson(headerJson)
  if not headerParse.ok or headerParse.value == nil:
    return failResult("invalid header JSON: " & headerParse.error)
  let header = headerParse.value

  let payloadParse = parseJson(payloadJson)
  if not payloadParse.ok or payloadParse.value == nil:
    return failResult("invalid payload JSON: " & payloadParse.error)
  let payload = payloadParse.value

  let alg = getAlg(header)
  let signingInput = headerB64 & "." & payloadB64
  let signingInputBytes = bytesToSeq(signingInput)
  let sigBytes = bytesToSeq(sig)

  var verified = false
  case alg
  of "HS256":
    let mac = hmacSha256(key, signingInputBytes)
    if sigBytes.len == 32:
      verified = true
      for i in 0 ..< 32:
        if mac[i] != sigBytes[i]: verified = false
  of "HS384":
    let mac = hmacSha384(key, signingInputBytes)
    if sigBytes.len == 48:
      verified = true
      for i in 0 ..< 48:
        if mac[i] != sigBytes[i]: verified = false
  of "HS512":
    let mac = hmacSha512(key, signingInputBytes)
    if sigBytes.len == 64:
      verified = true
      for i in 0 ..< 64:
        if mac[i] != sigBytes[i]: verified = false
  of "ES384":
    # JOSE ES384 signature encoding is the raw concatenation r(48) || s(48),
    # not DER (unlike, say, a certificate's signature field).
    if sigBytes.len != 96:
      return failResult("ES384 signature must be 96 bytes (r||s), got " & $sigBytes.len)
    var rBytes = newSeq[byte](48)
    var sBytes = newSeq[byte](48)
    for i in 0 ..< 48:
      rBytes[i] = sigBytes[i]
      sBytes[i] = sigBytes[48 + i]
    let hash = sha384(signingInputBytes)
    verified = verifyEcdsaP384(key, hash, rBytes, sBytes)
  else:
    return failResult("unsupported alg: " & alg & " (only HS256/384/512, ES384 implemented - see README.md)")

  if not verified:
    return failResult("signature verification failed")

  JwtVerifyResult(ok: true, header: header, payload: payload, error: "")

proc decodeJwtUnsafe*(token: string): JwtVerifyResult =
  ## Parses header/payload WITHOUT verifying the signature. Never trust
  ## claims from this for anything security-relevant - it exists for
  ## inspecting/debugging a token, or for the one legitimate
  ## "read-before-verify" case: pulling the `alg`/key-hint out of the
  ## header to decide which key material to verify with next.
  let (ok, headerB64, payloadB64, _) = splitToken(token)
  if not ok:
    return failResult("malformed token: expected 3 dot-separated segments")
  let headerParse = parseJson(decodeB64Url(headerB64))
  let payloadParse = parseJson(decodeB64Url(payloadB64))
  if not headerParse.ok or headerParse.value == nil:
    return failResult("invalid header JSON: " & headerParse.error)
  if not payloadParse.ok or payloadParse.value == nil:
    return failResult("invalid payload JSON: " & payloadParse.error)
  JwtVerifyResult(ok: true, header: headerParse.value, payload: payloadParse.value, error: "")
