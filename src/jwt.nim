## Public entry point: parse and verify a compact JWT
## (base64url(header) "." base64url(payload) "." base64url(signature)).
##
## Supports HS256/384/512 (HMAC) and ES384 (ECDSA P-384/SHA-384, the
## algorithm this library was originally built for - Minecraft Bedrock's
## login-chain JWTs). RS* (RSA) is not implemented; see README.md.

import std/json
import base64url, hmac, sha2, ecdsa, bignum

type
  JwtVerifyResult* = object
    ok*: bool
    header*: JsonNode    ## JNull-kind node unless `ok`
    payload*: JsonNode   ## JNull-kind node unless `ok`
    error*: string

proc failResult(msg: string): JwtVerifyResult =
  JwtVerifyResult(ok: false, header: JsonNode(), payload: JsonNode(), error: msg)

proc member*(n: JsonNode, key: string): JsonNode =
  ## Object member lookup: a JNull-kind node when `n` is not an object or has no `key`.
  result = JsonNode()
  if n.kind != JObject: return
  for k, v in pairs(n):
    if k == key:
      result = v
      return

proc parseSegment(json: string, node: var JsonNode): string =
  ## Parses one decoded JWT segment. Returns "" on success (node is then the
  ## document root, which stays alive after the tree goes out of scope) or the
  ## parser's diagnostic.
  var tree = parseJson(json)
  let err = tree.errorMsg
  if err.len > 0: return err
  node = tree.root
  ""

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

proc getAlg(header: JsonNode): string =
  let a = header.member("alg")
  if a.kind != JString: return ""
  a.getStr

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

  var header = JsonNode()
  let headerErr = parseSegment(headerJson, header)
  if headerErr.len > 0:
    return failResult("invalid header JSON: " & headerErr)

  var payload = JsonNode()
  let payloadErr = parseSegment(payloadJson, payload)
  if payloadErr.len > 0:
    return failResult("invalid payload JSON: " & payloadErr)

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
  var header = JsonNode()
  let headerErr = parseSegment(decodeB64Url(headerB64), header)
  if headerErr.len > 0:
    return failResult("invalid header JSON: " & headerErr)
  var payload = JsonNode()
  let payloadErr = parseSegment(decodeB64Url(payloadB64), payload)
  if payloadErr.len > 0:
    return failResult("invalid payload JSON: " & payloadErr)
  JwtVerifyResult(ok: true, header: header, payload: payload, error: "")
