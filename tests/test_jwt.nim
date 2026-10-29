import std/assertions
import std/syncio
import ../src/jwt
import ../src/hmac
import std/json
import ../src/base64url

proc hv(c: char): int =
  if c >= '0' and c <= '9': ord(c) - ord('0')
  elif c >= 'a' and c <= 'f': ord(c) - ord('a') + 10
  elif c >= 'A' and c <= 'F': ord(c) - ord('A') + 10
  else: 0

proc bytesFromHex(s: string): seq[byte] =
  result = newSeq[byte](s.len div 2)
  var i = 0
  while i < s.len:
    result[i div 2] = uint8(hv(s[i]) * 16 + hv(s[i+1]))
    i += 2

proc claim(v: JsonNode, key: string): string =
  let f = v.member(key)
  if f.kind != JString: return ""
  f.getStr

# --- ES384 end-to-end: a real JWT minted by an independent implementation
# (Python's pycryptodome, fresh random P-384 keypair) with a genuine
# header/payload, verified here using ONLY this library's code.
let token = "eyJhbGciOiJFUzM4NCIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJ0ZXN0LXVzZXIiLCJpYXQiOjE3MDAwMDAwMDAsImV4cCI6MTg5MzQ1NjAwMH0.a8u02fuWQ5A-pY_bIEfhGokpD-qSHI0c7B27Sq6sb1im8XIYiHMDA685QUfdt5-9FDAbecaTtrB5nj3-TxrVAP_-6_7_yRMj0l_5hI9jjgsbfGtTXdaRb5hiNv7_iUWY"
let pubKeyHex = "0400795e153e34ef959e470a1a2d49289c3e2790136de3a125adf4d19349d777c815a561a756300616401dead5d04e2e8a3cdeede220e72775b72c37379766b508a38b91afc68ec3be41bccf90b849b3bb0864702144c54ee6d63b0fa48667d3ea"
let pubKey = bytesFromHex(pubKeyHex)

let result = verifyJwt(token, pubKey)
assert result.ok
echo "ES384 end-to-end JWT (minted by pycryptodome, unrelated implementation) verified: OK"

assert claim(result.payload, "sub") == "test-user"
echo "payload claim readback: OK"

# Tampering with the token (flip a payload char) must fail verification.
var tamperedToken = token
var dotPos1 = 0
for i, c in token:
  if c == '.':
    dotPos1 = i
    break
tamperedToken[dotPos1 + 5] = (if tamperedToken[dotPos1 + 5] == 'a': 'b' else: 'a')
let tamperedResult = verifyJwt(tamperedToken, pubKey)
assert not tamperedResult.ok
echo "tampered ES384 JWT correctly rejected: OK"

# Wrong public key must fail verification.
var wrongKey = pubKey
wrongKey[10] = wrongKey[10] xor 0x01'u8
let wrongKeyResult = verifyJwt(token, wrongKey)
assert not wrongKeyResult.ok
echo "wrong pubkey correctly rejected: OK"

# --- HS256 end-to-end: self-signed, but exercises the whole
# split/decode/HMAC-compare/parse pipeline for the symmetric path.
proc buildHs256Jwt(headerJson, payloadJson: string, key: openArray[byte]): string =
  proc toB(s: string): seq[byte] =
    result = newSeq[byte](s.len)
    for i, c in s: result[i] = byte(c)
  let hB64 = encodeB64Url(toB(headerJson))
  let pB64 = encodeB64Url(toB(payloadJson))
  let signingInput = hB64 & "." & pB64
  let mac = hmacSha256(key, toB(signingInput))
  var macSeq = newSeq[byte](32)
  for i in 0 ..< 32: macSeq[i] = mac[i]
  signingInput & "." & encodeB64Url(macSeq)

let hsKey = bytesFromHex("00112233445566778899aabbccddeeff00112233445566778899aabbccddee")
let hsToken = buildHs256Jwt("""{"alg":"HS256","typ":"JWT"}""", """{"role":"admin"}""", hsKey)
let hsResult = verifyJwt(hsToken, hsKey)
assert hsResult.ok
assert claim(hsResult.payload, "role") == "admin"
echo "HS256 end-to-end: OK"

let hsWrongKeyResult = verifyJwt(hsToken, bytesFromHex("ff112233445566778899aabbccddeeff00112233445566778899aabbccddee"))
assert not hsWrongKeyResult.ok
echo "HS256 wrong key correctly rejected: OK"

# --- Malformed tokens ---
let malformed = verifyJwt("not.a.valid.jwt.token", hsKey)
assert not malformed.ok
echo "malformed token (wrong segment count) correctly rejected: OK"

let unknownAlg = decodeJwtUnsafe(hsToken)
assert unknownAlg.ok  # decodeJwtUnsafe never checks the signature
echo "decodeJwtUnsafe reads claims without verifying: OK"

echo "all jwt end-to-end checks passed"
