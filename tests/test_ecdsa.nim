import std/assertions
import std/syncio
import ../src/bignum
import ../src/ecdsa
import ../src/sha2

proc hv(c: char): int =
  if c >= '0' and c <= '9': ord(c) - ord('0')
  elif c >= 'a' and c <= 'f': ord(c) - ord('a') + 10
  elif c >= 'A' and c <= 'F': ord(c) - ord('A') + 10
  else: 0

proc bytesFromHex(s: string): seq[byte] =
  result = newSeq[byte]((s.len) div 2)
  var i = 0
  while i < s.len:
    result[i div 2] = uint8(hv(s[i]) * 16 + hv(s[i+1]))
    i += 2

# --- Sanity checks on point arithmetic / group order -----------------------

let curve = p384()
let g = EcPoint(x: curve.gx, y: curve.gy, infinity: false)
assert pointOnCurve(g, curve)
echo "G is on the curve: OK"

let g2a = pointAdd(g, g, curve)
let g2b = scalarMul(bnFromU32(2'u32), g, curve)
assert bnCmp(g2a.x, g2b.x) == 0
assert bnCmp(g2a.y, g2b.y) == 0
assert pointOnCurve(g2a, curve)
echo "2G via add == 2G via scalarMul, and on curve: OK"

let g3a = pointAdd(g2a, g, curve)
let g3b = scalarMul(bnFromU32(3'u32), g, curve)
assert bnCmp(g3a.x, g3b.x) == 0
assert bnCmp(g3a.y, g3b.y) == 0
echo "3G via add == 3G via scalarMul: OK"

let g4a = pointAdd(g3a, g, curve)
let g4b = scalarMul(bnFromU32(4'u32), g, curve)
echo "4G via add: infinity=" & $g4a.infinity
echo "4G via scalarMul: infinity=" & $g4b.infinity
assert bnCmp(g4a.x, g4b.x) == 0
assert bnCmp(g4a.y, g4b.y) == 0
echo "4G via add == 4G via scalarMul: OK"

let g7a = pointAdd(pointAdd(g4a, g2a, curve), g, curve)
let g7b = scalarMul(bnFromU32(7'u32), g, curve)
assert bnCmp(g7a.x, g7b.x) == 0
assert bnCmp(g7a.y, g7b.y) == 0
echo "7G via add == 7G via scalarMul: OK"

# n*G must be the point at infinity (G has order n).
let nG = scalarMul(curve.n, g, curve)
echo "n*G infinity=" & $nG.infinity
assert nG.infinity
echo "n*G == infinity (correct group order): OK"

# --- Real NIST/Wycheproof secp384r1-SHA384 test vector ---------------------
# Source: Google Wycheproof ecdsa_secp384r1_sha384_test.json, tcId 1,
# result "valid". Message is empty; SHA-384("") independently computed
# via Python's hashlib for cross-check.
let pubKeyHex = "0429bdb76d5fa741bfd70233cb3a66cc7d44beb3b0663d92a8136650478bcefb61ef182e155a54345a5e8e5e88f064e5bc9a525ab7f764dad3dae1468c2b419f3b62b9ba917d5e8c4fb1ec47404a3fc76474b2713081be9db4c00e043ada9fc4a3"
let rHex = "32401249714e9091f05a5e109d5c1216fdc05e98614261aa0dbd9e9cd4415dee29238afbd3b103c1e40ee5c9144aee0f"
let sHex = "4326756fb2c4fd726360dd6479b5849478c7a9d054a833a58c1631c33b63c3441336ddf2c7fe0ed129aae6d4ddfeb753"
let expectedHashHex = "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b"

let emptyMsg: seq[byte] = @[]
let msgHash = sha384(emptyMsg)
var msgHashHex = ""
const hexChars = "0123456789abcdef"
for b in msgHash:
  msgHashHex.add(hexChars[int(b shr 4)])
  msgHashHex.add(hexChars[int(b and 0x0F'u8)])
assert msgHashHex == expectedHashHex
echo "SHA-384('') matches independently-computed reference: OK"

let pubKeyBytes = bytesFromHex(pubKeyHex)
let rBytes = bytesFromHex(rHex)
let sBytes = bytesFromHex(sHex)

let verified = verifyEcdsaP384(pubKeyBytes, msgHash, rBytes, sBytes)
assert verified
echo "ECDSA P-384/SHA-384 verify against real Wycheproof vector: OK (valid signature accepted)"

# Negative control: flip one bit of s and confirm it's rejected.
var badSBytes = sBytes
badSBytes[badSBytes.len - 1] = badSBytes[badSBytes.len - 1] xor 0x01'u8
let rejectedBad = verifyEcdsaP384(pubKeyBytes, msgHash, rBytes, badSBytes)
assert not rejectedBad
echo "Tampered signature correctly rejected: OK"

# Negative control: wrong message hash.
let wrongHash = sha384(bytesFromHex("00"))
let rejectedWrongMsg = verifyEcdsaP384(pubKeyBytes, wrongHash, rBytes, sBytes)
assert not rejectedWrongMsg
echo "Wrong message correctly rejected: OK"

echo "all ecdsa checks passed"
