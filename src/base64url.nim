## Base64url (RFC 4648 §5) encode/decode, built on Nimony's stdlib
## `std/base64`, whose `decode` already accepts both the standard and
## URL-safe alphabets and ignores `=` padding - so decode needs no new
## logic, just a name. Encode needs `safe=true` plus stripping the padding
## `encode` still adds (JWT's base64url is always unpadded).

import std/base64

proc encodeB64Url*(data: openArray[byte]): string =
  result = base64.encode(data, safe = true)
  while result.len > 0 and result[result.len - 1] == '=':
    result.setLen(result.len - 1)

proc decodeB64Url*(s: string): string =
  ## Returns the decoded bytes as a `string` (byte container). Accepts
  ## padded or unpadded, standard or URL-safe input.
  base64.decode(s)
