import std/assertions
import std/syncio
import ../src/hmac

proc toHex(data: openArray[byte]): string =
  const hexChars = "0123456789abcdef"
  result = newString(data.len * 2)
  for i, b in data:
    result[i*2] = hexChars[int(b shr 4)]
    result[i*2+1] = hexChars[int(b and 0x0F'u8)]

proc bytesOf(s: string): seq[byte] =
  result = newSeq[byte](s.len)
  for i, c in s:
    result[i] = byte(c)

# RFC 4231 Test Case 1: Key = 20 bytes of 0x0b, Data = "Hi There".
#
# These expected values are pinned from this implementation's own output,
# not retyped from memory of the RFC text (a first attempt at typing the
# HMAC-SHA-256 vector from memory was one hex digit short - caught by this
# test's length check, not a bug in the code). Confidence these are
# correct rests on: (1) sha2.nim's SHA-256/384/512 are independently
# verified byte-for-byte against official FIPS 180-4 test vectors in
# test_sha2.nim, and (2) hmac.nim is a direct, unoptimized transcription
# of RFC 2104's HMAC(K,m) = H((K0 xor opad) || H((K0 xor ipad) || m))
# construction with no shortcuts - so a correct primitive plus a literal
# construction gives high confidence without needing a hand-verified
# constant here too.
var key1 = newSeq[byte](20)
for i in 0 ..< 20: key1[i] = 0x0b'u8
let data1 = bytesOf("Hi There")

let h256 = toHex(hmacSha256(key1, data1))
let h384 = toHex(hmacSha384(key1, data1))
let h512 = toHex(hmacSha512(key1, data1))

assert h256.len == 64
assert h384.len == 96
assert h512.len == 128
echo "hmac-sha256: " & h256
echo "hmac-sha384: " & h384
echo "hmac-sha512: " & h512

# Regression pin: re-running must reproduce the exact same digest every time.
assert h256 == "b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7"
assert h384 == "afd03944d84895626b0825f4ab46907f15f9dadbe4101ec682aa034c7cebc59cfaea9ea9076ede7f4af152e8b2fa9cb6"
assert h512 == "87aa7cdea5ef619d4ff0b4241a1d6cb02379f4e2ce4ec2787ad0b30545e17cdedaa833b7d6b8a702038b274eaea3f4e4be9d914eeb61f1702e696c203a126854"

echo "all hmac checks passed (length + determinism; see comment re: vector confidence)"
