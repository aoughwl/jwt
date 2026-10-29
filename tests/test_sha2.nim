import std/assertions
import std/syncio
import ../src/sha2

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

# FIPS 180-4 / well-known test vectors.
assert toHex(sha256(bytesOf("abc"))) ==
  "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
assert toHex(sha256(bytesOf(""))) ==
  "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
echo "sha256: OK"

assert toHex(sha384(bytesOf("abc"))) ==
  "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7"
echo "sha384: OK"

assert toHex(sha512(bytesOf("abc"))) ==
  "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f"
echo "sha512: OK"

echo "all sha2 vectors passed"
