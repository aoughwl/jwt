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
NIM_THREADVAR NB8 LENGC_ERR_;
#include <stdio.h>
typedef struct LongString_0_sysvq0asl LongString_0_sysvq0asl;
typedef struct openArray_0_Is74e021_shahpid5u{
  NU8* a_0;
  NI64 len_0;}
openArray_0_Is74e021_shahpid5u;
typedef struct seq_0_Incv1wn_shahpid5u{
  NI64 len_0;
  NU8* data_0;}
seq_0_Incv1wn_shahpid5u;
typedef struct openArray_0_Ijk0jkw1_sysvq0asl{
  NC8* a_0;
  NI64 len_0;}
openArray_0_Ijk0jkw1_sysvq0asl;
typedef struct X60Qt_0_IAtupleAiS64ZAmutAuS8_tesz3o8wy1{
  NI64 fld_0;
  NU8* fld_1;}
X60Qt_0_IAtupleAiS64ZAmutAuS8_tesz3o8wy1;
typedef struct X60Qt_0_IAtupleAiS64ZAmutAcS8_tesz3o8wy1{
  NI64 fld_0;
  NC8* fld_1;}
X60Qt_0_IAtupleAiS64ZAmutAcS8_tesz3o8wy1;
typedef struct X60Qt_0_IAarrayAuS8ZS32_shahpid5u{
  NU8 a[IL64(32)];}
X60Qt_0_IAarrayAuS8ZS32_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS8ZS48_shahpid5u{
  NU8 a[IL64(48)];}
X60Qt_0_IAarrayAuS8ZS48_shahpid5u;
typedef struct X60Qt_0_IAarrayAuS8ZS64_shahpid5u{
  NU8 a[IL64(64)];}
X60Qt_0_IAarrayAuS8ZS64_shahpid5u;
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
static inline NI64 len_6_Iroq7kd1_tesz3o8wy1(openArray_0_Ijk0jkw1_sysvq0asl a_7);
static inline NU8* rawData_0_Ihjhfzs_tesz3o8wy1(seq_0_Incv1wn_shahpid5u s_6);
static inline void nimStrWasMoved(string_0_sysvq0asl* s_38);
static inline void nimStrDestroy(string_0_sysvq0asl s_39);
static inline NI64 len_6_Itc4yka_shahpid5u(openArray_0_Is74e021_shahpid5u a_4);
extern string_0_sysvq0asl newString_0_sysvq0asl(NI64 len_2);
static inline NU8* getQ_10_Ikgj4ax_shahpid5u(openArray_0_Is74e021_shahpid5u x_8, NI64 idx_1);
static inline NC8 getQ_9_sysvq0asl(string_0_sysvq0asl s_52, NI64 i_14);
static inline void putQ_9_sysvq0asl(string_0_sysvq0asl* s_53, NI64 i_15, NC8 c_1);
static inline void inc_1_Irn1g7r1_shahpid5u(NI64* x_13);
static inline void eQwasMoved_1_I861g1c1_shahpid5u(seq_0_Incv1wn_shahpid5u* s_13);
extern void eQdestroy_1_Ijx6eoq_shahpid5u(seq_0_Incv1wn_shahpid5u s_12);
static inline NI64 len_4_sysvq0asl(string_0_sysvq0asl s_32);
extern seq_0_Incv1wn_shahpid5u newSeq_0_Ivbxvoi1_shahpid5u(NI64 size_1);
static inline openArray_0_Ijk0jkw1_sysvq0asl toOpenArray_2_sysvq0asl(string_0_sysvq0asl* s_65);
static inline NC8* getQ_10_I5nt6we_sysvq0asl(openArray_0_Ijk0jkw1_sysvq0asl x_363, NI64 idx_5);
static inline void putQ_7_Ipw0nqk1_shahpid5u(seq_0_Incv1wn_shahpid5u* s_4, NI64 i_10, NU8 elem_2);
extern void X60Qini_0_sysvq0asl(void);
extern void X60Qini_0_assy765wm(void);
extern void X60Qini_0_syn1lfpjv(void);
extern void X60Qini_0_shahpid5u(void);
extern X60Qt_0_IAarrayAuS8ZS32_shahpid5u sha256_0_shahpid5u(openArray_0_Is74e021_shahpid5u msg_0);
static inline NB8 eqQ_20_sysvq0asl(string_0_sysvq0asl a_14, string_0_sysvq0asl b_10);
extern void write_0_syn1lfpjv(FILE* f_6, string_0_sysvq0asl s_0);
extern LongString_0_sysvq0asl const strlit_0_I14676000009897902695_assy765wm;
extern void write_7_syn1lfpjv(FILE* f_13, NC8 c_1);
extern void quit_0_syn1lfpjv(NI64 value_0);
extern X60Qt_0_IAarrayAuS8ZS48_shahpid5u sha384_0_shahpid5u(openArray_0_Is74e021_shahpid5u msg_3);
extern X60Qt_0_IAarrayAuS8ZS64_shahpid5u sha512_0_shahpid5u(openArray_0_Is74e021_shahpid5u msg_2);
extern void nimFlushStdStreams(void);
static inline NB8 arcDec_0_sysvq0asl(NI64* memLoc_1);
extern void dealloc_0_sysvq0asl(void* p_10);
extern void panic_0_sysvq0asl(string_0_sysvq0asl s_68);
extern LongString_0_sysvq0asl const strlit_0_I5410009123728214703_shahpid5u;
extern LongString_0_sysvq0asl const strlit_0_I13232578976134542734_sysvq0asl;
extern LongString_0_sysvq0asl const strlit_0_I13343674595065056869_sysvq0asl;
extern void prepareMutation_0_sysvq0asl(string_0_sysvq0asl* s_44);
static inline NC8* readRawData_0_sysvq0asl(string_0_sysvq0asl* s_37, NI64 start_0);
extern LongString_0_sysvq0asl const strlit_0_I17896528460403498414_shahpid5u;
extern NB8 equalStrings_0_sysvq0asl(string_0_sysvq0asl a_13, string_0_sysvq0asl b_9);
LongString_0_sysvq0asl const strlit_0_I6105018409752412263_tesz3o8wy1 = {
  .fullLen_0 = IL64(16), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "0123456789abcdef"}
;
LongString_0_sysvq0asl const strlit_0_I3217033723331308564_tesz3o8wy1 = {
  .fullLen_0 = IL64(64), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"}
;
LongString_0_sysvq0asl const strlit_0_I6212282376496824396_tesz3o8wy1 = {
  .fullLen_0 = IL64(64), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"}
;
LongString_0_sysvq0asl const strlit_0_I4425232836796392125_tesz3o8wy1 = {
  .fullLen_0 = IL64(10), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "sha256: OK"}
;
LongString_0_sysvq0asl const strlit_0_I7171174049340436439_tesz3o8wy1 = {
  .fullLen_0 = IL64(96), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7"}
;
LongString_0_sysvq0asl const strlit_0_I565338032092185458_tesz3o8wy1 = {
  .fullLen_0 = IL64(10), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "sha384: OK"}
;
LongString_0_sysvq0asl const strlit_0_I3306965325246572757_tesz3o8wy1 = {
  .fullLen_0 = IL64(128), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f"}
;
LongString_0_sysvq0asl const strlit_0_I9485178145151000755_tesz3o8wy1 = {
  .fullLen_0 = IL64(10), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "sha512: OK"}
;
LongString_0_sysvq0asl const strlit_0_I2866654086288641348_tesz3o8wy1 = {
  .fullLen_0 = IL64(23), .rc_0 = IL64(0), .capImpl_0 = IL64(0), .data_0 = "all sha2 vectors passed"}
;
static string_0_sysvq0asl const hexChars_0 = {
  .bytes_0 = 3906085646303834366ull, .more_0 = (&strlit_0_I6105018409752412263_tesz3o8wy1)}
;
NB8 X60QiniGuard_0_tesz3o8wy1;
NI32 cmdCount;
NC8** cmdLine;
NC8** nimEnviron;
string_0_sysvq0asl toHex_0_tesz3o8wy1(openArray_0_Is74e021_shahpid5u data_0){
  string_0_sysvq0asl result_0;
  nimStrWasMoved((&result_0));
  nimStrDestroy(result_0);
  NI64 X60Qx_4 = len_6_Itc4yka_shahpid5u(data_0);
  string_0_sysvq0asl X60Qx_5 = newString_0_sysvq0asl(((NI64)(X60Qx_4 * IL64(2))));
  result_0 = X60Qx_5;
  {
    openArray_0_Is74e021_shahpid5u X60Qlf_0 = data_0;
    NI64 X60Qlf_1 = IL64(0);
    {
      while (NIM_TRUE){
        NI64 X60Qx_6 = len_6_Itc4yka_shahpid5u(X60Qlf_0);
        if (X60Qlf_1 < X60Qx_6){
          {
            NU8* X60Qx_7 = getQ_10_Ikgj4ax_shahpid5u(X60Qlf_0, X60Qlf_1);
            X60Qt_0_IAtupleAiS64ZAmutAuS8_tesz3o8wy1 X60Qii_2 = (X60Qt_0_IAtupleAiS64ZAmutAuS8_tesz3o8wy1){
              .fld_0 = X60Qlf_1, .fld_1 = X60Qx_7}
            ;
            NI64 i_0 = X60Qii_2.fld_0;
            NU8* b_0 = X60Qii_2.fld_1;
            NC8 X60Qx_8 = getQ_9_sysvq0asl((string_0_sysvq0asl){
              .bytes_0 = 3906085646303834366ull, .more_0 = (&strlit_0_I6105018409752412263_tesz3o8wy1)}
            , ((NI64)((NU8)((*b_0) >> IL64(4)))));
            putQ_9_sysvq0asl((&result_0), ((NI64)(i_0 * IL64(2))), X60Qx_8);
            NC8 X60Qx_9 = getQ_9_sysvq0asl((string_0_sysvq0asl){
              .bytes_0 = 3906085646303834366ull, .more_0 = (&strlit_0_I6105018409752412263_tesz3o8wy1)}
            , ((NI64)((NU8)((*b_0) & ((NU8)15ull)))));
            putQ_9_sysvq0asl((&result_0), ((NI64)(((NI64)(i_0 * IL64(2))) + IL64(1))), X60Qx_9);}
          inc_1_Irn1g7r1_shahpid5u((&X60Qlf_1));}
        else {
          break;}}}
    whileStmtLabel_1: ;}
  forStmtLabel_0: ;
  return result_0;}
seq_0_Incv1wn_shahpid5u bytesOf_0_tesz3o8wy1(string_0_sysvq0asl s_0){
  seq_0_Incv1wn_shahpid5u result_1;
  eQwasMoved_1_I861g1c1_shahpid5u((&result_1));
  eQdestroy_1_Ijx6eoq_shahpid5u(result_1);
  NI64 X60Qx_10 = len_4_sysvq0asl(s_0);
  seq_0_Incv1wn_shahpid5u X60Qx_11 = newSeq_0_Ivbxvoi1_shahpid5u(X60Qx_10);
  result_1 = X60Qx_11;
  {
    openArray_0_Ijk0jkw1_sysvq0asl X60Qlf_2 = toOpenArray_2_sysvq0asl((&s_0));
    NI64 X60Qlf_3 = IL64(0);
    {
      while (NIM_TRUE){
        NI64 X60Qx_12 = len_6_Iroq7kd1_tesz3o8wy1(X60Qlf_2);
        if (X60Qlf_3 < X60Qx_12){
          {
            NC8* X60Qx_13 = getQ_10_I5nt6we_sysvq0asl(X60Qlf_2, X60Qlf_3);
            X60Qt_0_IAtupleAiS64ZAmutAcS8_tesz3o8wy1 X60Qii_2 = (X60Qt_0_IAtupleAiS64ZAmutAcS8_tesz3o8wy1){
              .fld_0 = X60Qlf_3, .fld_1 = X60Qx_13}
            ;
            NI64 i_1 = X60Qii_2.fld_0;
            NC8* c_0 = X60Qii_2.fld_1;
            putQ_7_Ipw0nqk1_shahpid5u((&result_1), i_1, ((NU8)(*c_0)));}
          inc_1_Irn1g7r1_shahpid5u((&X60Qlf_3));}
        else {
          break;}}}
    whileStmtLabel_1: ;}
  forStmtLabel_0: ;
  return result_1;}
static inline openArray_0_Is74e021_shahpid5u toOpenArray_1_Itrkyf61_tesz3o8wy1(seq_0_Incv1wn_shahpid5u s_4){
  openArray_0_Is74e021_shahpid5u result_4;
  NU8* X60Qx_28 = rawData_0_Ihjhfzs_tesz3o8wy1(s_4);
  result_4 = (openArray_0_Is74e021_shahpid5u){
    .a_0 = X60Qx_28, .len_0 = s_4.len_0}
  ;
  return result_4;}
static inline openArray_0_Is74e021_shahpid5u toOpenArray_0_Iu7s8hm1_tesz3o8wy1(X60Qt_0_IAarrayAuS8ZS32_shahpid5u* x_6){
  openArray_0_Is74e021_shahpid5u result_5;
  openArray_0_Is74e021_shahpid5u X60Qx_0;
  if (((NI64)(((NI64)(((NI64)((NI64)IL64(31))) - ((NI64)((NI64)IL64(0))))) + IL64(1))) == IL64(0)){
    X60Qx_0 = (openArray_0_Is74e021_shahpid5u){
      .a_0 = NIM_NIL, .len_0 = IL64(0)}
    ;}
  else {
    X60Qx_0 = (openArray_0_Is74e021_shahpid5u){
      .a_0 = ((NU8*)(&(*x_6))), .len_0 = ((NI64)(((NI64)(((NI64)((NI64)IL64(31))) - ((NI64)((NI64)IL64(0))))) + IL64(1)))}
    ;}
  result_5 = X60Qx_0;
  return result_5;}
static inline openArray_0_Is74e021_shahpid5u toOpenArray_0_Inh1pts_tesz3o8wy1(X60Qt_0_IAarrayAuS8ZS48_shahpid5u* x_7){
  openArray_0_Is74e021_shahpid5u result_6;
  openArray_0_Is74e021_shahpid5u X60Qx_1;
  if (((NI64)(((NI64)(((NI64)((NI64)IL64(47))) - ((NI64)((NI64)IL64(0))))) + IL64(1))) == IL64(0)){
    X60Qx_1 = (openArray_0_Is74e021_shahpid5u){
      .a_0 = NIM_NIL, .len_0 = IL64(0)}
    ;}
  else {
    X60Qx_1 = (openArray_0_Is74e021_shahpid5u){
      .a_0 = ((NU8*)(&(*x_7))), .len_0 = ((NI64)(((NI64)(((NI64)((NI64)IL64(47))) - ((NI64)((NI64)IL64(0))))) + IL64(1)))}
    ;}
  result_6 = X60Qx_1;
  return result_6;}
static inline openArray_0_Is74e021_shahpid5u toOpenArray_0_Ihotbaj_tesz3o8wy1(X60Qt_0_IAarrayAuS8ZS64_shahpid5u* x_8){
  openArray_0_Is74e021_shahpid5u result_7;
  openArray_0_Is74e021_shahpid5u X60Qx_2;
  if (((NI64)(((NI64)(((NI64)((NI64)IL64(63))) - ((NI64)((NI64)IL64(0))))) + IL64(1))) == IL64(0)){
    X60Qx_2 = (openArray_0_Is74e021_shahpid5u){
      .a_0 = NIM_NIL, .len_0 = IL64(0)}
    ;}
  else {
    X60Qx_2 = (openArray_0_Is74e021_shahpid5u){
      .a_0 = ((NU8*)(&(*x_8))), .len_0 = ((NI64)(((NI64)(((NI64)((NI64)IL64(63))) - ((NI64)((NI64)IL64(0))))) + IL64(1)))}
    ;}
  result_7 = X60Qx_2;
  return result_7;}
static inline NI64 len_6_Iroq7kd1_tesz3o8wy1(openArray_0_Ijk0jkw1_sysvq0asl a_7){
  NI64 result_10;
  result_10 = a_7.len_0;
  return result_10;}
static inline NU8* rawData_0_Ihjhfzs_tesz3o8wy1(seq_0_Incv1wn_shahpid5u s_6){
  NU8* result_12;
  result_12 = s_6.data_0;
  return result_12;}
void X60Qini_0_tesz3o8wy1(void){
  if (X60QiniGuard_0_tesz3o8wy1){
    return;}
  X60QiniGuard_0_tesz3o8wy1 = NIM_TRUE;
  X60Qini_0_sysvq0asl();
  X60Qini_0_assy765wm();
  X60Qini_0_syn1lfpjv();
  X60Qini_0_shahpid5u();
  seq_0_Incv1wn_shahpid5u X60Qtmp_1 = bytesOf_0_tesz3o8wy1((string_0_sysvq0asl){
    .bytes_0 = 1667391747ull, .more_0 = NIM_NIL}
  );
  openArray_0_Is74e021_shahpid5u X60Qx_14 = toOpenArray_1_Itrkyf61_tesz3o8wy1(X60Qtmp_1);
  X60Qt_0_IAarrayAuS8ZS32_shahpid5u X60QconstRefTemp_0 = sha256_0_shahpid5u(X60Qx_14);
  openArray_0_Is74e021_shahpid5u X60Qx_15 = toOpenArray_0_Iu7s8hm1_tesz3o8wy1((&X60QconstRefTemp_0));
  string_0_sysvq0asl X60Qtmp_0 = toHex_0_tesz3o8wy1(X60Qx_15);
  NB8 X60Qx_16 = eqQ_20_sysvq0asl(X60Qtmp_0, (string_0_sysvq0asl){
    .bytes_0 = 7076897981976371966ull, .more_0 = (&strlit_0_I3217033723331308564_tesz3o8wy1)}
  );
  if ((!X60Qx_16)){
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 8390880602273963006ull, .more_0 = (&strlit_0_I14676000009897902695_assy765wm)}
    );
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 0ull, .more_0 = NIM_NIL}
    );
    write_7_syn1lfpjv(stdout, (NC8)'\012');
    quit_0_syn1lfpjv(IL64(1));}
  seq_0_Incv1wn_shahpid5u X60Qtmp_3 = bytesOf_0_tesz3o8wy1((string_0_sysvq0asl){
    .bytes_0 = 0ull, .more_0 = NIM_NIL}
  );
  openArray_0_Is74e021_shahpid5u X60Qx_17 = toOpenArray_1_Itrkyf61_tesz3o8wy1(X60Qtmp_3);
  X60Qt_0_IAarrayAuS8ZS32_shahpid5u X60QconstRefTemp_1 = sha256_0_shahpid5u(X60Qx_17);
  openArray_0_Is74e021_shahpid5u X60Qx_18 = toOpenArray_0_Iu7s8hm1_tesz3o8wy1((&X60QconstRefTemp_1));
  string_0_sysvq0asl X60Qtmp_2 = toHex_0_tesz3o8wy1(X60Qx_18);
  NB8 X60Qx_19 = eqQ_20_sysvq0asl(X60Qtmp_2, (string_0_sysvq0asl){
    .bytes_0 = 3761740648218322430ull, .more_0 = (&strlit_0_I6212282376496824396_tesz3o8wy1)}
  );
  if ((!X60Qx_19)){
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 8390880602273963006ull, .more_0 = (&strlit_0_I14676000009897902695_assy765wm)}
    );
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 0ull, .more_0 = NIM_NIL}
    );
    write_7_syn1lfpjv(stdout, (NC8)'\012');
    quit_0_syn1lfpjv(IL64(1));}
  write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
    .bytes_0 = 4194598593441068030ull, .more_0 = (&strlit_0_I4425232836796392125_tesz3o8wy1)}
  );
  write_7_syn1lfpjv(stdout, (NC8)'\012');
  seq_0_Incv1wn_shahpid5u X60Qtmp_5 = bytesOf_0_tesz3o8wy1((string_0_sysvq0asl){
    .bytes_0 = 1667391747ull, .more_0 = NIM_NIL}
  );
  openArray_0_Is74e021_shahpid5u X60Qx_20 = toOpenArray_1_Itrkyf61_tesz3o8wy1(X60Qtmp_5);
  X60Qt_0_IAarrayAuS8ZS48_shahpid5u X60QconstRefTemp_2 = sha384_0_shahpid5u(X60Qx_20);
  openArray_0_Is74e021_shahpid5u X60Qx_21 = toOpenArray_0_Inh1pts_tesz3o8wy1((&X60QconstRefTemp_2));
  string_0_sysvq0asl X60Qtmp_4 = toHex_0_tesz3o8wy1(X60Qx_21);
  NB8 X60Qx_22 = eqQ_20_sysvq0asl(X60Qtmp_4, (string_0_sysvq0asl){
    .bytes_0 = 3689916149809701886ull, .more_0 = (&strlit_0_I7171174049340436439_tesz3o8wy1)}
  );
  if ((!X60Qx_22)){
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 8390880602273963006ull, .more_0 = (&strlit_0_I14676000009897902695_assy765wm)}
    );
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 0ull, .more_0 = NIM_NIL}
    );
    write_7_syn1lfpjv(stdout, (NC8)'\012');
    quit_0_syn1lfpjv(IL64(1));}
  write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
    .bytes_0 = 4194038946317497342ull, .more_0 = (&strlit_0_I565338032092185458_tesz3o8wy1)}
  );
  write_7_syn1lfpjv(stdout, (NC8)'\012');
  seq_0_Incv1wn_shahpid5u X60Qtmp_7 = bytesOf_0_tesz3o8wy1((string_0_sysvq0asl){
    .bytes_0 = 1667391747ull, .more_0 = NIM_NIL}
  );
  openArray_0_Is74e021_shahpid5u X60Qx_23 = toOpenArray_1_Itrkyf61_tesz3o8wy1(X60Qtmp_7);
  X60Qt_0_IAarrayAuS8ZS64_shahpid5u X60QconstRefTemp_3 = sha512_0_shahpid5u(X60Qx_23);
  openArray_0_Is74e021_shahpid5u X60Qx_24 = toOpenArray_0_Ihotbaj_tesz3o8wy1((&X60QconstRefTemp_3));
  string_0_sysvq0asl X60Qtmp_6 = toHex_0_tesz3o8wy1(X60Qx_24);
  NB8 X60Qx_25 = eqQ_20_sysvq0asl(X60Qtmp_6, (string_0_sysvq0asl){
    .bytes_0 = 7004561310258324734ull, .more_0 = (&strlit_0_I3306965325246572757_tesz3o8wy1)}
  );
  if ((!X60Qx_25)){
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 8390880602273963006ull, .more_0 = (&strlit_0_I14676000009897902695_assy765wm)}
    );
    write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
      .bytes_0 = 0ull, .more_0 = NIM_NIL}
    );
    write_7_syn1lfpjv(stdout, (NC8)'\012');
    quit_0_syn1lfpjv(IL64(1));}
  write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
    .bytes_0 = 4193468308372616190ull, .more_0 = (&strlit_0_I9485178145151000755_tesz3o8wy1)}
  );
  write_7_syn1lfpjv(stdout, (NC8)'\012');
  write_0_syn1lfpjv(stdout, (string_0_sysvq0asl){
    .bytes_0 = 7018986602352108030ull, .more_0 = (&strlit_0_I2866654086288641348_tesz3o8wy1)}
  );
  write_7_syn1lfpjv(stdout, (NC8)'\012');
  nimStrDestroy(X60Qtmp_6);
  eQdestroy_1_Ijx6eoq_shahpid5u(X60Qtmp_7);
  nimStrDestroy(X60Qtmp_4);
  eQdestroy_1_Ijx6eoq_shahpid5u(X60Qtmp_5);
  nimStrDestroy(X60Qtmp_2);
  eQdestroy_1_Ijx6eoq_shahpid5u(X60Qtmp_3);
  nimStrDestroy(X60Qtmp_0);
  eQdestroy_1_Ijx6eoq_shahpid5u(X60Qtmp_1);}
NI32 main(NI32 X60Qargc_0_tesz3o8wy1, char** X60Qargv_0_tesz3o8wy1, char** X60Qenvp_0_tesz3o8wy1){
  cmdCount = X60Qargc_0_tesz3o8wy1;
  cmdLine = ((NC8**)X60Qargv_0_tesz3o8wy1);
  nimEnviron = ((NC8**)X60Qenvp_0_tesz3o8wy1);
  X60Qini_0_tesz3o8wy1();
  nimFlushStdStreams();
  return IL64(0);}
static inline void nimStrWasMoved(string_0_sysvq0asl* s_38){
  (*s_38).bytes_0 = ((NU64)IL64(0));}
static inline void nimStrDestroy(string_0_sysvq0asl s_39){
  if (((NI64)(*((NU8*)(&s_39.bytes_0)))) == ((NI64)IL64(255))){
    NB8 X60Qx_80 = arcDec_0_sysvq0asl((&(*s_39.more_0).rc_0));
    if (X60Qx_80){
      dealloc_0_sysvq0asl(((void*)s_39.more_0));}}}
static inline NI64 len_6_Itc4yka_shahpid5u(openArray_0_Is74e021_shahpid5u a_4){
  NI64 result_6;
  result_6 = a_4.len_0;
  return result_6;}
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
static inline NC8 getQ_9_sysvq0asl(string_0_sysvq0asl s_52, NI64 i_14){
  NB8 X60Qx_116;
  NI64 X60Qx_117 = len_4_sysvq0asl(s_52);
  if (i_14 < X60Qx_117){
    X60Qx_116 = (IL64(0) <= i_14);}
  else {
    X60Qx_116 = NIM_FALSE;}
  if ((!X60Qx_116)){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 7939615443972402942ull, .more_0 = (&strlit_0_I13232578976134542734_sysvq0asl)}
    );}
  NC8 result_74;
  NC8 X60Qx_21;
  if (((NI64)IL64(14)) < ((NI64)(*((NU8*)(&s_52.bytes_0))))){
    X60Qx_21 = (*s_52.more_0).data_0[i_14];}
  else {
    X60Qx_21 = ((NC8*)((NU64)(((NU64)(&s_52.bytes_0)) + 1ull)))[i_14];}
  result_74 = X60Qx_21;
  return result_74;}
static inline void putQ_9_sysvq0asl(string_0_sysvq0asl* s_53, NI64 i_15, NC8 c_1){
  NB8 X60Qx_118;
  NI64 X60Qx_119 = len_4_sysvq0asl((*s_53));
  if (i_15 < X60Qx_119){
    X60Qx_118 = (IL64(0) <= i_15);}
  else {
    X60Qx_118 = NIM_FALSE;}
  if ((!X60Qx_118)){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 7939615443972402942ull, .more_0 = (&strlit_0_I13343674595065056869_sysvq0asl)}
    );}
  prepareMutation_0_sysvq0asl(s_53);
  if (((NI64)IL64(14)) < ((NI64)(*((NU8*)(&(*s_53).bytes_0))))){
    (*(*s_53).more_0).data_0[i_15] = c_1;
    if (i_15 < ((NI64)IL64(7))){
      ((NC8*)((NU64)(((NU64)(&(*s_53).bytes_0)) + 1ull)))[i_15] = c_1;}}
  else {
    ((NC8*)((NU64)(((NU64)(&(*s_53).bytes_0)) + 1ull)))[i_15] = c_1;}}
static inline void inc_1_Irn1g7r1_shahpid5u(NI64* x_13){
  (*x_13) = ((NI64)((*x_13) + ((NI64)IL64(1))));}
static inline void eQwasMoved_1_I861g1c1_shahpid5u(seq_0_Incv1wn_shahpid5u* s_13){
  (*s_13).len_0 = IL64(0);
  (*s_13).data_0 = NIM_NIL;}
static inline NI64 len_4_sysvq0asl(string_0_sysvq0asl s_32){
  NI64 result_60;
  result_60 = ((NI64)(*((NU8*)(&s_32.bytes_0))));
  if (((NI64)IL64(14)) < result_60){
    result_60 = (*s_32.more_0).fullLen_0;}
  return result_60;}
static inline openArray_0_Ijk0jkw1_sysvq0asl toOpenArray_2_sysvq0asl(string_0_sysvq0asl* s_65){
  openArray_0_Ijk0jkw1_sysvq0asl result_108;
  NC8* X60Qx_175 = readRawData_0_sysvq0asl((&(*s_65)), IL64(0));
  NI64 X60Qx_176 = len_4_sysvq0asl((*s_65));
  result_108 = (openArray_0_Ijk0jkw1_sysvq0asl){
    .a_0 = X60Qx_175, .len_0 = X60Qx_176}
  ;
  return result_108;}
static inline NC8* getQ_10_I5nt6we_sysvq0asl(openArray_0_Ijk0jkw1_sysvq0asl x_363, NI64 idx_5){
  NB8 X60Qx_310;
  if (IL64(0) <= idx_5){
    X60Qx_310 = (idx_5 < x_363.len_0);}
  else {
    X60Qx_310 = NIM_FALSE;}
  if ((!X60Qx_310)){
    panic_0_sysvq0asl((string_0_sysvq0asl){
      .bytes_0 = 7939615443972402942ull, .more_0 = (&strlit_0_I5410009123728214703_shahpid5u)}
    );}
  NC8* result_193;
  result_193 = (&x_363.a_0[idx_5]);
  return result_193;}
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
static inline NB8 eqQ_20_sysvq0asl(string_0_sysvq0asl a_14, string_0_sysvq0asl b_10){
  NB8 result_88;
  NB8 X60Qx_142 = equalStrings_0_sysvq0asl(a_14, b_10);
  result_88 = X60Qx_142;
  return result_88;}
static inline NB8 arcDec_0_sysvq0asl(NI64* memLoc_1){
  NB8 result_118;
  NI64 X60Qx_178 = __atomic_sub_fetch((&(*memLoc_1)), IL64(1), __ATOMIC_SEQ_CST);
  result_118 = (X60Qx_178 < IL64(0));
  return result_118;}
static inline NC8* readRawData_0_sysvq0asl(string_0_sysvq0asl* s_37, NI64 start_0){
  NC8* result_65;
  if (((NI64)IL64(14)) < ((NI64)(*((NU8*)(&(*s_37).bytes_0))))){
    result_65 = ((NC8*)((NU64)(((NU64)(&(*(*s_37).more_0).data_0[IL64(0)])) + ((NU64)start_0))));}
  else {
    result_65 = ((NC8*)((NU64)(((NU64)((NC8*)((NU64)(((NU64)(&(*s_37).bytes_0)) + 1ull)))) + ((NU64)start_0))));}
  return result_65;}
