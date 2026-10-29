import std/assertions
import std/syncio
import ../src/minijson

let r1 = parseJson("""{"alg":"ES384","typ":"JWT","x5u":"AbCd123"}""")
assert r1.ok
let r1v = r1.value
if r1v != nil:
  assert r1v.kind == jkObject
  let alg = objGet(r1v, "alg")
  if alg != nil:
    assert alg.kind == jkString
    assert alg.strVal == "ES384"
  else:
    assert false
else:
  assert false
echo "header parse: OK"

let r2 = parseJson("""{"exp":1893456000,"iat":1893452400,"nbf":null,"extraData":{"randomUuid":"abc","XUID":"1234"},"identityPublicKey":"MEkwEwYHK...","chain":[]}""")
assert r2.ok
let r2v = r2.value
if r2v != nil:
  let exp = objGet(r2v, "exp")
  if exp != nil:
    assert exp.kind == jkNumber
    assert exp.numVal == 1893456000.0
  else: assert false
  let extra = objGet(r2v, "extraData")
  if extra != nil:
    assert extra.kind == jkObject
    let uuid = objGet(extra, "randomUuid")
    if uuid != nil:
      assert uuid.strVal == "abc"
    else: assert false
  else: assert false
  let nbf = objGet(r2v, "nbf")
  if nbf != nil:
    assert nbf.kind == jkNull
  else: assert false
  let chain = objGet(r2v, "chain")
  if chain != nil:
    assert chain.kind == jkArray
    assert chain.arrVal.len == 0
  else: assert false
else:
  assert false
echo "payload parse (nested obj, array, null): OK"

# Escaped strings and missing-key lookup.
let r3 = parseJson("""{"msg":"line1\nline2\t\"quoted\""}""")
assert r3.ok
let r3v = r3.value
if r3v != nil:
  let msg = objGet(r3v, "msg")
  if msg != nil:
    assert msg.strVal == "line1\nline2\t\"quoted\""
  else: assert false
  assert objGet(r3v, "missing") == nil
else:
  assert false
echo "escapes + missing-key: OK"

# Malformed input is rejected, not silently accepted.
let bad = parseJson("""{"a": }""")
assert not bad.ok
echo "malformed JSON rejected: OK"

echo "all minijson checks passed"
