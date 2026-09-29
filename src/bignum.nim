## Arbitrary-precision unsigned integer arithmetic, built for ECDSA's
## modular arithmetic needs (not general-purpose performance). Nimony's
## stdlib has no bigint module, so this is from scratch.
##
## Representation: `seq[uint32]` limbs, little-endian (limb 0 = least
## significant 32 bits), always normalized (no high zero limbs except a
## single `[0]` for the value zero).
##
## Division/modulo use straightforward binary long division (shift one
## bit at a time, compare, conditionally subtract) rather than Knuth's
## algorithm D - O(bits^2) instead of near-linear, but this is only used
## for one-off signature verification, not a hot path, and it is far
## easier to get correct, which matters more here.

type BigInt* = seq[uint32]

proc bnNormalize(a: var BigInt) =
  while a.len > 1 and a[a.len - 1] == 0'u32:
    a.setLen(a.len - 1)
  if a.len == 0:
    a.add(0'u32)

proc bnZero*(): BigInt = @[0'u32]

proc bnFromU32*(v: uint32): BigInt = @[v]

proc bnIsZero*(a: BigInt): bool =
  a.len == 1 and a[0] == 0'u32

proc bnFromBytesBE*(bytes: openArray[byte]): BigInt =
  ## Parses a big-endian byte string (e.g. a curve coordinate or a hash
  ## digest) into a BigInt.
  if bytes.len == 0:
    return bnZero()
  let nLimbs = (bytes.len + 3) div 4
  result = newSeq[uint32](nLimbs)
  var bi = bytes.len - 1
  var limb = 0
  var shift = 0
  while bi >= 0:
    result[limb] = result[limb] or (uint32(bytes[bi]) shl uint32(shift))
    shift += 8
    if shift == 32:
      shift = 0
      inc limb
    dec bi
  bnNormalize(result)

proc bnToBytesBE*(a: BigInt, byteLen: int): seq[byte] =
  ## Encodes as a fixed-width big-endian byte string, left-padded with
  ## zeros (as ECDSA/SEC1 field elements require).
  result = newSeq[byte](byteLen)
  for i in 0 ..< byteLen:
    let bitPos = i * 8
    let limbIdx = bitPos div 32
    let shift = bitPos mod 32
    var b = 0'u8
    if limbIdx < a.len:
      b = uint8((a[limbIdx] shr uint32(shift)) and 0xFF'u32)
    result[byteLen - 1 - i] = b

proc bnCmp*(a, b: BigInt): int =
  if a.len != b.len:
    return (if a.len < b.len: -1 else: 1)
  var i = a.len - 1
  while i >= 0:
    if a[i] != b[i]:
      return (if a[i] < b[i]: -1 else: 1)
    dec i
  0

proc bnAdd*(a, b: BigInt): BigInt =
  let n = max(a.len, b.len)
  result = newSeq[uint32](n + 1)
  var carry = 0'u64
  for i in 0 ..< n:
    let av = if i < a.len: uint64(a[i]) else: 0'u64
    let bv = if i < b.len: uint64(b[i]) else: 0'u64
    let s = av + bv + carry
    result[i] = uint32(s and 0xFFFFFFFF'u64)
    carry = s shr 32'u64
  result[n] = uint32(carry)
  bnNormalize(result)

proc bnSub*(a, b: BigInt): BigInt =
  ## Requires a >= b. (Verification code below never calls this otherwise.)
  result = newSeq[uint32](a.len)
  var borrow = 0'i64
  for i in 0 ..< a.len:
    let bv = if i < b.len: int64(b[i]) else: 0'i64
    var d = int64(a[i]) - bv - borrow
    if d < 0:
      d += 0x100000000'i64
      borrow = 1
    else:
      borrow = 0
    result[i] = uint32(d)
  bnNormalize(result)

proc bnShl1*(a: BigInt): BigInt =
  ## a * 2.
  result = newSeq[uint32](a.len + 1)
  var carry = 0'u32
  for i in 0 ..< a.len:
    let v = a[i]
    result[i] = (v shl 1'u32) or carry
    carry = v shr 31'u32
  result[a.len] = carry
  bnNormalize(result)

proc bnShr1*(a: BigInt): BigInt =
  ## a div 2.
  result = newSeq[uint32](a.len)
  var carry = 0'u32
  var i = a.len - 1
  while i >= 0:
    result[i] = (a[i] shr 1'u32) or carry
    carry = (a[i] and 1'u32) shl 31'u32
    dec i
  bnNormalize(result)

proc bnBitLen*(a: BigInt): int =
  if bnIsZero(a): return 0
  var top = a[a.len - 1]
  result = (a.len - 1) * 32
  while top != 0'u32:
    inc result
    top = top shr 1'u32

proc bnTestBit*(a: BigInt, bit: int): bool =
  let limbIdx = bit div 32
  if limbIdx >= a.len: return false
  ((a[limbIdx] shr uint32(bit mod 32)) and 1'u32) == 1'u32

proc bnMul*(a, b: BigInt): BigInt =
  if bnIsZero(a) or bnIsZero(b):
    return bnZero()
  result = newSeq[uint32](a.len + b.len)
  for i in 0 ..< a.len:
    var carry = 0'u64
    let av = uint64(a[i])
    for j in 0 ..< b.len:
      let cur = uint64(result[i+j]) + av * uint64(b[j]) + carry
      result[i+j] = uint32(cur and 0xFFFFFFFF'u64)
      carry = cur shr 32'u64
    var k = i + b.len
    while carry != 0'u64:
      let cur = uint64(result[k]) + carry
      result[k] = uint32(cur and 0xFFFFFFFF'u64)
      carry = cur shr 32'u64
      inc k
  bnNormalize(result)

proc bnDivMod*(a, b: BigInt): (BigInt, BigInt) =
  ## Binary long division: returns (quotient, remainder). `b` must be
  ## nonzero (unchecked - all call sites here divide by a curve prime or
  ## order, which is a compile-time-known nonzero constant).
  var rem = bnZero()
  var quot = newSeq[uint32]((a.len))
  bnNormalize(quot)
  let nbits = bnBitLen(a)
  var i = nbits - 1
  while i >= 0:
    rem = bnShl1(rem)
    if bnTestBit(a, i):
      rem[0] = rem[0] or 1'u32
    if bnCmp(rem, b) >= 0:
      rem = bnSub(rem, b)
      # Set bit i of quot.
      let limbIdx = i div 32
      while quot.len <= limbIdx:
        quot.add(0'u32)
      quot[limbIdx] = quot[limbIdx] or (1'u32 shl uint32(i mod 32))
    dec i
  bnNormalize(quot)
  (quot, rem)

proc bnMod*(a, m: BigInt): BigInt =
  bnDivMod(a, m)[1]

proc bnAddMod*(a, b, m: BigInt): BigInt =
  ## Assumes a, b already < m.
  let s = bnAdd(a, b)
  if bnCmp(s, m) >= 0: bnSub(s, m) else: s

proc bnSubMod*(a, b, m: BigInt): BigInt =
  ## Assumes a, b already < m.
  if bnCmp(a, b) >= 0: bnSub(a, b)
  else: bnSub(bnAdd(a, m), b)

proc bnMulMod*(a, b, m: BigInt): BigInt =
  bnMod(bnMul(a, b), m)

proc bnModPow*(base, exp, modulus: BigInt): BigInt =
  ## Square-and-multiply. `base` need not be pre-reduced.
  result = bnFromU32(1'u32)
  var b = bnMod(base, modulus)
  let nbits = bnBitLen(exp)
  for i in 0 ..< nbits:
    if bnTestBit(exp, i):
      result = bnMulMod(result, b, modulus)
    b = bnMulMod(b, b, modulus)

proc bnModInv*(a, m: BigInt): BigInt =
  ## Modular inverse via Fermat's little theorem: a^(m-2) mod m.
  ## Requires m prime - true for every modulus this library uses it with
  ## (a NIST curve's field prime p, or its order n).
  let two = bnFromU32(2'u32)
  let mMinus2 = bnSub(m, two)
  bnModPow(a, mMinus2, m)
