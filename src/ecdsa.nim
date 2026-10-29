## ECDSA verification over the NIST P-384 curve (secp384r1), the curve
## Minecraft Bedrock's login-chain JWTs sign with (ES384). Point
## arithmetic in affine coordinates over `bignum.nim`'s BigInt.
##
## Only verification is implemented (the actual need: checking a chain
## of server-issued JWTs), not signing. Curve parameters are the public
## NIST SP 800-186 constants for P-384.

import bignum

const FieldByteLen = 48

type
  EcPoint* = object
    x*, y*: BigInt
    infinity*: bool

  P384Curve* = object
    p*: BigInt   # field prime
    a*: BigInt   # curve coefficient a (≡ p-3)
    b*: BigInt   # curve coefficient b
    gx*, gy*: BigInt
    n*: BigInt   # order of G

proc hexToBigInt(s: string): BigInt =
  var bytes: seq[byte] = @[]
  var i = 0
  while i < s.len:
    proc hv(c: char): int =
      if c >= '0' and c <= '9': ord(c) - ord('0')
      elif c >= 'a' and c <= 'f': ord(c) - ord('a') + 10
      elif c >= 'A' and c <= 'F': ord(c) - ord('A') + 10
      else: 0
    bytes.add(uint8(hv(s[i]) * 16 + hv(s[i+1])))
    i += 2
  bnFromBytesBE(bytes)

proc p384*(): P384Curve {.noinit.} =
  ## NIST SP 800-186 secp384r1 domain parameters.
  result.p = hexToBigInt(
    "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffeffffffff0000000000000000ffffffff")
  result.a = bnSub(result.p, bnFromU32(3'u32))
  result.b = hexToBigInt(
    "b3312fa7e23ee7e4988e056be3f82d19181d9c6efe8141120314088f5013875ac656398d8a2ed19d2a85c8edd3ec2aef")
  result.gx = hexToBigInt(
    "aa87ca22be8b05378eb1c71ef320ad746e1d3b628ba79b9859f741e082542a385502f25dbf55296c3a545e3872760ab7")
  result.gy = hexToBigInt(
    "3617de4a96262c6f5d9e98bf9292dc29f8f41dbd289a147ce9da3113b5f0b8c00a60b1ce1d7e819d7a431d7c90ea0e5f")
  result.n = hexToBigInt(
    "ffffffffffffffffffffffffffffffffffffffffffffffffc7634d81f4372ddf581a0db248b0a77aecec196accc52973")

proc infinityPoint(): EcPoint =
  EcPoint(x: bnZero(), y: bnZero(), infinity: true)

# --- Jacobian projective coordinates ----------------------------------------
#
# Affine (x,y) <-> Jacobian (X,Y,Z) via x = X/Z^2, y = Y/Z^3. Every point
# add/double in these coordinates costs a handful of multiplies and NO
# modular inverse - `bnModInv` is a full Fermat exponentiation
# (~384 squarings), so calling it inside every one of scalarMul's ~384
# doublings (as a first affine-coordinates version of this file did) is a
# combinatorial blowup that made even one scalarMul take unreasonably
# long. Jacobian coordinates defer the single needed inversion to the end
# of `scalarMul`, cutting the modInv count from O(bits) to O(1) per call.

type JacPoint = object
  x, y, z: BigInt
  infinity: bool

proc toJacobian(pt: EcPoint): JacPoint =
  if pt.infinity:
    JacPoint(x: bnFromU32(1'u32), y: bnFromU32(1'u32), z: bnZero(), infinity: true)
  else:
    JacPoint(x: pt.x, y: pt.y, z: bnFromU32(1'u32), infinity: false)

proc toAffine(pt: JacPoint, curve: P384Curve): EcPoint =
  if pt.infinity or bnIsZero(pt.z):
    return infinityPoint()
  let zInv = bnModInv(pt.z, curve.p)
  let zInv2 = bnMulMod(zInv, zInv, curve.p)
  let zInv3 = bnMulMod(zInv2, zInv, curve.p)
  EcPoint(x: bnMulMod(pt.x, zInv2, curve.p), y: bnMulMod(pt.y, zInv3, curve.p), infinity: false)

proc jacDouble(pt: JacPoint, curve: P384Curve): JacPoint =
  ## Standard Jacobian doubling for a = -3 curves (true for every NIST
  ## prime curve, including P-384): cheaper than the generic-`a` formula.
  if pt.infinity or bnIsZero(pt.y):
    return JacPoint(x: bnFromU32(1'u32), y: bnFromU32(1'u32), z: bnZero(), infinity: true)
  let p = curve.p
  let ySq = bnMulMod(pt.y, pt.y, p)
  let s = bnMulMod(bnFromU32(4'u32), bnMulMod(pt.x, ySq, p), p)
  let zSq = bnMulMod(pt.z, pt.z, p)
  let xMinusZSq = bnSubMod(pt.x, zSq, p)
  let xPlusZSq = bnAddMod(pt.x, zSq, p)
  let m = bnMulMod(bnFromU32(3'u32), bnMulMod(xMinusZSq, xPlusZSq, p), p)
  let x3 = bnSubMod(bnMulMod(m, m, p), bnAddMod(s, s, p), p)
  let ySqSq = bnMulMod(ySq, ySq, p)
  let y3 = bnSubMod(bnMulMod(m, bnSubMod(s, x3, p), p), bnMulMod(bnFromU32(8'u32), ySqSq, p), p)
  let yz = bnMulMod(pt.y, pt.z, p)
  let z3 = bnAddMod(yz, yz, p)
  JacPoint(x: x3, y: y3, z: z3, infinity: false)

proc jacAdd(p1, p2: JacPoint, curve: P384Curve): JacPoint =
  if p1.infinity: return p2
  if p2.infinity: return p1
  let p = curve.p
  let z1z1 = bnMulMod(p1.z, p1.z, p)
  let z2z2 = bnMulMod(p2.z, p2.z, p)
  let u1 = bnMulMod(p1.x, z2z2, p)
  let u2 = bnMulMod(p2.x, z1z1, p)
  let s1 = bnMulMod(p1.y, bnMulMod(p2.z, z2z2, p), p)
  let s2 = bnMulMod(p2.y, bnMulMod(p1.z, z1z1, p), p)
  if bnCmp(u1, u2) == 0:
    if bnCmp(s1, s2) != 0:
      return JacPoint(x: bnFromU32(1'u32), y: bnFromU32(1'u32), z: bnZero(), infinity: true)
    return jacDouble(p1, curve)
  let h = bnSubMod(u2, u1, p)
  let i = bnMulMod(bnFromU32(4'u32), bnMulMod(h, h, p), p)
  let j = bnMulMod(h, i, p)
  let r = bnAddMod(bnSubMod(s2, s1, p), bnSubMod(s2, s1, p), p)
  let v = bnMulMod(u1, i, p)
  let x3 = bnSubMod(bnSubMod(bnMulMod(r, r, p), j, p), bnAddMod(v, v, p), p)
  let y3 = bnSubMod(bnMulMod(r, bnSubMod(v, x3, p), p), bnAddMod(bnMulMod(s1, j, p), bnMulMod(s1, j, p), p), p)
  let zSum = bnAddMod(p1.z, p2.z, p)
  let z3 = bnMulMod(bnSubMod(bnMulMod(zSum, zSum, p), bnAddMod(z1z1, z2z2, p), p), h, p)
  JacPoint(x: x3, y: y3, z: z3, infinity: false)

proc pointAdd*(p1, p2: EcPoint, curve: P384Curve): EcPoint =
  toAffine(jacAdd(toJacobian(p1), toJacobian(p2), curve), curve)

proc scalarMul*(k: BigInt, pt: EcPoint, curve: P384Curve): EcPoint =
  ## Double-and-add, MSB to LSB, entirely in Jacobian coordinates -
  ## converts to affine only once, at the end.
  var acc = JacPoint(x: bnFromU32(1'u32), y: bnFromU32(1'u32), z: bnZero(), infinity: true)
  let base = toJacobian(pt)
  let nbits = bnBitLen(k)
  var i = nbits - 1
  while i >= 0:
    acc = jacDouble(acc, curve)
    if bnTestBit(k, i):
      acc = jacAdd(acc, base, curve)
    dec i
  toAffine(acc, curve)

proc pointOnCurve*(pt: EcPoint, curve: P384Curve): bool =
  ## y^2 == x^3 + a*x + b (mod p).
  if pt.infinity: return false
  let lhs = bnMulMod(pt.y, pt.y, curve.p)
  let x2 = bnMulMod(pt.x, pt.x, curve.p)
  let x3 = bnMulMod(x2, pt.x, curve.p)
  let ax = bnMulMod(bnMod(curve.a, curve.p), pt.x, curve.p)
  let rhs = bnAddMod(bnAddMod(x3, ax, curve.p), bnMod(curve.b, curve.p), curve.p)
  bnCmp(lhs, rhs) == 0

proc pubKeyFromUncompressed*(bytes: openArray[byte]): (bool, EcPoint) =
  ## Parses a SEC1 uncompressed point encoding: 0x04 || X(48) || Y(48).
  if bytes.len != 1 + 2 * FieldByteLen or bytes[0] != 0x04'u8:
    return (false, infinityPoint())
  var xBytes = newSeq[byte](FieldByteLen)
  var yBytes = newSeq[byte](FieldByteLen)
  for i in 0 ..< FieldByteLen:
    xBytes[i] = bytes[1 + i]
    yBytes[i] = bytes[1 + FieldByteLen + i]
  let pt = EcPoint(x: bnFromBytesBE(xBytes), y: bnFromBytesBE(yBytes), infinity: false)
  (true, pt)

proc ecdsaVerify*(pubKey: EcPoint, hash: openArray[byte], r, s: BigInt): bool =
  ## FIPS 186-5 ECDSA signature verification.
  let curve = p384()

  if not pointOnCurve(pubKey, curve):
    return false

  let one = bnFromU32(1'u32)
  let nMinus1 = bnSub(curve.n, one)
  if bnIsZero(r) or bnCmp(r, nMinus1) > 0: return false
  if bnIsZero(s) or bnCmp(s, nMinus1) > 0: return false

  let z = bnFromBytesBE(hash)
  let w = bnModInv(s, curve.n)
  let u1 = bnMulMod(z, w, curve.n)
  let u2 = bnMulMod(r, w, curve.n)

  let g = EcPoint(x: curve.gx, y: curve.gy, infinity: false)
  let p1 = scalarMul(u1, g, curve)
  let p2 = scalarMul(u2, pubKey, curve)
  let sum = pointAdd(p1, p2, curve)
  if sum.infinity: return false

  let x1modn = bnMod(sum.x, curve.n)
  bnCmp(x1modn, r) == 0

proc verifyEcdsaP384*(pubKeyUncompressed: openArray[byte], hash: openArray[byte],
                       rBytes, sBytes: openArray[byte]): bool =
  ## Convenience entry point: takes SEC1 uncompressed pubkey bytes and
  ## big-endian r/s byte strings (as a JWT's raw ES384 signature splits
  ## into, or as DER-decoded integers).
  let (ok, pubKey) = pubKeyFromUncompressed(pubKeyUncompressed)
  if not ok: return false
  let r = bnFromBytesBE(rBytes)
  let s = bnFromBytesBE(sBytes)
  ecdsaVerify(pubKey, hash, r, s)
