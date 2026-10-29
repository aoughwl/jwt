import std/assertions
import std/syncio
import ../src/bignum

proc toHexLower(a: BigInt): string =
  const hexChars = "0123456789abcdef"
  # Byte-length just large enough (a is normalized, top limb nonzero).
  let byteLen = a.len * 4
  let bytes = bnToBytesBE(a, byteLen)
  var i = 0
  while i < bytes.len - 1 and bytes[i] == 0'u8:
    inc i
  result = ""
  var started = false
  while i < bytes.len:
    let hi = int(bytes[i] shr 4)
    let lo = int(bytes[i] and 0x0F'u8)
    if started or hi != 0:
      result.add(hexChars[hi])
      started = true
    if started or lo != 0 or i == bytes.len - 1:
      result.add(hexChars[lo])
      started = true
    inc i
  if result.len == 0: result = "0"

proc bnFromHex(s: string): BigInt =
  var bytes: seq[byte] = @[]
  var hs = s
  if hs.len mod 2 == 1: hs = "0" & hs
  var i = 0
  while i < hs.len:
    proc hv(c: char): int =
      if c >= '0' and c <= '9': ord(c) - ord('0')
      elif c >= 'a' and c <= 'f': ord(c) - ord('a') + 10
      elif c >= 'A' and c <= 'F': ord(c) - ord('A') + 10
      else: 0
    let b = uint8(hv(hs[i]) * 16 + hv(hs[i+1]))
    bytes.add(b)
    i += 2
  bnFromBytesBE(bytes)

# Cross-checked against Python's arbitrary-precision arithmetic.
let a = bnFromHex("13aaf504e4bc1e62173f87a4378c37b49c8ccff196ce3f0ad2")
let b = bnFromHex("c7748819dffb62438d1c67eea")

let prod = bnMul(a, b)
echo "prod = " & toHexLower(prod)
assert toHexLower(prod) == "f52d862a317a3746c75798bdc79876dbf6093b20b1e5e61bdf0425c0d8e29befe35d5f3ff4"
echo "bnMul: OK"

let (q, r) = bnDivMod(a, b)
echo "q = " & toHexLower(q)
echo "r = " & toHexLower(r)
assert toHexLower(r) == "bce36ba0332d56bc68f95a2a8"
assert toHexLower(q) == "193e5935c4923b1039c48ae21"
echo "bnDivMod: OK"

# Fermat's little theorem against the real NIST P-384 field prime:
# 2^(p-1) mod p == 1.
let p384 = bnFromHex(
  "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffeffffffff0000000000000000ffffffff")
let one = bnFromU32(1'u32)
let pMinus1 = bnSub(p384, one)
let fermatCheck = bnModPow(bnFromU32(2'u32), pMinus1, p384)
assert bnCmp(fermatCheck, one) == 0
echo "Fermat check against real P-384 prime: OK"

# Modular inverse sanity: a * a^-1 mod p384 == 1, for an arbitrary a.
let av = bnMod(a, p384)
let inv = bnModInv(av, p384)
let check = bnMulMod(av, inv, p384)
assert bnCmp(check, one) == 0
echo "bnModInv: OK"

echo "all bignum checks passed"
