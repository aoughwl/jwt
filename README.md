# jwt

A JWT (JSON Web Token) library for [Nimony](https://github.com/aoughwl/nimony),
written from scratch because Nimony's stdlib lacks the crypto pieces JWT
needs: no SHA-256/384/512 (only SHA-1), no HMAC, no big-integer
arithmetic, and no elliptic-curve crypto. JSON parsing uses Nimony's own
`std/json`.

Built originally to unblock the Nimony port of
[Pumpkin](https://github.com/Pumpkin-MC/Pumpkin) (a Minecraft server, see
the sibling repo `minecraft-server`), which needs to verify Minecraft
Bedrock Edition's JWT-based login chain - signed with ES384 (ECDSA over
NIST P-384, SHA-384). That's the algorithm this library treats as its
primary target, but everything here is written as a general-purpose
library, not a one-off.

## What's implemented and verified

| Piece | File | Verified against |
|---|---|---|
| Base64url encode/decode | `src/base64url.nim` | Thin wrapper over `std/base64` (already handles both alphabets + padding) |
| SHA-256/384/512 | `src/sha2.nim` | FIPS 180-4 test vectors (`"abc"`, `""`) |
| HMAC-SHA256/384/512 | `src/hmac.nim` | RFC 4231 test case 1 (built on the verified SHA-2 primitives) |
| Arbitrary-precision bignum | `src/bignum.nim` | Cross-checked against Python; Fermat's little theorem against the real P-384 field prime; modular-inverse round-trip |
| ECDSA verify, NIST P-384 (ES384) | `src/ecdsa.nim` | A **real** secp384r1/SHA-384 test vector from Google's [Wycheproof](https://github.com/google/wycheproof) project, cross-checked against Python's `pycryptodome` (an independent implementation) |
| `verifyJwt()` public API | `src/jwt.nim` | **End-to-end**: a real ES384 JWT minted entirely by `pycryptodome` (unrelated implementation, fresh random keypair) verifies successfully using only this library's code; tamper/wrong-key/wrong-message are all correctly rejected. HS256 self-sign-and-verify round-trip also covered. |

Run any test with:
```
nimony c -r tests/test_<name>.nim
```
(from PowerShell - Bash/Git Bash can silently swallow C compiler errors
on the compile-and-run path; `nimony check <file>` for a type-check-only
pass works fine from either shell.)

### A note on how the ECDSA vectors were sourced

I do not trust hand-typed hex constants recalled from memory for
anything cryptographic in this repo - a first attempt at typing the
curve order `n` from memory was two hex digits short, caught only by an
`n*G == point at infinity` group-order check, not by smaller sanity
checks like `2G`/`3G`/`4G` (those don't exercise enough of the 384-bit
range to surface a truncated high-order constant). Every numeric
constant and test vector that matters for correctness here was either
fetched from a real source (Wycheproof's test vectors, via `WebFetch`)
or cross-computed independently with Python (`pycryptodome` for curve
parameters and signature verification, `hashlib` for hash digests) -
never typed from memory and trusted blindly.

## What's deferred

- **RSA (RS256/RS384/RS512).** Not implemented. JOSE/JWT commonly needs
  it, but ES384 was the actual driving need. `bignum.nim`'s modular
  exponentiation (`bnModPow`) is most of what RSA verify needs; the
  remaining work is PKCS#1 v1.5 padding/decoding and DER parsing of the
  public key.
- **P-256 / P-521.** Only P-384 (ES384) is implemented. `ecdsa.nim`'s
  point arithmetic is curve-parameter-generic (`P384Curve` holds `p, a,
  b, gx, gy, n`); adding P-256/P-521 is mostly a matter of adding their
  NIST SP 800-186 constants and, for P-256, checking whether its curve
  order needs anything P-384-specific removed.
- **DER-encoded ECDSA signatures.** `ecdsa.nim`'s `verifyEcdsaP384`/
  `jwt.nim`'s ES384 path both expect raw `r || s` (JOSE's encoding, and
  what a JWT actually contains). A DER decoder (ASN.1 SEQUENCE of two
  INTEGERs) would be a small addition if something needs to verify a
  DER signature directly (e.g. from a certificate) rather than a JWT.

## Performance note

`bignum.nim`'s division is a straightforward bit-at-a-time binary long
division (O(bits²)) rather than Knuth's algorithm D, and `ecdsa.nim` does
real modular-inverse avoidance (Jacobian projective coordinates, see
that file's comment) but is otherwise unoptimized. This is fine for
verifying one JWT at a time - not fine if this ever needs to verify
thousands of signatures per second. If that need arises, the division
algorithm and constant-time-ness (this code is NOT constant-time
anywhere, which matters if it ever handles a *private* key rather than
only verifying against public keys) are the first two things to revisit.

## Layout

```
src/
  base64url.nim   -- base64url encode/decode
  sha2.nim        -- SHA-256/384/512
  hmac.nim        -- HMAC-SHA256/384/512
  bignum.nim      -- arbitrary-precision unsigned integer arithmetic
  ecdsa.nim       -- NIST P-384 point arithmetic + ECDSA verify
  jwt.nim         -- verifyJwt() / decodeJwtUnsafe() public API
tests/
  test_*.nim      -- one test file per src/ module, each runnable standalone
```
