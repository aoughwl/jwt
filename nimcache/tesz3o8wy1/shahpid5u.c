#define NIM_INTBITS 64
/* GENERATED CODE. DO NOT EDIT. */

#ifdef __cplusplus
#  if __cplusplus >= 201103L
#    /* nullptr is more type safe (less implicit conversions than 0) */
#    define NIM_NIL nullptr
#  else
#    // both `((void*)0)` and `NULL` would cause codegen to emit
#    // error: assigning to 'Foo *' from incompatible type 'void *'
#    // but codegen could be fixed if need. See also potential caveat regarding
#    // NULL.
#    // However, `0` causes other issues, see #13798
#    define NIM_NIL 0
#  endif
#else
#  include <stdbool.h>
#  define NIM_NIL NULL
#endif

#ifdef __cplusplus
#define NB8 bool
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901)
// see #13798: to avoid conflicts for code emitting `#include <stdbool.h>`
#define NB8 _Bool
#else
typedef unsigned char NB8; // best effort
#endif

typedef unsigned char NC8;

typedef float NF32;
typedef double NF64;
#if defined(__BORLANDC__) || defined(_MSC_VER)
typedef signed char NI8;
typedef signed short int NI16;
typedef signed int NI32;
typedef __int64 NI64;
/* XXX: Float128? */
typedef unsigned char NU8;
typedef unsigned short int NU16;
typedef unsigned int NU32;
typedef unsigned __int64 NU64;
#elif defined(HAVE_STDINT_H)
#ifndef USE_NIM_NAMESPACE
#  include <stdint.h>
#endif
typedef int8_t NI8;
typedef int16_t NI16;
typedef int32_t NI32;
typedef int64_t NI64;
typedef uint8_t NU8;
typedef uint16_t NU16;
typedef uint32_t NU32;
typedef uint64_t NU64;
#elif defined(HAVE_CSTDINT)
#ifndef USE_NIM_NAMESPACE
#  include <cstdint>
#endif
typedef std::int8_t NI8;
typedef std::int16_t NI16;
typedef std::int32_t NI32;
typedef std::int64_t NI64;
typedef std::uint8_t NU8;
typedef std::uint16_t NU16;
typedef std::uint32_t NU32;
typedef std::uint64_t NU64;
#else
/* Unknown compiler/version, do our best */
#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ NI8;
#else
typedef signed char NI8;
#endif
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ NI16;
#else
typedef signed short int NI16;
#endif
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ NI32;
#else
typedef signed int NI32;
#endif
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ NI64;
#else
typedef long long int NI64;
#endif
/* XXX: Float128? */
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ NU8;
#else
typedef unsigned char NU8;
#endif
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ NU16;
#else
typedef unsigned short int NU16;
#endif
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ NU32;
#else
typedef unsigned int NU32;
#endif
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ NU64;
#else
typedef unsigned long long int NU64;
#endif
#endif

#ifdef NIM_INTBITS
#  if NIM_INTBITS == 64
typedef NI64 NI;
typedef NU64 NU;
#  elif NIM_INTBITS == 32
typedef NI32 NI;
typedef NU32 NU;
#  elif NIM_INTBITS == 16
typedef NI16 NI;
typedef NU16 NU;
#  elif NIM_INTBITS == 8
typedef NI8 NI;
typedef NU8 NU;
#  else
#    error "invalid bit width for int"
#  endif
#endif

#define NIM_TRUE true
#define NIM_FALSE false

#define _GNU_SOURCE

// Include math.h to use `NAN` that should be defined in C compilers supports C99.
#include <math.h>

// Define NAN in case math.h doesn't define it.
// NAN definition copied from math.h included in the Windows SDK version 10.0.14393.0
#ifndef NAN
#  ifndef _HUGE_ENUF
#    define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#  endif
#  define NAN_INFINITY ((float)(_HUGE_ENUF * _HUGE_ENUF))
#  define NAN ((float)(NAN_INFINITY * 0.0F))
#endif

#ifndef INF
#  ifdef INFINITY
#    define INF INFINITY
#  elif defined(HUGE_VAL)
#    define INF  HUGE_VAL
#  elif defined(_MSC_VER)
#    include <float.h>
#    define INF (DBL_MAX+DBL_MAX)
#  else
#    define INF (1.0 / 0.0)
#  endif
#endif

#if defined(__GNUC__) || defined(_MSC_VER)
#  define IL64(x) x##LL
#else /* works only without LL */
#  define IL64(x) ((NI64)x)
#endif


/* ------------ ignore typical warnings in Nim-generated files ------------- */
#if defined(__GNUC__) || defined(__clang__)
#  pragma GCC diagnostic ignored "-Wswitch-bool"
#  pragma GCC diagnostic ignored "-Wformat"
#  pragma GCC diagnostic ignored "-Wpointer-sign"
#  if defined(__clang__)
#    pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
#  else
#    pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#  endif
#endif



/* ------------------------------------------------------------------- */
#ifdef  __cplusplus
#  define NIM_EXTERNC extern "C"
#else
#  define NIM_EXTERNC
#endif

#if defined(WIN32) || defined(_WIN32) /* only Windows has this mess... */
#  define N_LIB_PRIVATE
#  define N_CDECL(rettype, name) rettype __cdecl name
#  define N_STDCALL(rettype, name) rettype __stdcall name
#  define N_SYSCALL(rettype, name) rettype __syscall name
#  define N_FASTCALL(rettype, name) rettype __fastcall name
#  define N_THISCALL(rettype, name) rettype __thiscall name
#  define N_SAFECALL(rettype, name) rettype __stdcall name
/* function pointers with calling convention: */
#  define N_CDECL_PTR(rettype, name) rettype (__cdecl *name)
#  define N_STDCALL_PTR(rettype, name) rettype (__stdcall *name)
#  define N_SYSCALL_PTR(rettype, name) rettype (__syscall *name)
#  define N_FASTCALL_PTR(rettype, name) rettype (__fastcall *name)
#  define N_THISCALL_PTR(rettype, name) rettype (__thiscall *name)
#  define N_SAFECALL_PTR(rettype, name) rettype (__stdcall *name)

#  ifdef __EMSCRIPTEN__
#    define N_LIB_EXPORT  NIM_EXTERNC __declspec(dllexport) __attribute__((used))
#    define N_LIB_EXPORT_VAR  __declspec(dllexport) __attribute__((used))
#  else
#    define N_LIB_EXPORT  NIM_EXTERNC __declspec(dllexport)
#    define N_LIB_EXPORT_VAR  __declspec(dllexport)
#  endif
#  define N_LIB_IMPORT  extern __declspec(dllimport)
#else
#  define N_LIB_PRIVATE __attribute__((visibility("hidden")))
#  if defined(__GNUC__)
#    define N_CDECL(rettype, name) rettype name
#    define N_STDCALL(rettype, name) rettype name
#    define N_SYSCALL(rettype, name) rettype name
#    define N_FASTCALL(rettype, name) __attribute__((fastcall)) rettype name
#    define N_SAFECALL(rettype, name) rettype name
/*   function pointers with calling convention: */
#    define N_CDECL_PTR(rettype, name) rettype (*name)
#    define N_STDCALL_PTR(rettype, name) rettype (*name)
#    define N_SYSCALL_PTR(rettype, name) rettype (*name)
#    define N_FASTCALL_PTR(rettype, name) __attribute__((fastcall)) rettype (*name)
#    define N_SAFECALL_PTR(rettype, name) rettype (*name)
#  else
#    define N_CDECL(rettype, name) rettype name
#    define N_STDCALL(rettype, name) rettype name
#    define N_SYSCALL(rettype, name) rettype name
#    define N_FASTCALL(rettype, name) rettype name
#    define N_SAFECALL(rettype, name) rettype name
/*   function pointers with calling convention: */
#    define N_CDECL_PTR(rettype, name) rettype (*name)
#    define N_STDCALL_PTR(rettype, name) rettype (*name)
#    define N_SYSCALL_PTR(rettype, name) rettype (*name)
#    define N_FASTCALL_PTR(rettype, name) rettype (*name)
#    define N_SAFECALL_PTR(rettype, name) rettype (*name)
#  endif
#  ifdef __EMSCRIPTEN__
#    define N_LIB_EXPORT NIM_EXTERNC __attribute__((visibility("default"), used))
#    define N_LIB_EXPORT_VAR  __attribute__((visibility("default"), used))
#  else
#    define N_LIB_EXPORT NIM_EXTERNC __attribute__((visibility("default")))
#    define N_LIB_EXPORT_VAR  __attribute__((visibility("default")))
#  endif
#  define N_LIB_IMPORT  extern
#endif

#if defined(__BORLANDC__) || defined(_MSC_VER) || defined(WIN32) || defined(_WIN32)
/* these compilers have a fastcall so use it: */
#  define N_NIMCALL(rettype, name) rettype __fastcall name
#  define N_NIMCALL_PTR(rettype, name) rettype (__fastcall *name)
#else
#  define N_NIMCALL(rettype, name) rettype name /* no modifier */
#  define N_NIMCALL_PTR(rettype, name) rettype (*name)
#endif

#define N_NOCONV(rettype, name) rettype name
/* specify no calling convention */
#define N_NOCONV_PTR(rettype, name) rettype (*name)

/* calling convention mess ----------------------------------------------- */
#if defined(__GNUC__) || defined(__TINYC__)
  /* these should support C99's inline */
#  define N_INLINE(rettype, name) inline rettype name
#elif defined(__BORLANDC__) || defined(_MSC_VER)
/* Borland's compiler is really STRANGE here; note that the __fastcall
   keyword cannot be before the return type, but __inline cannot be after
   the return type, so we do not handle this mess in the code generator
   but rather here. */
#  define N_INLINE(rettype, name) __inline rettype name
#else /* others are less picky: */
#  define N_INLINE(rettype, name) rettype __inline name
#endif

#define N_INLINE_PTR(rettype, name) rettype (*name)

#if defined(__GNUC__) || defined(__ICC__)
#  define N_NOINLINE __attribute__((__noinline__))
#elif defined(_MSC_VER)
#  define N_NOINLINE __declspec(noinline)
#else
#  define N_NOINLINE
#endif

#define N_NOINLINE_PTR(rettype, name) rettype (*name)

#if defined(_MSC_VER)
#  define NIM_ALIGN(x)  __declspec(align(x))
#  define NIM_ALIGNOF(x) __alignof(x)
#else
#  define NIM_ALIGN(x)  __attribute__((aligned(x)))
#  define NIM_ALIGNOF(x) __alignof__(x)
#endif

#include <stddef.h>


/*
  NIM_THREADVAR declaration based on
  https://stackoverflow.com/questions/18298280/how-to-declare-a-variable-as-thread-local-portably
*/
#if defined _WIN32
#  if defined _MSC_VER || defined __BORLANDC__
#    define NIM_THREADVAR __declspec(thread)
#  else
#    define NIM_THREADVAR __thread
#  endif
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112 && !defined __STDC_NO_THREADS__
#  define NIM_THREADVAR _Thread_local
#elif defined _WIN32 && ( \
       defined _MSC_VER || \
       defined __ICL || \
       defined __BORLANDC__ )
#  define NIM_THREADVAR __declspec(thread)
#elif defined(__TINYC__) || defined(__GENODE__)
#  define NIM_THREADVAR
/* note that ICC (linux) and Clang are covered by __GNUC__ */
#elif defined __GNUC__ || \
       defined __SUNPRO_C || \
       defined __xlC__
#  define NIM_THREADVAR __thread
#else
#  error "Cannot define NIM_THREADVAR"
#endif

/* define NIM_STATIC_ASSERT */
#if defined(__cplusplus)
#define NIM_STATIC_ASSERT(x, msg) static_assert((x), msg)
#else
#define NIM_STATIC_ASSERT(x, msg) _Static_assert((x), msg)
#endif

// Test to see if Nim and the C compiler agree on the size of a pointer.
NIM_STATIC_ASSERT(sizeof(NI) == sizeof(void*) && NIM_INTBITS == sizeof(NI)*8, "Pointer size mismatch between Nim and C/C++ backend. You probably need to setup the backend compiler for target CPU.");

N_INLINE(NB8, _Qlengc_div_sll_overflow)(long long int a, long long int b, long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long long int)(((unsigned long long int)1) << (sizeof(long long int) * 8 - 1)) && b == -1) {
    *res = a;
    return NIM_TRUE;
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_div_sl_overflow)(long int a, long int b, long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long int)(((unsigned long int)1) << (sizeof(long int) * 8 - 1)) && b == -1) {
    *res = a;
    return NIM_TRUE;
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_div_ull_overflow)(unsigned long long int a, unsigned long long int b, unsigned long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE; /* Overflow: division by zero */
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_div_ul_overflow)(unsigned long int a, unsigned long int b, unsigned long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a / b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_sll_overflow)(long long int a, long long int b, long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long long int)(((unsigned long long int)1) << (sizeof(long long int) * 8 - 1)) && b == -1) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_sl_overflow)(long int a, long int b, long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  if (a == (long int)(((unsigned long int)1) << (sizeof(long int) * 8 - 1)) && b == -1) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_ull_overflow)(unsigned long long int a, unsigned long long int b, unsigned long long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}

N_INLINE(NB8, _Qlengc_mod_ul_overflow)(unsigned long int a, unsigned long int b, unsigned long int *res) {
  if (b == 0) {
    *res = 0;
    return NIM_TRUE;
  }
  *res = a % b;
  return NIM_FALSE;
}
typedef struct LongString_0_sysvq0asl LongString_0_sysvq0asl;
typedef struct openArray_0_Is74e021_shahpid5u{
  NU8* a_0;
  NI64 len_0;}
openArray_0_Is74e021_shahpid5u;
typedef struct seq_0_Incv1wn_shahpid5u{
  NI64 len_0;
  NU8* data_0;}
seq_0_Incv1wn_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS32ZS64_shahpid5u{
  NU32 a[IL64(64)];}
X60Qt_0_IAarrayAuS32ZS64_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS8ZS32_shahpid5u{
  NU8 a[IL64(32)];}
X60Qt_0_IAarrayAuS8ZS32_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS32ZS8_shahpid5u{
  NU32 a[IL64(8)];}
X60Qt_0_IAarrayAuS32ZS8_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS64ZS80_shahpid5u{
  NU64 a[IL64(80)];}
X60Qt_0_IAarrayAuS64ZS80_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS64ZS8_shahpid5u{
  NU64 a[IL64(8)];}
X60Qt_0_IAarrayAuS64ZS8_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS8ZS64_shahpid5u{
  NU8 a[IL64(64)];}
X60Qt_0_IAarrayAuS8ZS64_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS8ZS48_shahpid5u{
  NU8 a[IL64(48)];}
X60Qt_0_IAarrayAuS8ZS48_shahpid5u;
typedef struct LongString_0_sysvq0asl{
  NI64 fullLen_0;
  NI64 rc_0;
  NI64 capImpl_0;
  NC8 data_0[];}
LongString_0_sysvq0asl;
typedef struct string_0_sysvq0asl{
  NU64 bytes_0;
  LongString_0_sysvq0asl* more_0;}
string_0_sysvq0asl;
typedef N_NIMCALL_PTR(void,  X60Qt_0_IAiS64ZSEAnimcallZAfalseZAR17_sysvq0asl)(NI64);
static inline NI64 len_6_Itc4yka_shahpid5u(openArray_0_Is74e021_shahpid5u a_4);
seq_0_Incv1wn_shahpid5u newSeq_0_Ivbxvoi1_shahpid5u(NI64 size_1);
static inline NU8* getQ_10_Ikgj4ax_shahpid5u(openArray_0_Is74e021_shahpid5u x_8, NI64 idx_1);
static inline void putQ_7_Ipw0nqk1_shahpid5u(seq_0_Incv1wn_shahpid5u* s_4, NI64 i_10, NU8 elem_2);
static inline void add_0_Ibphvmo_shahpid5u(seq_0_Incv1wn_shahpid5u* s_5, NU8 elem_3);
static inline NI64 len_3_Izoe8zv_shahpid5u(seq_0_Incv1wn_shahpid5u s_7);
static inline void minusQeQ_0_Isqosxa_shahpid5u(NI64* x_9, NI64 y_4);
static inline NU8* getQ_7_Ig0r1051_shahpid5u(seq_0_Incv1wn_shahpid5u s_8, NI64 i_11);
static inline void plusQeQ_0_Ih8llpb_shahpid5u(NU32* x_10, NU32 y_5);
static inline void plusQeQ_0_Ihg6mz11_shahpid5u(NI64* x_11, NI64 y_6);
static inline void plusQeQ_0_Iar0t5x_shahpid5u(NU64* x_12, NU64 y_7);
static inline NI64 memSizeInBytes_0_Infw7m1_shahpid5u(NI64 size_3);
static inline void inc_1_Irn1g7r1_shahpid5u(NI64* x_13);
static inline NI64 capInBytes_0_Iffahgv_shahpid5u(seq_0_Incv1wn_shahpid5u s_9);
NB8 resize_0_Iuiuhg71_shahpid5u(seq_0_Incv1wn_shahpid5u* dest_1, NI64 addedElements_1);
void eQdestroy_1_Ijx6eoq_shahpid5u(seq_0_Incv1wn_shahpid5u s_12);
static inline NI64 nimIcheckB(NI64 i_19, NI64 b_19);
extern void* alloc_0_sysvq0asl(NI64 size_10);
extern X60Qt_0_IAiS64ZSEAnimcallZAfalseZAR17_sysvq0asl oomHandler_0_sysvq0asl;
extern void panic_0_sysvq0asl(string_0_sysvq0asl s_68);
extern NI64 allocatedSize_0_sysvq0asl(void* p_11);
static inline NI64 recalcCap_0_sysvq0asl(NI64 oldCap_0, NI64 addedElements_0);
extern void* realloc_0_sysvq0asl(void* p_9, NI64 size_12);
extern void dealloc_0_sysvq0asl(void* p_10);
extern void X60Qini_0_sysvq0asl(void);
extern void raiseIndexError3_0_Ice8haj1_sysvq0asl(NI64 i_66, NI64 a_45, NI64 b_34);
static inline NI64 max_3_sysvq0asl(NI64 x_212, NI64 y_169);
LongString_0_sysvq0asl const strlit_0_I5410009123728214703_shahpid5u = {
  .fullLen_0 = IL64(95), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../nimony/lib/std/system/openarrays.nim(10, 49): 0 <= idx and idx < x.len [AssertionDefect]\012"}
;
LongString_0_sysvq0asl const strlit_0_I17896528460403498414_shahpid5u = {
  .fullLen_0 = IL64(89), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../nimony/lib/std/system/seqimpl.nim(169, 53): i < s.len and 0 <= i [AssertionDefect]\012"}
;
LongString_0_sysvq0asl const strlit_0_I16713941061949234674_shahpid5u = {
  .fullLen_0 = IL64(89), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "../../nimony/lib/std/system/seqimpl.nim(167, 41): i < s.len and 0 <= i [AssertionDefect]\012"}
;
X60Qt_0_IAarrayAuS32ZS64_shahpid5u const sha256K_0_shahpid5u = {
  .a = {
    ((NU32)1116352408ull), ((NU32)1899447441ull), ((NU32)3049323471ull), ((NU32)3921009573ull), ((NU32)961987163ull), ((NU32)1508970993ull), ((NU32)2453635748ull), ((NU32)2870763221ull), ((NU32)3624381080ull), ((NU32)310598401ull), ((NU32)607225278ull), ((NU32)1426881987ull), ((NU32)1925078388ull), ((NU32)2162078206ull), ((NU32)2614888103ull), ((NU32)3248222580ull), ((NU32)3835390401ull), ((NU32)4022224774ull), ((NU32)264347078ull), ((NU32)604807628ull), ((NU32)770255983ull), ((NU32)1249150122ull), ((NU32)1555081692ull), ((NU32)1996064986ull), ((NU32)2554220882ull), ((NU32)2821834349ull), ((NU32)2952996808ull), ((NU32)3210313671ull), ((NU32)3336571891ull), ((NU32)3584528711ull), ((NU32)113926993ull), ((NU32)338241895ull), ((NU32)666307205ull), ((NU32)773529912ull), ((NU32)1294757372ull), ((NU32)1396182291ull), ((NU32)1695183700ull), ((NU32)1986661051ull), ((NU32)2177026350ull), ((NU32)2456956037ull), ((NU32)2730485921ull), ((NU32)2820302411ull), ((NU32)3259730800ull), ((NU32)3345764771ull), ((NU32)3516065817ull), ((NU32)3600352804ull), ((NU32)4094571909ull), ((NU32)275423344ull), ((NU32)430227734ull), ((NU32)506948616ull), ((NU32)659060556ull), ((NU32)883997877ull), ((NU32)958139571ull), ((NU32)1322822218ull), ((NU32)1537002063ull), ((NU32)1747873779ull), ((NU32)1955562222ull), ((NU32)2024104815ull), ((NU32)2227730452ull), ((NU32)2361852424ull), ((NU32)2428436474ull), ((NU32)2756734187ull), ((NU32)3204031479ull), ((NU32)3329325298ull)}}
;
X60Qt_0_IAarrayAuS64ZS80_shahpid5u const sha512K_0_shahpid5u = {
  .a = {
    ((NU64)4794697086780616226ull), ((NU64)8158064640168781261ull), ((NU64)13096744586834688815ull), ((NU64)16840607885511220156ull), ((NU64)4131703408338449720ull), ((NU64)6480981068601479193ull), ((NU64)10538285296894168987ull), ((NU64)12329834152419229976ull), ((NU64)15566598209576043074ull), ((NU64)1334009975649890238ull), ((NU64)2608012711638119052ull), ((NU64)6128411473006802146ull), ((NU64)8268148722764581231ull), ((NU64)9286055187155687089ull), ((NU64)11230858885718282805ull), ((NU64)13951009754708518548ull), ((NU64)16472876342353939154ull), ((NU64)17275323862435702243ull), ((NU64)1135362057144423861ull), ((NU64)2597628984639134821ull), ((NU64)3308224258029322869ull), ((NU64)5365058923640841347ull), ((NU64)6679025012923562964ull), ((NU64)8573033837759648693ull), ((NU64)10970295158949994411ull), ((NU64)12119686244451234320ull), ((NU64)12683024718118986047ull), ((NU64)13788192230050041572ull), ((NU64)14330467153632333762ull), ((NU64)15395433587784984357ull), ((NU64)489312712824947311ull), ((NU64)1452737877330783856ull), ((NU64)2861767655752347644ull), ((NU64)3322285676063803686ull), ((NU64)5560940570517711597ull), ((NU64)5996557281743188959ull), ((NU64)7280758554555802590ull), ((NU64)8532644243296465576ull), ((NU64)9350256976987008742ull), ((NU64)10552545826968843579ull), ((NU64)11727347734174303076ull), ((NU64)12113106623233404929ull), ((NU64)14000437183269869457ull), ((NU64)14369950271660146224ull), ((NU64)15101387698204529176ull), ((NU64)15463397548674623760ull), ((NU64)17586052441742319658ull), ((NU64)1182934255886127544ull), ((NU64)1847814050463011016ull), ((NU64)2177327727835720531ull), ((NU64)2830643537854262169ull), ((NU64)3796741975233480872ull), ((NU64)4115178125766777443ull), ((NU64)5681478168544905931ull), ((NU64)6601373596472566643ull), ((NU64)7507060721942968483ull), ((NU64)8399075790359081724ull), ((NU64)8693463985226723168ull), ((NU64)9568029438360202098ull), ((NU64)10144078919501101548ull), ((NU64)10430055236837252648ull), ((NU64)11840083180663258601ull), ((NU64)13761210420658862357ull), ((NU64)14299343276471374635ull), ((NU64)14566680578165727644ull), ((NU64)15097957966210449927ull), ((NU64)16922976911328602910ull), ((NU64)17689382322260857208ull), ((NU64)500013540394364858ull), ((NU64)748580250866718886ull), ((NU64)1242879168328830382ull), ((NU64)1977374033974150939ull), ((NU64)2944078676154940804ull), ((NU64)3659926193048069267ull), ((NU64)4368137639120453308ull), ((NU64)4836135668995329356ull), ((NU64)5532061633213252278ull), ((NU64)6448918945643986474ull), ((NU64)6902733635092675308ull), ((NU64)7801388544844847127ull)}}
;
NB8 X60QiniGuard_0_shahpid5u;
static inline NU32 rotr32_0_shahpid5u(NU32 x_0, NI64 n_0){
  NU32 result_0;
  result_0 = ((NU32)(((NU32)(x_0 >> ((NU32)n_0))) | ((NU32)(x_0 << ((NU32)((NI64)(IL64(32) - n_0)))))));
  return result_0;}
X60Qt_0_IAarrayAuS8ZS32_shahpid5u sha256_0_shahpid5u(openArray_0_Is74e021_shahpid5u msg_0){
  X60Qt_0_IAarrayAuS8ZS32_shahpid5u result_1;
  X60Qt_0_IAarrayAuS32ZS8_shahpid5u h_0 = (X60Qt_0_IAarrayAuS32ZS8_shahpid5u){
    .a = {
      ((NU32)1779033703ull), ((NU32)3144134277ull), ((NU32)1013904242ull), ((NU32)2773480762ull), ((NU32)1359893119ull), ((NU32)2600822924ull), ((NU32)528734635ull), ((NU32)1541459225ull)}}
  ;
  NI64 X60Qx_1 = len_6_Itc4yka_shahpid5u(msg_0);
  seq_0_Incv1wn_shahpid5u data_0 = newSeq_0_Ivbxvoi1_shahpid5u(X60Qx_1);
  {
    NI64 X60Qlf_0 = IL64(0);
    NI64 X60Qlf_1 = len_6_Itc4yka_shahpid5u(msg_0);
    NI64 X60Qlf_2 = X60Qlf_0;
    {
      while (X60Qlf_2 < X60Qlf_1){
        {
          NU8* X60Qx_2 = getQ_10_Ikgj4ax_shahpid5u(msg_0, X60Qlf_2);
          putQ_7_Ipw0nqk1_shahpid5u((&data_0), X60Qlf_2, (*X60Qx_2));}
        inc_1_Irn1g7r1_shahpid5u((&X60Qlf_2));}}
    whileStmtLabel_1: ;}
  forStmtLabel_0: ;
  NI64 X60Qx_3 = len_6_Itc4yka_shahpid5u(msg_0);
  NU64 bitLen_0 = ((NU64)(((NU64)X60Qx_3) * ((NU64)8ull)));
  add_0_Ibphvmo_shahpid5u((&data_0), ((NU8)128ull));
  {
    while ((!(((NI64)(data_0.len_0 % IL64(64))) == IL64(56)))){
      add_0_Ibphvmo_shahpid5u((&data_0), ((NU8)0ull));}}
  whileStmtLabel_2: ;
  NI64 shift_0 = IL64(56);
  {
    while (IL64(0) <= shift_0){
      add_0_Ibphvmo_shahpid5u((&data_0), ((NU8)((NU64)(((NU64)(bitLen_0 >> ((NU64)shift_0))) & ((NU64)255ull)))));
      minusQeQ_0_Isqosxa_shahpid5u((&shift_0), IL64(8));}}
  whileStmtLabel_3: ;
  NI64 blockStart_0 = IL64(0);
  {
    while (NIM_TRUE){
      NI64 X60Qx_4 = len_3_Izoe8zv_shahpid5u(data_0);
      if (blockStart_0 < X60Qx_4){
        X60Qt_0_IAarrayAuS32ZS64_shahpid5u w_0;
        {
          NI64 X60Qlf_3 = IL64(0);
          NI64 X60Qlf_4 = IL64(16);
          NI64 X60Qlf_5 = X60Qlf_3;
          {
            while (X60Qlf_5 < X60Qlf_4){
              {
                NI64 X60Qii_7 = ((NI64)(blockStart_0 + ((NI64)(X60Qlf_5 * IL64(4)))));
                NI64 X60Qx_5 = nimIcheckB(X60Qlf_5, IL64(63));
                NU8* X60Qx_6 = getQ_7_Ig0r1051_shahpid5u(data_0, X60Qii_7);
                NU8* X60Qx_7 = getQ_7_Ig0r1051_shahpid5u(data_0, ((NI64)(X60Qii_7 + IL64(1))));
                NU8* X60Qx_8 = getQ_7_Ig0r1051_shahpid5u(data_0, ((NI64)(X60Qii_7 + IL64(2))));
                NU8* X60Qx_9 = getQ_7_Ig0r1051_shahpid5u(data_0, ((NI64)(X60Qii_7 + IL64(3))));
                w_0.a[X60Qx_5] = ((NU32)(((NU32)(((NU32)(((NU32)(((NU32)(*X60Qx_6)) << IL64(24))) | ((NU32)(((NU32)(*X60Qx_7)) << IL64(16))))) | ((NU32)(((NU32)(*X60Qx_8)) << IL64(8))))) | ((NU32)(*X60Qx_9))));}
              inc_1_Irn1g7r1_shahpid5u((&X60Qlf_5));}}
          whileStmtLabel_6: ;}
        forStmtLabel_5: ;
        {
          NI64 X60Qlf_6 = IL64(16);
          NI64 X60Qlf_7 = IL64(64);
          NI64 X60Qlf_8 = X60Qlf_6;
          {
            while (X60Qlf_8 < X60Qlf_7){
              {
                NI64 X60Qx_10 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(15))), IL64(63));
                NU32 X60Qx_11 = rotr32_0_shahpid5u(w_0.a[X60Qx_10], IL64(7));
                NI64 X60Qx_12 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(15))), IL64(63));
                NU32 X60Qx_13 = rotr32_0_shahpid5u(w_0.a[X60Qx_12], IL64(18));
                NI64 X60Qx_14 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(15))), IL64(63));
                NU32 X60Qii_10 = ((NU32)(((NU32)(X60Qx_11 ^ X60Qx_13)) ^ ((NU32)(w_0.a[X60Qx_14] >> ((NU32)3ull)))));
                NI64 X60Qx_15 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(2))), IL64(63));
                NU32 X60Qx_16 = rotr32_0_shahpid5u(w_0.a[X60Qx_15], IL64(17));
                NI64 X60Qx_17 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(2))), IL64(63));
                NU32 X60Qx_18 = rotr32_0_shahpid5u(w_0.a[X60Qx_17], IL64(19));
                NI64 X60Qx_19 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(2))), IL64(63));
                NU32 X60Qii_11 = ((NU32)(((NU32)(X60Qx_16 ^ X60Qx_18)) ^ ((NU32)(w_0.a[X60Qx_19] >> ((NU32)10ull)))));
                NI64 X60Qx_20 = nimIcheckB(X60Qlf_8, IL64(63));
                NI64 X60Qx_21 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(16))), IL64(63));
                NI64 X60Qx_22 = nimIcheckB(((NI64)(X60Qlf_8 - IL64(7))), IL64(63));
                w_0.a[X60Qx_20] = ((NU32)(((NU32)(((NU32)(w_0.a[X60Qx_21] + X60Qii_10)) + w_0.a[X60Qx_22])) + X60Qii_11));}
              inc_1_Irn1g7r1_shahpid5u((&X60Qlf_8));}}
          whileStmtLabel_9: ;}
        forStmtLabel_8: ;
        NI64 X60Qx_23 = nimIcheckB(IL64(0), IL64(7));
        NU32 a_2 = h_0.a[X60Qx_23];
        NI64 X60Qx_24 = nimIcheckB(IL64(1), IL64(7));
        NU32 b_1 = h_0.a[X60Qx_24];
        NI64 X60Qx_25 = nimIcheckB(IL64(2), IL64(7));
        NU32 c_0 = h_0.a[X60Qx_25];
        NI64 X60Qx_26 = nimIcheckB(IL64(3), IL64(7));
        NU32 d_0 = h_0.a[X60Qx_26];
        NI64 X60Qx_27 = nimIcheckB(IL64(4), IL64(7));
        NU32 e_0 = h_0.a[X60Qx_27];
        NI64 X60Qx_28 = nimIcheckB(IL64(5), IL64(7));
        NU32 f_0 = h_0.a[X60Qx_28];
        NI64 X60Qx_29 = nimIcheckB(IL64(6), IL64(7));
        NU32 g_0 = h_0.a[X60Qx_29];
        NI64 X60Qx_30 = nimIcheckB(IL64(7), IL64(7));
        NU32 hh_0 = h_0.a[X60Qx_30];
        {
          NI64 X60Qlf_9 = IL64(0);
          NI64 X60Qlf_10 = IL64(64);
          NI64 X60Qlf_11 = X60Qlf_9;
          {
            while (X60Qlf_11 < X60Qlf_10){
              {
                NU32 X60Qx_31 = rotr32_0_shahpid5u(e_0, IL64(6));
                NU32 X60Qx_32 = rotr32_0_shahpid5u(e_0, IL64(11));
                NU32 X60Qx_33 = rotr32_0_shahpid5u(e_0, IL64(25));
                NU32 X60Qii_14 = ((NU32)(((NU32)(X60Qx_31 ^ X60Qx_32)) ^ X60Qx_33));
                NU32 X60Qii_15 = ((NU32)(((NU32)(e_0 & f_0)) ^ ((NU32)(((NU32) ~ e_0) & g_0))));
                NI64 X60Qx_34 = nimIcheckB(X60Qlf_11, IL64(63));
                NI64 X60Qx_35 = nimIcheckB(X60Qlf_11, IL64(63));
                NU32 X60Qii_16 = ((NU32)(((NU32)(((NU32)(((NU32)(hh_0 + X60Qii_14)) + X60Qii_15)) + sha256K_0_shahpid5u.a[X60Qx_34])) + w_0.a[X60Qx_35]));
                NU32 X60Qx_36 = rotr32_0_shahpid5u(a_2, IL64(2));
                NU32 X60Qx_37 = rotr32_0_shahpid5u(a_2, IL64(13));
                NU32 X60Qx_38 = rotr32_0_shahpid5u(a_2, IL64(22));
                NU32 X60Qii_17 = ((NU32)(((NU32)(X60Qx_36 ^ X60Qx_37)) ^ X60Qx_38));
                NU32 X60Qii_18 = ((NU32)(((NU32)(((NU32)(a_2 & b_1)) ^ ((NU32)(a_2 & c_0)))) ^ ((NU32)(b_1 & c_0))));
                NU32 X60Qii_19 = ((NU32)(X60Qii_17 + X60Qii_18));
                hh_0 = g_0;
                g_0 = f_0;
                f_0 = e_0;
                e_0 = ((NU32)(d_0 + X60Qii_16));
                d_0 = c_0;
                c_0 = b_1;
                b_1 = a_2;
                a_2 = ((NU32)(X60Qii_16 + X60Qii_19));}
              inc_1_Irn1g7r1_shahpid5u((&X60Qlf_11));}}
          whileStmtLabel_13: ;}
        forStmtLabel_12: ;
        NI64 X60Qx_39 = nimIcheckB(IL64(0), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_39]), a_2);
        NI64 X60Qx_40 = nimIcheckB(IL64(1), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_40]), b_1);
        NI64 X60Qx_41 = nimIcheckB(IL64(2), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_41]), c_0);
        NI64 X60Qx_42 = nimIcheckB(IL64(3), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_42]), d_0);
        NI64 X60Qx_43 = nimIcheckB(IL64(4), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_43]), e_0);
        NI64 X60Qx_44 = nimIcheckB(IL64(5), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_44]), f_0);
        NI64 X60Qx_45 = nimIcheckB(IL64(6), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_45]), g_0);
        NI64 X60Qx_46 = nimIcheckB(IL64(7), IL64(7));
        plusQeQ_0_Ih8llpb_shahpid5u((&h_0.a[X60Qx_46]), hh_0);
        plusQeQ_0_Ihg6mz11_shahpid5u((&blockStart_0), IL64(64));}
      else {
        break;}}}
  whileStmtLabel_4: ;
  {
    NI64 X60Qlf_12 = IL64(0);
    NI64 X60Qlf_13 = IL64(8);
    NI64 X60Qlf_14 = X60Qlf_12;
    {
      while (X60Qlf_14 < X60Qlf_13){
        {
          NI64 X60Qx_47 = nimIcheckB(((NI64)(X60Qlf_14 * IL64(4))), IL64(31));
          NI64 X60Qx_48 = nimIcheckB(X60Qlf_14, IL64(7));
          result_1.a[X60Qx_47] = ((NU8)((NU32)(h_0.a[X60Qx_48] >> IL64(24))));
          NI64 X60Qx_49 = nimIcheckB(((NI64)(((NI64)(X60Qlf_14 * IL64(4))) + IL64(1))), IL64(31));
          NI64 X60Qx_50 = nimIcheckB(X60Qlf_14, IL64(7));
          result_1.a[X60Qx_49] = ((NU8)((NU32)(((NU32)(h_0.a[X60Qx_50] >> IL64(16))) & ((NU32)255ull))));
          NI64 X60Qx_51 = nimIcheckB(((NI64)(((NI64)(X60Qlf_14 * IL64(4))) + IL64(2))), IL64(31));
          NI64 X60Qx_52 = nimIcheckB(X60Qlf_14, IL64(7));
          result_1.a[X60Qx_51] = ((NU8)((NU32)(((NU32)(h_0.a[X60Qx_52] >> IL64(8))) & ((NU32)255ull))));
          NI64 X60Qx_53 = nimIcheckB(((NI64)(((NI64)(X60Qlf_14 * IL64(4))) + IL64(3))), IL64(31));
          NI64 X60Qx_54 = nimIcheckB(X60Qlf_14, IL64(7));
          result_1.a[X60Qx_53] = ((NU8)((NU32)(h_0.a[X60Qx_54] & ((NU32)255ull))));}
        inc_1_Irn1g7r1_shahpid5u((&X60Qlf_14));}}
    whileStmtLabel_21: ;}
  forStmtLabel_20: ;
  eQdestroy_1_Ijx6eoq_shahpid5u(data_0);
  return result_1;
  eQdestroy_1_Ijx6eoq_shahpid5u(data_0);
  return result_1;}
static inline NU64 rotr64_0_shahpid5u(NU64 x_1, NI64 n_1){
  NU64 result_2;
  result_2 = ((NU64)(((NU64)(x_1 >> ((NU64)n_1))) | ((NU64)(x_1 << ((NU64)((NI64)(IL64(64) - n_1)))))));
  return result_2;}
X60Qt_0_IAarrayAuS64ZS8_shahpid5u sha512Core_0_shahpid5u(openArray_0_Is74e021_shahpid5u msg_1, X60Qt_0_IAarrayAuS64ZS8_shahpid5u* iv_0){
  X60Qt_0_IAarrayAuS64ZS8_shahpid5u result_3;
  X60Qt_0_IAarrayAuS64ZS8_shahpid5u h_1 = (*iv_0);
  NI64 X60Qx_55 = len_6_Itc4yka_shahpid5u(msg_1);
  seq_0_Incv1wn_shahpid5u data_1 = newSeq_0_Ivbxvoi1_shahpid5u(X60Qx_55);
  {
    NI64 X60Qlf_15 = IL64(0);
    NI64 X60Qlf_16 = len_6_Itc4yka_shahpid5u(msg_1);
    NI64 X60Qlf_17 = X60Qlf_15;
    {
      while (X60Qlf_17 < X60Qlf_16){
        {
          NU8* X60Qx_56 = getQ_10_Ikgj4ax_shahpid5u(msg_1, X60Qlf_17);
          putQ_7_Ipw0nqk1_shahpid5u((&data_1), X60Qlf_17, (*X60Qx_56));}
        inc_1_Irn1g7r1_shahpid5u((&X60Qlf_17));}}
    whileStmtLabel_1: ;}
  forStmtLabel_0: ;
  NI64 X60Qx_57 = len_6_Itc4yka_shahpid5u(msg_1);
  NU64 bitLen_1 = ((NU64)(((NU64)X60Qx_57) * ((NU64)8ull)));
  add_0_Ibphvmo_shahpid5u((&data_1), ((NU8)128ull));
  {
    while ((!(((NI64)(data_1.len_0 % IL64(128))) == IL64(112)))){
      add_0_Ibphvmo_shahpid5u((&data_1), ((NU8)0ull));}}
  whileStmtLabel_2: ;
  {
    NI64 X60Qlf_18 = IL64(0);
    NI64 X60Qlf_19 = IL64(8);
    NI64 X60Qlf_20 = X60Qlf_18;
    {
      while (X60Qlf_20 < X60Qlf_19){
        {
          add_0_Ibphvmo_shahpid5u((&data_1), ((NU8)0ull));}
        inc_1_Irn1g7r1_shahpid5u((&X60Qlf_20));}}
    whileStmtLabel_4: ;}
  forStmtLabel_3: ;
  NI64 shift_1 = IL64(56);
  {
    while (IL64(0) <= shift_1){
      add_0_Ibphvmo_shahpid5u((&data_1), ((NU8)((NU64)(((NU64)(bitLen_1 >> ((NU64)shift_1))) & ((NU64)255ull)))));
      minusQeQ_0_Isqosxa_shahpid5u((&shift_1), IL64(8));}}
  whileStmtLabel_5: ;
  NI64 blockStart_1 = IL64(0);
  {
    while (NIM_TRUE){
      NI64 X60Qx_58 = len_3_Izoe8zv_shahpid5u(data_1);
      if (blockStart_1 < X60Qx_58){
        X60Qt_0_IAarrayAuS64ZS80_shahpid5u w_1;
        {
          NI64 X60Qlf_21 = IL64(0);
          NI64 X60Qlf_22 = IL64(16);
          NI64 X60Qlf_23 = X60Qlf_21;
          {
            while (X60Qlf_23 < X60Qlf_22){
              {
                NI64 X60Qii_9 = ((NI64)(blockStart_1 + ((NI64)(X60Qlf_23 * IL64(8)))));
                NU64 X60Qii_10 = ((NU64)0ull);
                {
                  NI64 X60Qlf_24 = IL64(0);
                  NI64 X60Qlf_25 = IL64(8);
                  NI64 X60Qlf_26 = X60Qlf_24;
                  {
                    while (X60Qlf_26 < X60Qlf_25){
                      {
                        NU8* X60Qx_59 = getQ_7_Ig0r1051_shahpid5u(data_1, ((NI64)(X60Qii_9 + X60Qlf_26)));
                        X60Qii_10 = ((NU64)(((NU64)(X60Qii_10 << IL64(8))) | ((NU64)(*X60Qx_59))));}
                      inc_1_Irn1g7r1_shahpid5u((&X60Qlf_26));}}
                  whileStmtLabel_12: ;}
                forStmtLabel_11: ;
                NI64 X60Qx_60 = nimIcheckB(X60Qlf_23, IL64(79));
                w_1.a[X60Qx_60] = X60Qii_10;}
              inc_1_Irn1g7r1_shahpid5u((&X60Qlf_23));}}
          whileStmtLabel_8: ;}
        forStmtLabel_7: ;
        {
          NI64 X60Qlf_27 = IL64(16);
          NI64 X60Qlf_28 = IL64(80);
          NI64 X60Qlf_29 = X60Qlf_27;
          {
            while (X60Qlf_29 < X60Qlf_28){
              {
                NI64 X60Qx_61 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(15))), IL64(79));
                NU64 X60Qx_62 = rotr64_0_shahpid5u(w_1.a[X60Qx_61], IL64(1));
                NI64 X60Qx_63 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(15))), IL64(79));
                NU64 X60Qx_64 = rotr64_0_shahpid5u(w_1.a[X60Qx_63], IL64(8));
                NI64 X60Qx_65 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(15))), IL64(79));
                NU64 X60Qii_15 = ((NU64)(((NU64)(X60Qx_62 ^ X60Qx_64)) ^ ((NU64)(w_1.a[X60Qx_65] >> ((NU64)7ull)))));
                NI64 X60Qx_66 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(2))), IL64(79));
                NU64 X60Qx_67 = rotr64_0_shahpid5u(w_1.a[X60Qx_66], IL64(19));
                NI64 X60Qx_68 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(2))), IL64(79));
                NU64 X60Qx_69 = rotr64_0_shahpid5u(w_1.a[X60Qx_68], IL64(61));
                NI64 X60Qx_70 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(2))), IL64(79));
                NU64 X60Qii_16 = ((NU64)(((NU64)(X60Qx_67 ^ X60Qx_69)) ^ ((NU64)(w_1.a[X60Qx_70] >> ((NU64)6ull)))));
                NI64 X60Qx_71 = nimIcheckB(X60Qlf_29, IL64(79));
                NI64 X60Qx_72 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(16))), IL64(79));
                NI64 X60Qx_73 = nimIcheckB(((NI64)(X60Qlf_29 - IL64(7))), IL64(79));
                w_1.a[X60Qx_71] = ((NU64)(((NU64)(((NU64)(w_1.a[X60Qx_72] + X60Qii_15)) + w_1.a[X60Qx_73])) + X60Qii_16));}
              inc_1_Irn1g7r1_shahpid5u((&X60Qlf_29));}}
          whileStmtLabel_14: ;}
        forStmtLabel_13: ;
        NI64 X60Qx_74 = nimIcheckB(IL64(0), IL64(7));
        NU64 a_3 = h_1.a[X60Qx_74];
        NI64 X60Qx_75 = nimIcheckB(IL64(1), IL64(7));
        NU64 b_2 = h_1.a[X60Qx_75];
        NI64 X60Qx_76 = nimIcheckB(IL64(2), IL64(7));
        NU64 c_1 = h_1.a[X60Qx_76];
        NI64 X60Qx_77 = nimIcheckB(IL64(3), IL64(7));
        NU64 d_1 = h_1.a[X60Qx_77];
        NI64 X60Qx_78 = nimIcheckB(IL64(4), IL64(7));
        NU64 e_1 = h_1.a[X60Qx_78];
        NI64 X60Qx_79 = nimIcheckB(IL64(5), IL64(7));
        NU64 f_1 = h_1.a[X60Qx_79];
        NI64 X60Qx_80 = nimIcheckB(IL64(6), IL64(7));
        NU64 g_1 = h_1.a[X60Qx_80];
        NI64 X60Qx_81 = nimIcheckB(IL64(7), IL64(7));
        NU64 hh_1 = h_1.a[X60Qx_81];
        {
          NI64 X60Qlf_30 = IL64(0);
          NI64 X60Qlf_31 = IL64(80);
          NI64 X60Qlf_32 = X60Qlf_30;
          {
            while (X60Qlf_32 < X60Qlf_31){
              {
                NU64 X60Qx_82 = rotr64_0_shahpid5u(e_1, IL64(14));
                NU64 X60Qx_83 = rotr64_0_shahpid5u(e_1, IL64(18));
                NU64 X60Qx_84 = rotr64_0_shahpid5u(e_1, IL64(41));
                NU64 X60Qii_19 = ((NU64)(((NU64)(X60Qx_82 ^ X60Qx_83)) ^ X60Qx_84));
                NU64 X60Qii_20 = ((NU64)(((NU64)(e_1 & f_1)) ^ ((NU64)(((NU64) ~ e_1) & g_1))));
                NI64 X60Qx_85 = nimIcheckB(X60Qlf_32, IL64(79));
                NI64 X60Qx_86 = nimIcheckB(X60Qlf_32, IL64(79));
                NU64 X60Qii_21 = ((NU64)(((NU64)(((NU64)(((NU64)(hh_1 + X60Qii_19)) + X60Qii_20)) + sha512K_0_shahpid5u.a[X60Qx_85])) + w_1.a[X60Qx_86]));
                NU64 X60Qx_87 = rotr64_0_shahpid5u(a_3, IL64(28));
                NU64 X60Qx_88 = rotr64_0_shahpid5u(a_3, IL64(34));
                NU64 X60Qx_89 = rotr64_0_shahpid5u(a_3, IL64(39));
                NU64 X60Qii_22 = ((NU64)(((NU64)(X60Qx_87 ^ X60Qx_88)) ^ X60Qx_89));
                NU64 X60Qii_23 = ((NU64)(((NU64)(((NU64)(a_3 & b_2)) ^ ((NU64)(a_3 & c_1)))) ^ ((NU64)(b_2 & c_1))));
                NU64 X60Qii_24 = ((NU64)(X60Qii_22 + X60Qii_23));
                hh_1 = g_1;
                g_1 = f_1;
                f_1 = e_1;
                e_1 = ((NU64)(d_1 + X60Qii_21));
                d_1 = c_1;
                c_1 = b_2;
                b_2 = a_3;
                a_3 = ((NU64)(X60Qii_21 + X60Qii_24));}
              inc_1_Irn1g7r1_shahpid5u((&X60Qlf_32));}}
          whileStmtLabel_18: ;}
        forStmtLabel_17: ;
        NI64 X60Qx_90 = nimIcheckB(IL64(0), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_90]), a_3);
        NI64 X60Qx_91 = nimIcheckB(IL64(1), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_91]), b_2);
        NI64 X60Qx_92 = nimIcheckB(IL64(2), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_92]), c_1);
        NI64 X60Qx_93 = nimIcheckB(IL64(3), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_93]), d_1);
        NI64 X60Qx_94 = nimIcheckB(IL64(4), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_94]), e_1);
        NI64 X60Qx_95 = nimIcheckB(IL64(5), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_95]), f_1);
        NI64 X60Qx_96 = nimIcheckB(IL64(6), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_96]), g_1);
        NI64 X60Qx_97 = nimIcheckB(IL64(7), IL64(7));
        plusQeQ_0_Iar0t5x_shahpid5u((&h_1.a[X60Qx_97]), hh_1);
        plusQeQ_0_Ihg6mz11_shahpid5u((&blockStart_1), IL64(128));}
      else {
        break;}}}
  whileStmtLabel_6: ;
  result_3 = h_1;
  eQdestroy_1_Ijx6eoq_shahpid5u(data_1);
  return result_3;
  eQdestroy_1_Ijx6eoq_shahpid5u(data_1);
  return result_3;}
X60Qt_0_IAarrayAuS8ZS64_shahpid5u sha512_0_shahpid5u(openArray_0_Is74e021_shahpid5u msg_2){
  X60Qt_0_IAarrayAuS8ZS64_shahpid5u result_4;
  X60Qt_0_IAarrayAuS64ZS8_shahpid5u iv_1 = (X60Qt_0_IAarrayAuS64ZS8_shahpid5u){
    .a = {
      ((NU64)7640891576956012808ull), ((NU64)13503953896175478587ull), ((NU64)4354685564936845355ull), ((NU64)11912009170470909681ull), ((NU64)5840696475078001361ull), ((NU64)11170449401992604703ull), ((NU64)2270897969802886507ull), ((NU64)6620516959819538809ull)}}
  ;
  X60Qt_0_IAarrayAuS64ZS8_shahpid5u h_2 = sha512Core_0_shahpid5u(msg_2, (&iv_1));
  {
    NI64 X60Qlf_33 = IL64(0);
    NI64 X60Qlf_34 = IL64(8);
    NI64 X60Qlf_35 = X60Qlf_33;
    {
      while (X60Qlf_35 < X60Qlf_34){
        {
          NI64 X60Qx_98 = nimIcheckB(((NI64)(X60Qlf_35 * IL64(8))), IL64(63));
          NI64 X60Qx_99 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_98] = ((NU8)((NU64)(((NU64)(h_2.a[X60Qx_99] >> ((NU64)56ull))) & ((NU64)255ull))));
          NI64 X60Qx_100 = nimIcheckB(((NI64)(((NI64)(X60Qlf_35 * IL64(8))) + IL64(1))), IL64(63));
          NI64 X60Qx_101 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_100] = ((NU8)((NU64)(((NU64)(h_2.a[X60Qx_101] >> ((NU64)48ull))) & ((NU64)255ull))));
          NI64 X60Qx_102 = nimIcheckB(((NI64)(((NI64)(X60Qlf_35 * IL64(8))) + IL64(2))), IL64(63));
          NI64 X60Qx_103 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_102] = ((NU8)((NU64)(((NU64)(h_2.a[X60Qx_103] >> ((NU64)40ull))) & ((NU64)255ull))));
          NI64 X60Qx_104 = nimIcheckB(((NI64)(((NI64)(X60Qlf_35 * IL64(8))) + IL64(3))), IL64(63));
          NI64 X60Qx_105 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_104] = ((NU8)((NU64)(((NU64)(h_2.a[X60Qx_105] >> ((NU64)32ull))) & ((NU64)255ull))));
          NI64 X60Qx_106 = nimIcheckB(((NI64)(((NI64)(X60Qlf_35 * IL64(8))) + IL64(4))), IL64(63));
          NI64 X60Qx_107 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_106] = ((NU8)((NU64)(((NU64)(h_2.a[X60Qx_107] >> ((NU64)24ull))) & ((NU64)255ull))));
          NI64 X60Qx_108 = nimIcheckB(((NI64)(((NI64)(X60Qlf_35 * IL64(8))) + IL64(5))), IL64(63));
          NI64 X60Qx_109 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_108] = ((NU8)((NU64)(((NU64)(h_2.a[X60Qx_109] >> ((NU64)16ull))) & ((NU64)255ull))));
          NI64 X60Qx_110 = nimIcheckB(((NI64)(((NI64)(X60Qlf_35 * IL64(8))) + IL64(6))), IL64(63));
          NI64 X60Qx_111 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_110] = ((NU8)((NU64)(((NU64)(h_2.a[X60Qx_111] >> ((NU64)8ull))) & ((NU64)255ull))));
          NI64 X60Qx_112 = nimIcheckB(((NI64)(((NI64)(X60Qlf_35 * IL64(8))) + IL64(7))), IL64(63));
          NI64 X60Qx_113 = nimIcheckB(X60Qlf_35, IL64(7));
          result_4.a[X60Qx_112] = ((NU8)((NU64)(h_2.a[X60Qx_113] & ((NU64)255ull))));}
        inc_1_Irn1g7r1_shahpid5u((&X60Qlf_35));}}
    whileStmtLabel_1: ;}
  forStmtLabel_0: ;
  return result_4;}
X60Qt_0_IAarrayAuS8ZS48_shahpid5u sha384_0_shahpid5u(openArray_0_Is74e021_shahpid5u msg_3){
  X60Qt_0_IAarrayAuS8ZS48_shahpid5u result_5;
  X60Qt_0_IAarrayAuS64ZS8_shahpid5u iv_2 = (X60Qt_0_IAarrayAuS64ZS8_shahpid5u){
    .a = {
      ((NU64)14680500436340154072ull), ((NU64)7105036623409894663ull), ((NU64)10473403895298186519ull), ((NU64)1526699215303891257ull), ((NU64)7436329637833083697ull), ((NU64)10282925794625328401ull), ((NU64)15784041429090275239ull), ((NU64)5167115440072839076ull)}}
  ;
  X60Qt_0_IAarrayAuS64ZS8_shahpid5u h_3 = sha512Core_0_shahpid5u(msg_3, (&iv_2));
  {
    NI64 X60Qlf_36 = IL64(0);
    NI64 X60Qlf_37 = IL64(6);
    NI64 X60Qlf_38 = X60Qlf_36;
    {
      while (X60Qlf_38 < X60Qlf_37){
        {
          NI64 X60Qx_114 = nimIcheckB(((NI64)(X60Qlf_38 * IL64(8))), IL64(47));
          NI64 X60Qx_115 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_114] = ((NU8)((NU64)(((NU64)(h_3.a[X60Qx_115] >> ((NU64)56ull))) & ((NU64)255ull))));
          NI64 X60Qx_116 = nimIcheckB(((NI64)(((NI64)(X60Qlf_38 * IL64(8))) + IL64(1))), IL64(47));
          NI64 X60Qx_117 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_116] = ((NU8)((NU64)(((NU64)(h_3.a[X60Qx_117] >> ((NU64)48ull))) & ((NU64)255ull))));
          NI64 X60Qx_118 = nimIcheckB(((NI64)(((NI64)(X60Qlf_38 * IL64(8))) + IL64(2))), IL64(47));
          NI64 X60Qx_119 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_118] = ((NU8)((NU64)(((NU64)(h_3.a[X60Qx_119] >> ((NU64)40ull))) & ((NU64)255ull))));
          NI64 X60Qx_120 = nimIcheckB(((NI64)(((NI64)(X60Qlf_38 * IL64(8))) + IL64(3))), IL64(47));
          NI64 X60Qx_121 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_120] = ((NU8)((NU64)(((NU64)(h_3.a[X60Qx_121] >> ((NU64)32ull))) & ((NU64)255ull))));
          NI64 X60Qx_122 = nimIcheckB(((NI64)(((NI64)(X60Qlf_38 * IL64(8))) + IL64(4))), IL64(47));
          NI64 X60Qx_123 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_122] = ((NU8)((NU64)(((NU64)(h_3.a[X60Qx_123] >> ((NU64)24ull))) & ((NU64)255ull))));
          NI64 X60Qx_124 = nimIcheckB(((NI64)(((NI64)(X60Qlf_38 * IL64(8))) + IL64(5))), IL64(47));
          NI64 X60Qx_125 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_124] = ((NU8)((NU64)(((NU64)(h_3.a[X60Qx_125] >> ((NU64)16ull))) & ((NU64)255ull))));
          NI64 X60Qx_126 = nimIcheckB(((NI64)(((NI64)(X60Qlf_38 * IL64(8))) + IL64(6))), IL64(47));
          NI64 X60Qx_127 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_126] = ((NU8)((NU64)(((NU64)(h_3.a[X60Qx_127] >> ((NU64)8ull))) & ((NU64)255ull))));
          NI64 X60Qx_128 = nimIcheckB(((NI64)(((NI64)(X60Qlf_38 * IL64(8))) + IL64(7))), IL64(47));
          NI64 X60Qx_129 = nimIcheckB(X60Qlf_38, IL64(7));
          result_5.a[X60Qx_128] = ((NU8)((NU64)(h_3.a[X60Qx_129] & ((NU64)255ull))));}
        inc_1_Irn1g7r1_shahpid5u((&X60Qlf_38));}}
    whileStmtLabel_1: ;}
  forStmtLabel_0: ;
  return result_5;}
static inline NI64 len_6_Itc4yka_shahpid5u(openArray_0_Is74e021_shahpid5u a_4){
  NI64 result_6;
  result_6 = a_4.len_0;
  return result_6;}
seq_0_Incv1wn_shahpid5u newSeq_0_Ivbxvoi1_shahpid5u(NI64 size_1){
  seq_0_Incv1wn_shahpid5u result_7;
  if (size_1 == IL64(0)){
    result_7 = (seq_0_Incv1wn_shahpid5u){
      .len_0 = size_1, .data_0 = NIM_NIL}
    ;}
  else {
    NI64 memSize_0 = memSizeInBytes_0_Infw7m1_shahpid5u(size_1);
    void* X60Qx_130 = alloc_0_sysvq0asl(memSize_0);
    result_7 = (seq_0_Incv1wn_shahpid5u){
      .len_0 = size_1, .data_0 = ((NU8*)X60Qx_130)}
    ;
    if ((!(result_7.data_0 == NIM_NIL))){
      NI64 i_8 = IL64(0);
      {
        while (i_8 < size_1){
          result_7.data_0[i_8] = ((NU8)0ull);
          inc_1_Irn1g7r1_shahpid5u((&i_8));}}
      whileStmtLabel_0: ;}
    else {
      result_7.len_0 = IL64(0);
      oomHandler_0_sysvq0asl(memSize_0);}}
  return result_7;}
static inline NU8* getQ_10_Ikgj4ax_shahpid5u(openArray_0_Is74e021_shahpid5u x_8, NI64 idx_1){
  NB8 X60Qx_131;
  if (IL64(0) <= idx_1){
    X60Qx_131 = (idx_1 < x_8.len_0);}
  else {
    X60Qx_131 = NIM_FALSE;}
  if ((!X60Qx_131)){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 7939615443972402942ull, .more_0 = (&strlit_0_I5410009123728214703_shahpid5u)}
    );}
  NU8* result_8;
  result_8 = (&x_8.a_0[idx_1]);
  return result_8;}
static inline void putQ_7_Ipw0nqk1_shahpid5u(seq_0_Incv1wn_shahpid5u* s_4, NI64 i_10, NU8 elem_2){
  NB8 X60Qx_132;
  if (i_10 < (*s_4).len_0){
    X60Qx_132 = (IL64(0) <= i_10);}
  else {
    X60Qx_132 = NIM_FALSE;}
  if ((!X60Qx_132)){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 7939615443972402942ull, .more_0 = (&strlit_0_I17896528460403498414_shahpid5u)}
    );}
  (*s_4).data_0[i_10] = elem_2;}
static inline void add_0_Ibphvmo_shahpid5u(seq_0_Incv1wn_shahpid5u* s_5, NU8 elem_3){
  NI64 L_0 = (*s_5).len_0;
  NI64 X60Qx_133 = capInBytes_0_Iffahgv_shahpid5u((*s_5));
  if (X60Qx_133 < ((NI64)(((NI64)(L_0 * sizeof(NU8))) + sizeof(NU8)))){
    NB8 X60Qx_134 = resize_0_Iuiuhg71_shahpid5u(s_5, IL64(1));
    if ((!X60Qx_134)){
      return;}}
  inc_1_Irn1g7r1_shahpid5u((&(*s_5).len_0));
  (*s_5).data_0[L_0] = elem_3;}
static inline NI64 len_3_Izoe8zv_shahpid5u(seq_0_Incv1wn_shahpid5u s_7){
  NI64 result_9;
  result_9 = s_7.len_0;
  return result_9;}
static inline void minusQeQ_0_Isqosxa_shahpid5u(NI64* x_9, NI64 y_4){
  (*x_9) = ((NI64)((*x_9) - y_4));}
static inline NU8* getQ_7_Ig0r1051_shahpid5u(seq_0_Incv1wn_shahpid5u s_8, NI64 i_11){
  NB8 X60Qx_135;
  if (i_11 < s_8.len_0){
    X60Qx_135 = (IL64(0) <= i_11);}
  else {
    X60Qx_135 = NIM_FALSE;}
  if ((!X60Qx_135)){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 7939615443972402942ull, .more_0 = (&strlit_0_I16713941061949234674_shahpid5u)}
    );}
  NU8* result_10;
  result_10 = (&s_8.data_0[i_11]);
  return result_10;}
static inline void plusQeQ_0_Ih8llpb_shahpid5u(NU32* x_10, NU32 y_5){
  (*x_10) = ((NU32)((*x_10) + y_5));}
static inline void plusQeQ_0_Ihg6mz11_shahpid5u(NI64* x_11, NI64 y_6){
  (*x_11) = ((NI64)((*x_11) + y_6));}
static inline void plusQeQ_0_Iar0t5x_shahpid5u(NU64* x_12, NU64 y_7){
  (*x_12) = ((NU64)((*x_12) + y_7));}
static inline NI64 memSizeInBytes_0_Infw7m1_shahpid5u(NI64 size_3){
  NB8 LENGC_OVF_ = NIM_FALSE;
  NI64 result_11;
  NI64 X60QconstRefTemp_0;
  if (__builtin_smulll_overflow(size_3, sizeof(NU8), (long long int*)(&X60QconstRefTemp_0))){
    LENGC_OVF_ = LENGC_OVF_ || NIM_TRUE;}
  result_11 = X60QconstRefTemp_0;
  if (LENGC_OVF_){
    result_11 = ((NI64)IL64(9223372036854775807));}
  return result_11;}
static inline void inc_1_Irn1g7r1_shahpid5u(NI64* x_13){
  (*x_13) = ((NI64)((*x_13) + ((NI64)IL64(1))));}
static inline NI64 capInBytes_0_Iffahgv_shahpid5u(seq_0_Incv1wn_shahpid5u s_9){
  NI64 result_12;
  NI64 X60Qx_0;
  if ((!(s_9.data_0 == NIM_NIL))){
    NI64 X60Qx_136 = allocatedSize_0_sysvq0asl(((void*)((void*)s_9.data_0)));
    X60Qx_0 = X60Qx_136;}
  else {
    X60Qx_0 = IL64(0);}
  result_12 = X60Qx_0;
  return result_12;}
NB8 resize_0_Iuiuhg71_shahpid5u(seq_0_Incv1wn_shahpid5u* dest_1, NI64 addedElements_1){
  NB8 result_13;
  NI64 X60Qx_137 = capInBytes_0_Iffahgv_shahpid5u((*dest_1));
  NI64 oldCap_0 = ((NI64)(X60Qx_137 / sizeof(NU8)));
  NI64 newCap_0 = recalcCap_0_sysvq0asl(oldCap_0, addedElements_1);
  NI64 memSize_1 = memSizeInBytes_0_Infw7m1_shahpid5u(newCap_0);
  void* X60Qx_138 = realloc_0_sysvq0asl(((void*)((void*)(*dest_1).data_0)), memSize_1);
  (*dest_1).data_0 = ((NU8*)X60Qx_138);
  if ((*dest_1).data_0 == NIM_NIL){
    (*dest_1).len_0 = IL64(0);
    oomHandler_0_sysvq0asl(memSize_1);
    result_13 = NIM_FALSE;}
  else {
    result_13 = NIM_TRUE;}
  return result_13;}
void eQdestroy_1_Ijx6eoq_shahpid5u(seq_0_Incv1wn_shahpid5u s_12){
  if ((!(s_12.data_0 == NIM_NIL))){
    NI64 i_12 = IL64(0);
    {
      while (i_12 < s_12.len_0){
        inc_1_Irn1g7r1_shahpid5u((&i_12));}}
    whileStmtLabel_0: ;
    dealloc_0_sysvq0asl(((void*)((void*)s_12.data_0)));}}
static inline void eQwasMoved_1_I861g1c1_shahpid5u(seq_0_Incv1wn_shahpid5u* s_13){
  (*s_13).len_0 = IL64(0);
  (*s_13).data_0 = NIM_NIL;}
void X60Qini_0_shahpid5u(void){
  if (X60QiniGuard_0_shahpid5u){
    return;}
  X60QiniGuard_0_shahpid5u = NIM_TRUE;
  X60Qini_0_sysvq0asl();}
static inline NI64 nimIcheckB(NI64 i_19, NI64 b_19){
  NI64 result_121;
  NB8 X60Qx_186;
  if (IL64(0) <= i_19){
    X60Qx_186 = (i_19 <= b_19);}
  else {
    X60Qx_186 = NIM_FALSE;}
  if (X60Qx_186){
    result_121 = i_19;}
  else {
    result_121 = IL64(0);
    raiseIndexError3_0_Ice8haj1_sysvq0asl(i_19, IL64(0), b_19);}
  return result_121;}
static inline NI64 recalcCap_0_sysvq0asl(NI64 oldCap_0, NI64 addedElements_0){
  NB8 LENGC_OVF_ = NIM_FALSE;
  NI64 result_47;
  NI64 X60QconstRefTemp_0;
  if (__builtin_saddll_overflow(oldCap_0, addedElements_0, (long long int*)(&X60QconstRefTemp_0))){
    LENGC_OVF_ = LENGC_OVF_ || NIM_TRUE;}
  NI64 requiredLen_0 = X60QconstRefTemp_0;
  if (LENGC_OVF_){
    result_47 = ((NI64)IL64(9223372036854775807));}
  else {
    NI64 X60QconstRefTemp_1;
    if (__builtin_saddll_overflow(oldCap_0, ((NI64)(((NI64)oldCap_0) >> ((NU64)IL64(1)))), (long long int*)(&X60QconstRefTemp_1))){
      LENGC_OVF_ = LENGC_OVF_ || NIM_TRUE;}
    result_47 = X60QconstRefTemp_1;
    if (LENGC_OVF_){
      result_47 = requiredLen_0;}
    else {
      NI64 X60Qx_78 = max_3_sysvq0asl(result_47, requiredLen_0);
      result_47 = X60Qx_78;}}
  return result_47;}
static inline NI64 max_3_sysvq0asl(NI64 x_212, NI64 y_169){
  NI64 result_13;
  NI64 X60Qx_9;
  if (y_169 <= x_212){
    X60Qx_9 = x_212;}
  else {
    X60Qx_9 = y_169;}
  result_13 = X60Qx_9;
  return result_13;}
