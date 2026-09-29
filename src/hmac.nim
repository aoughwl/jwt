## HMAC (RFC 2104) for SHA-256/384/512.
## Verified against RFC 4231 test vectors in tests/test_hmac.nim.
##
## Not factored through a generic/higher-order `hashFn` parameter: passing
## a proc value (even a named top-level one marked `{.closure.}`) into a
## generic helper here crashed the Nimony compiler with an internal
## AssertionDefect in `lambdalifting.nim` (`env.s != SymId(0)`) instead of
## a diagnostic. Three direct, near-identical implementations avoid it.

import sha2

const
  Sha256BlockSize = 64
  Sha384512BlockSize = 128

proc hmacSha256*(key, msg: openArray[byte]): array[32, byte] {.noinit.} =
  var k0 = newSeq[byte](Sha256BlockSize)
  if key.len > Sha256BlockSize:
    let hk = sha256(key)
    for i in 0 ..< 32: k0[i] = hk[i]
  else:
    for i in 0 ..< key.len: k0[i] = key[i]

  var ipad = newSeq[byte](Sha256BlockSize)
  var opad = newSeq[byte](Sha256BlockSize)
  for i in 0 ..< Sha256BlockSize:
    ipad[i] = k0[i] xor 0x36'u8
    opad[i] = k0[i] xor 0x5C'u8

  var inner = newSeq[byte](Sha256BlockSize + msg.len)
  for i in 0 ..< Sha256BlockSize: inner[i] = ipad[i]
  for i in 0 ..< msg.len: inner[Sha256BlockSize + i] = msg[i]
  let innerHash = sha256(inner)

  var outer = newSeq[byte](Sha256BlockSize + 32)
  for i in 0 ..< Sha256BlockSize: outer[i] = opad[i]
  for i in 0 ..< 32: outer[Sha256BlockSize + i] = innerHash[i]
  sha256(outer)

proc hmacSha384*(key, msg: openArray[byte]): array[48, byte] {.noinit.} =
  var k0 = newSeq[byte](Sha384512BlockSize)
  if key.len > Sha384512BlockSize:
    let hk = sha384(key)
    for i in 0 ..< 48: k0[i] = hk[i]
  else:
    for i in 0 ..< key.len: k0[i] = key[i]

  var ipad = newSeq[byte](Sha384512BlockSize)
  var opad = newSeq[byte](Sha384512BlockSize)
  for i in 0 ..< Sha384512BlockSize:
    ipad[i] = k0[i] xor 0x36'u8
    opad[i] = k0[i] xor 0x5C'u8

  var inner = newSeq[byte](Sha384512BlockSize + msg.len)
  for i in 0 ..< Sha384512BlockSize: inner[i] = ipad[i]
  for i in 0 ..< msg.len: inner[Sha384512BlockSize + i] = msg[i]
  let innerHash = sha384(inner)

  var outer = newSeq[byte](Sha384512BlockSize + 48)
  for i in 0 ..< Sha384512BlockSize: outer[i] = opad[i]
  for i in 0 ..< 48: outer[Sha384512BlockSize + i] = innerHash[i]
  sha384(outer)

proc hmacSha512*(key, msg: openArray[byte]): array[64, byte] {.noinit.} =
  var k0 = newSeq[byte](Sha384512BlockSize)
  if key.len > Sha384512BlockSize:
    let hk = sha512(key)
    for i in 0 ..< 64: k0[i] = hk[i]
  else:
    for i in 0 ..< key.len: k0[i] = key[i]

  var ipad = newSeq[byte](Sha384512BlockSize)
  var opad = newSeq[byte](Sha384512BlockSize)
  for i in 0 ..< Sha384512BlockSize:
    ipad[i] = k0[i] xor 0x36'u8
    opad[i] = k0[i] xor 0x5C'u8

  var inner = newSeq[byte](Sha384512BlockSize + msg.len)
  for i in 0 ..< Sha384512BlockSize: inner[i] = ipad[i]
  for i in 0 ..< msg.len: inner[Sha384512BlockSize + i] = msg[i]
  let innerHash = sha512(inner)

  var outer = newSeq[byte](Sha384512BlockSize + 64)
  for i in 0 ..< Sha384512BlockSize: outer[i] = opad[i]
  for i in 0 ..< 64: outer[Sha384512BlockSize + i] = innerHash[i]
  sha512(outer)
