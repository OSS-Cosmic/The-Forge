/* stb_ds.h - v0.67 - public domain data structures - Sean Barrett 2019
   This is a single-header-file library that provides easy-to-use
   dynamic arrays and hash tables for C (also works in C++).
   For a gentle introduction:
      http://nothings.org/stb_ds
   To use this library, do this in *one* C or C++ file:
      #define STB_DS_IMPLEMENTATION
      #include "stb_ds.h"
TABLE OF CONTENTS
  Table of Contents
  Compile-time options
  License
  Documentation
  Notes
  Notes - Dynamic arrays
  Notes - Hash maps
  Credits
COMPILE-TIME OPTIONS
  #define STBDS_NO_SHORT_NAMES
     This flag needs to be set globally.
     By default stb_ds exposes shorter function names that are not qualified
     with the "stbds_" prefix. If these names conflict with the names in your
     code, define this flag.
  #define STBDS_SIPHASH_2_4
     This flag only needs to be set in the file containing #define STB_DS_IMPLEMENTATION.
     By default stb_ds.h hashes using a weaker variant of SipHash and a custom hash for
     4- and 8-byte keys. On 64-bit platforms, you can define the above flag to force
     stb_ds.h to use specification-compliant SipHash-2-4 for all keys. Doing so makes
     hash table insertion about 20% slower on 4- and 8-byte keys, 5% slower on
     64-byte keys, and 10% slower on 256-byte keys on my test computer.
  #define STBDS_REALLOC(context,ptr,size) better_realloc
  #define STBDS_FREE(context,ptr)         better_free
     These defines only need to be set in the file containing #define STB_DS_IMPLEMENTATION.
     By default stb_ds uses stdlib realloc() and free() for memory management. You can
     substitute your own functions instead by defining these symbols. You must either
     define both, or neither. Note that at the moment, 'context' will always be NULL.
     @TODO add an array/hash initialization function that takes a memory context pointer.
  #define STBDS_UNIT_TESTS
     Defines a function stbds_unit_tests() that checks the functioning of the data structures.
  Note that on older versions of gcc (e.g. 5.x.x) you may need to build with '-std=c++0x'
     (or equivalentally '-std=c++11') when using anonymous structures as seen on the web
     page or in STBDS_UNIT_TESTS.
LICENSE
  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.
DOCUMENTATION
  Dynamic Arrays
    Non-function interface:
      Declare an empty dynamic array of type T
        T* foo = NULL;
      Access the i'th item of a dynamic array 'foo' of type T, T* foo:
        foo[i]
    Functions (actually macros)
      arrfree:
        void arrfree(T*);
          Frees the array.
      arrlen:
        ptrdiff_t arrlen(T*);
          Returns the number of elements in the array.
      arrlenu:
        size_t arrlenu(T*);
          Returns the number of elements in the array as an unsigned type.
      arrpop:
        T arrpop(T* a)
          Removes the final element of the array and returns it.
      arrput:
        T arrput(T* a, T b);
          Appends the item b to the end of array a. Returns b.
      arrins:
        T arrins(T* a, int p, T b);
          Inserts the item b into the middle of array a, into a[p],
          moving the rest of the array over. Returns b.
      arrinsn:
        void arrinsn(T* a, int p, int n);
          Inserts n uninitialized items into array a starting at a[p],
          moving the rest of the array over.
      arraddnptr:
        T* arraddnptr(T* a, int n)
          Appends n uninitialized items onto array at the end.
          Returns a pointer to the first uninitialized item added.
      arraddnindex:
        size_t arraddnindex(T* a, int n)
          Appends n uninitialized items onto array at the end.
          Returns the index of the first uninitialized item added.
      arrdel:
        void arrdel(T* a, int p);
          Deletes the element at a[p], moving the rest of the array over.
      arrdeln:
        void arrdeln(T* a, int p, int n);
          Deletes n elements starting at a[p], moving the rest of the array over.
      arrdelswap:
        void arrdelswap(T* a, int p);
          Deletes the element at a[p], replacing it with the element from
          the end of the array. O(1) performance.
      arrsetlen:
        void arrsetlen(T* a, int n);
          Changes the length of the array to n. Allocates uninitialized
          slots at the end if necessary.
      arrsetcap:
        size_t arrsetcap(T* a, int n);
          Sets the length of allocated storage to at least n. It will not
          change the length of the array.
      arrcap:
        size_t arrcap(T* a);
          Returns the number of total elements the array can contain without
          needing to be reallocated.
  Hash maps & String hash maps
    Given T is a structure type: struct { TK key; TV value; }. Note that some
    functions do not require TV value and can have other fields. For string
    hash maps, TK must be 'char *'.
    Special interface:
      stbds_rand_seed:
        void stbds_rand_seed(size_t seed);
          For security against adversarially chosen data, you should seed the
          library with a strong random number. Or at least seed it with time().
      stbds_hash_string:
        size_t stbds_hash_string(char *str, size_t seed);
          Returns a hash value for a string.
      stbds_hash_bytes:
        size_t stbds_hash_bytes(void *p, size_t len, size_t seed);
          These functions hash an arbitrary number of bytes. The function
          uses a custom hash for 4- and 8-byte data, and a weakened version
          of SipHash for everything else. On 64-bit platforms you can get
          specification-compliant SipHash-2-4 on all data by defining
          STBDS_SIPHASH_2_4, at a significant cost in speed.
    Non-function interface:
      Declare an empty hash map of type T
        T* foo = NULL;
      Access the i'th entry in a hash table T* foo:
        foo[i]
    Function interface (actually macros):
      hmfree
      shfree
        void hmfree(T*);
        void shfree(T*);
          Frees the hashmap and sets the pointer to NULL.
      hmlen
      shlen
        ptrdiff_t hmlen(T*)
        ptrdiff_t shlen(T*)
          Returns the number of elements in the hashmap.
      hmlenu
      shlenu
        size_t hmlenu(T*)
        size_t shlenu(T*)
          Returns the number of elements in the hashmap.
      hmgeti
      shgeti
      hmgeti_ts
        ptrdiff_t hmgeti(T*, TK key)
        ptrdiff_t shgeti(T*, char* key)
        ptrdiff_t hmgeti_ts(T*, TK key, ptrdiff_t tempvar)
          Returns the index in the hashmap which has the key 'key', or -1
          if the key is not present.
      hmget
      hmget_ts
      shget
        TV hmget(T*, TK key)
        TV shget(T*, char* key)
        TV hmget_ts(T*, TK key, ptrdiff_t tempvar)
          Returns the value corresponding to 'key' in the hashmap.
          The structure must have a 'value' field
      hmgets
      shgets
        T hmgets(T*, TK key)
        T shgets(T*, char* key)
          Returns the structure corresponding to 'key' in the hashmap.
      hmgetp
      shgetp
      hmgetp_ts
      hmgetp_null
      shgetp_null
        T* hmgetp(T*, TK key)
        T* shgetp(T*, char* key)
        T* hmgetp_ts(T*, TK key, ptrdiff_t tempvar)
        T* hmgetp_null(T*, TK key)
        T* shgetp_null(T*, char *key)
          Returns a pointer to the structure corresponding to 'key' in
          the hashmap. Functions ending in "_null" return NULL if the key
          is not present in the hashmap; the others return a pointer to a
          structure holding the default value (but not the searched-for key).
      hmdefault
      shdefault
        TV hmdefault(T*, TV value)
        TV shdefault(T*, TV value)
          Sets the default value for the hashmap, the value which will be
          returned by hmget/shget if the key is not present.
      hmdefaults
      shdefaults
        TV hmdefaults(T*, T item)
        TV shdefaults(T*, T item)
          Sets the default struct for the hashmap, the contents which will be
          returned by hmgets/shgets if the key is not present.
      hmput
      shput
        TV hmput(T*, TK key, TV value)
        TV shput(T*, char* key, TV value)
          Inserts a <key,value> pair into the hashmap. If the key is already
          present in the hashmap, updates its value.
      hmputs
      shputs
        T hmputs(T*, T item)
        T shputs(T*, T item)
          Inserts a struct with T.key into the hashmap. If the struct is already
          present in the hashmap, updates it.
      hmdel
      shdel
        int hmdel(T*, TK key)
        int shdel(T*, char* key)
          If 'key' is in the hashmap, deletes its entry and returns 1.
          Otherwise returns 0.
    Function interface (actually macros) for strings only:
      sh_new_strdup
        void sh_new_strdup(T*);
          Overwrites the existing pointer with a newly allocated
          string hashmap which will automatically allocate and free
          each string key using realloc/free
      sh_new_arena
        void sh_new_arena(T*);
          Overwrites the existing pointer with a newly allocated
          string hashmap which will automatically allocate each string
          key to a string arena. Every string key ever used by this
          hash table remains in the arena until the arena is freed.
          Additionally, any key which is deleted and reinserted will
          be allocated multiple times in the string arena.
NOTES
  * These data structures are realloc'd when they grow, and the macro
    "functions" write to the provided pointer. This means: (a) the pointer
    must be an lvalue, and (b) the pointer to the data structure is not
    stable, and you must maintain it the same as you would a realloc'd
    pointer. For example, if you pass a pointer to a dynamic array to a
    function which updates it, the function must return back the new
    pointer to the caller. This is the price of trying to do this in C.
  * The following are the only functions that are thread-safe on a single data
    structure, i.e. can be run in multiple threads simultaneously on the same
    data structure
        hmlen        shlen
        hmlenu       shlenu
        hmget_ts     shget_ts
        hmgeti_ts    shgeti_ts
        hmgets_ts    shgets_ts
  * You iterate over the contents of a dynamic array and a hashmap in exactly
    the same way, using arrlen/hmlen/shlen:
      for (i=0; i < arrlen(foo); ++i)
         ... foo[i] ...
  * All operations except arrins/arrdel are O(1) amortized, but individual
    operations can be slow, so these data structures may not be suitable
    for real time use. Dynamic arrays double in capacity as needed, so
    elements are copied an average of once. Hash tables double/halve
    their size as needed, with appropriate hysteresis to maintain O(1)
    performance.
NOTES - DYNAMIC ARRAY
  * If you know how long a dynamic array is going to be in advance, you can avoid
    extra memory allocations by using arrsetlen to allocate it to that length in
    advance and use foo[n] while filling it out, or arrsetcap to allocate the memory
    for that length and use arrput/arrpush as normal.
  * Unlike some other versions of the dynamic array, this version should
    be safe to use with strict-aliasing optimizations.
NOTES - HASH MAP
  * For compilers other than GCC and clang (e.g. Visual Studio), for hmput/hmget/hmdel
    and variants, the key must be an lvalue (so the macro can take the address of it).
    Extensions are used that eliminate this requirement if you're using C99 and later
    in GCC or clang, or if you're using C++ in GCC. But note that this can make your
    code less portable.
  * To test for presence of a key in a hashmap, just do 'hmgeti(foo,key) >= 0'.
  * The iteration order of your data in the hashmap is determined solely by the
    order of insertions and deletions. In particular, if you never delete, new
    keys are always added at the end of the array. This will be consistent
    across all platforms and versions of the library. However, you should not
    attempt to serialize the internal hash table, as the hash is not consistent
    between different platforms, and may change with future versions of the library.
  * Use sh_new_arena() for string hashmaps that you never delete from. Initialize
    with NULL if you're managing the memory for your strings, or your strings are
    never freed (at least until the hashmap is freed). Otherwise, use sh_new_strdup().
    @TODO: make an arena variant that garbage collects the strings with a trivial
    copy collector into a new arena whenever the table shrinks / rebuilds. Since
    current arena recommendation is to only use arena if it never deletes, then
    this can just replace current arena implementation.
  * If adversarial input is a serious concern and you're on a 64-bit platform,
    enable STBDS_SIPHASH_2_4 (see the 'Compile-time options' section), and pass
    a strong random number to stbds_rand_seed.
  * The default value for the hash table is stored in foo[-1], so if you
    use code like 'hmget(T,k)->value = 5' you can accidentally overwrite
    the value stored by hmdefault if 'k' is not present.
CREDITS
  Sean Barrett -- library, idea for dynamic array API/implementation
  Per Vognsen  -- idea for hash table API/implementation
  Rafael Sachetto -- arrpop()
  github:HeroicKatora -- arraddn() reworking
  Bugfixes:
    Andy Durdin
    Shane Liesegang
    Vinh Truong
    Andreas Molzer
    github:hashitaku
    github:srdjanstipic
    Macoy Madson
    Andreas Vennstrom
    Tobias Mansfield-Williams
*/

#ifdef STBDS_UNIT_TESTS
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#ifndef INCLUDE_STB_DS_H
#define INCLUDE_STB_DS_H

#include "Forge/Config.h"

#define STB_DS_API FORGE_API

#include <stddef.h>
#include <stdint.h>
#include <string.h>

struct bstring;

// PVS Studio error supression
//-V:arrfree:595
//-V:stbds_arrfree:595
//-V:arrdel:568
//-V:stbds_arrdel:568
//-V:hmputs:568
//-V:stbds_hmputs:568
//-V:hmput:568, 574
//-V:stbds_hmput:568
//-V:hmgetp_null:568, 574, 769
//-V:stbds_hmgetp_null:568

// macro for specifying constraints (assertMacro doesn't work inside macros for some reason)
#ifdef PVS_STUDIO
#define STBDS_PVS_ASSERT(x) ((x) ? (void)0 : abort())
#else
#define STBDS_PVS_ASSERT(x) ((void)0)
#endif

#ifndef STBDS_NO_SHORT_NAMES
// functions for static arrays
#define staticarrinit    stbds_staticarrinit
#define staticarr        stbds_staticarr


#define arrinit     stbds_arrinit
#define arrlen      stbds_arrlen
#define arrlenu     stbds_arrlenu
#define arrback     stbds_arrback
#define arrput      stbds_arrput
#define arrpush     stbds_arrput
#define arrpop      stbds_arrpop
#define arrfree     stbds_arrfree
#define arraddn     stbds_arraddn // deprecated, use one of the following instead:
#define arraddnptr  stbds_arraddnptr
#define arraddnindex stbds_arraddnindex
#define arrsetlen   stbds_arrsetlen
#define arrlast     stbds_arrlast
#define arrins      stbds_arrins
#define arrinsn     stbds_arrinsn
#define arrdel      stbds_arrdel
#define arrdeln     stbds_arrdeln
#define arrdelswap  stbds_arrdelswap
#define arrcap      stbds_arrcap
#define arrsetcap   stbds_arrsetcap
#define arrcopy     stbds_arrcopy

#define hmput       stbds_hmput
#define hmputs      stbds_hmputs
#define hmget       stbds_hmget
#define hmget_ts    stbds_hmget_ts
#define hmgets      stbds_hmgets
#define hmgetp      stbds_hmgetp
#define hmgetp_ts   stbds_hmgetp_ts
#define hmgetp_null stbds_hmgetp_null
#define hmgeti      stbds_hmgeti
#define hmgeti_ts   stbds_hmgeti_ts
#define hmdel       stbds_hmdel
#define hmlen       stbds_hmlen
#define hmlenu      stbds_hmlenu
#define hmfree      stbds_hmfree
#define hmdefault   stbds_hmdefault
#define hmdefaults  stbds_hmdefaults

#define shput       stbds_shput
#define shputi      stbds_shputi
#define shputs      stbds_shputs
#define shget       stbds_shget
#define shgeti      stbds_shgeti
#define shgets      stbds_shgets
#define shgetp      stbds_shgetp
#define shgetp_null stbds_shgetp_null
#define shdel       stbds_shdel
#define shlen       stbds_shlen
#define shlenu      stbds_shlenu
#define shfree      stbds_shfree
#define shdefault   stbds_shdefault
#define shdefaults  stbds_shdefaults
#define sh_new_arena  stbds_sh_new_arena
#define sh_new_strdup stbds_sh_new_strdup

#define stralloc    stbds_stralloc
#define strreset    stbds_strreset
#endif

#ifndef STB_DS_IMPLEMENTATION
#define IMEMORY_FROM_HEADER
#include "Forge/Core/Mem/TF_Memory.h"
#endif

#ifdef _MSC_VER
#define STBDS_NOTUSED(v)  (void)(v)

#ifndef STBDS_MSVC_MAX_ALIGNMENT
// There is no way to get alignment of a variable behind pointer for msvc C compiler
// We use size to determine the alignment and clamp it to the max alignment value from this macro
// Note: Actual alignment is defined as 2^STBDS_MSVC_MAX_ALIGNMENT_POWER
#define STBDS_MSVC_MAX_ALIGNMENT_POWER 6
#endif

// Checks whether the sizeof(*p) is aligned to given power of 2
// (Should be divisible by 2^power)
#define STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, power) \
  ( (power) <= STBDS_MSVC_MAX_ALIGNMENT_POWER && ( ( sizeof(*(p)) ) & ( ((size_t)1 << (size_t)(power)) - 1 ) ) == 0 )

#if STBDS_MSVC_MAX_ALIGNMENT_POWER > 8
#error "Max supported alignment power is 8 which corresponds to alignment of 256. When bumping this value adjust STBDS_MSVC_ALIGNOF_PTR macro definition"
#endif

#define STBDS_MSVC_ALIGNOF_PTR(p)                           \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 8) ? ( 1 << 8 ) :   \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 7) ? ( 1 << 7 ) :   \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 6) ? ( 1 << 6 ) :   \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 5) ? ( 1 << 5 ) :   \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 4) ? ( 1 << 4 ) :   \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 3) ? ( 1 << 3 ) :   \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 2) ? ( 1 << 2 ) :   \
    ( STBDS_MSVC_IS_PTR_SIZE_ALIGNED(p, 1) ? ( 1 << 1 ) :   \
    1))))))))

#ifdef __cplusplus
template<typename T>
constexpr void STBDS_CheckAlignment()
{
  static_assert(ALIGNOF(T) <= ((size_t)1 << (size_t)STBDS_MSVC_MAX_ALIGNMENT_POWER), "Increase STBDS_MSVC_MAX_ALIGNMENT_POWER to meet alignment requirements of T");
}
#define STBDS_ALIGNOF_PTR(p) ( STBDS_CheckAlignment<decltype(*(p))>(), STBDS_MSVC_ALIGNOF_PTR(p) )
#else
#define STBDS_ALIGNOF_PTR(p) STBDS_MSVC_ALIGNOF_PTR(p)
#endif

#else
#define STBDS_NOTUSED(v)  (void)sizeof(v)
#define STBDS_ALIGNOF_PTR(p) ALIGNOF(*(p))
#endif

#ifdef __cplusplus
template<typename Tablekey, typename ProvidedKey>
inline void STBDS_AssertKeySizesImpl()
{
  COMPILE_ASSERT(sizeof(Tablekey) == sizeof(ProvidedKey) && "Sizes should be equal. You are probably mixing integers of different size.");
}
#define STBDS_ASSERT_KEY_SIZE(tableKey, key) ( (void)STBDS_AssertKeySizesImpl<decltype(tableKey), decltype(key)>() )

#else
#include "../../../Interfaces/ILog.h"
// Can't do static assert in the middle of expression, so have to use ASSERT for C
inline void STBDS_AssertKeySizesImpl(size_t realSize, size_t providedSize)
{
  ASSERT(realSize == providedSize && "Sizes should be equal. You are probably mixing integers of different size.");
}
#define STBDS_ASSERT_KEY_SIZE(tableKey, key) ( STBDS_AssertKeySizesImpl(sizeof(tableKey), sizeof(key) ) )

#endif

#ifdef ENABLE_MEMORY_TRACKING
#define STBDS_IF_MEM_TRACKING(...) __VA_ARGS__
#else
#define STBDS_IF_MEM_TRACKING(...)
#endif

#define STBDS_FN_ALLOC_ARGS			STBDS_IF_MEM_TRACKING(,const char* FILE_NAME, int FILE_LINE, const char* FUNCTION_NAME, const char* PARENT_FUNCTION_NAME)
#define STBDS_FN_ALLOC_PARAMS		STBDS_IF_MEM_TRACKING(,FILE_NAME, FILE_LINE, FUNCTION_NAME, PARENT_FUNCTION_NAME)

#ifdef __cplusplus
extern "C" {
#endif

// for security against attackers, seed the library with a random number, at least time() but stronger is better
STB_DS_API extern void stbds_rand_seed(size_t seed);

// these are the hash functions used internally if you want to test them or use them for other purposes
STB_DS_API extern size_t stbds_hash_bytes(const void *p, size_t len, size_t seed);
STB_DS_API extern size_t stbds_hash_string(const char *str, size_t seed);
STB_DS_API extern size_t stbds_hash_bstring(const struct bstring* str, size_t seed);


// this is a simple string arena allocator, initialize with e.g. 'stbds_string_arena my_arena={0}'.
typedef struct stbds_string_arena stbds_string_arena;
STB_DS_API extern char * stbds_stralloc_func(stbds_string_arena *a, char *str STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void   stbds_strreset_func(stbds_string_arena *a STBDS_FN_ALLOC_ARGS);

// have to #define STBDS_UNIT_TESTS to call this
STB_DS_API extern void stbds_unit_tests(void);

///////////////
//
// Everything below here is implementation details
//

STB_DS_API extern void * stbds_arrgrowf(void *a, size_t elemsize, size_t elemalign, size_t addlen, size_t min_cap STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void   stbds_arrfree_func(const void* a STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void   stbds_hmfree_func(const void *p, size_t elemsize STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void * stbds_hmget_key(void *a, size_t elemsize, size_t elemalign, const void *key, size_t keysize, int mode STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void * stbds_hmget_key_ts(void *a, size_t elemsize, size_t elemalign, const void *key, size_t keysize, ptrdiff_t *temp, int mode STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void * stbds_hmput_default(void *a, size_t elemsize, size_t elemalign STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void * stbds_hmput_key(void *a, size_t elemsize, size_t elemalign, const void *key, size_t keysize, int mode STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void * stbds_hmdel_key(void *a, size_t elemsize, const void *key, size_t keysize, size_t keyoffset, int mode STBDS_FN_ALLOC_ARGS);
STB_DS_API extern void * stbds_shmode_func(size_t elemsize, size_t elemalign, int mode STBDS_FN_ALLOC_ARGS);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
template<typename T>
/* If you hit error in this function, passed types to arrcopy are different */
void stbds_same_type(const T*, const T*) {}
#else
/* If you hit warning/error in this macro, passed types to arrcopy are different */
#define stbds_same_type(x,y) (void)(x == y)
#endif

#if defined(__GNUC__) || defined(__clang__)
#define STBDS_HAS_TYPEOF
#ifdef __cplusplus
//#define STBDS_HAS_LITERAL_ARRAY  // this is currently broken for clang
#endif
#endif

#if !defined(__cplusplus)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define STBDS_HAS_LITERAL_ARRAY
#endif
#endif

// this macro takes the address of the argument, but on gcc/clang can accept rvalues
#if defined(STBDS_HAS_LITERAL_ARRAY) && defined(STBDS_HAS_TYPEOF)
  #if __clang__
  #define STBDS_ADDRESSOF(typevar, value)     ((__typeof__(typevar)[1]){value}) // literal array decays to pointer to value
  #else
  #define STBDS_ADDRESSOF(typevar, value)     ((typeof(typevar)[1]){value}) // literal array decays to pointer to value
  #endif
#else
#define STBDS_ADDRESSOF(typevar, value)     &(value)
#endif

#define STBDS_OFFSETOF(var,field)((char *) &(var)->field - (char *) (var))

#define stbds_header(t)          ((stbds_array_header*)( (char*)(t) - sizeof(stbds_array_header)))
#define stbds_mem_begin(t)       ((char*)(t) - stbds_header((t))->offset)
#define stbds_temp(t)            (stbds_header(t)->temp)
#define stbds_temp_key(t)        (*(char **) stbds_header(t)->hash_table)

#define stbds_arrsetcap_impl(a,n,f,l,fn,p)		(stbds_arrgrow_impl(a,0,n,f,l,fn,p), STBDS_PVS_ASSERT(stbds_arrcap(a) >= (n)))
#define stbds_arrsetcap(a,n)					stbds_arrsetcap_impl(a,n, __FILE__, __LINE__, __FUNCTION__, "arrsetcap")
#define stbds_arrsetlen_impl(a,n,f,l,fn,p)		((stbds_arrcap(a) < (size_t) (n) ? stbds_arrsetcap_impl((a),(size_t)(n), f, l, fn, p),0 : 0), (a) ? stbds_header(a)->length = (size_t) (n) : 0)
#define stbds_arrsetlen(a,n)					stbds_arrsetlen_impl(a,n, __FILE__, __LINE__, __FUNCTION__, "arrsetlen")
#define stbds_arrcopy_impl(to,from,f,l,fn,p)	(stbds_same_type(to, from), stbds_arrsetlen_impl(to, stbds_arrlen(from), f,l,fn,p), memmove((to), (from), sizeof(*(from)) * stbds_arrlen((from))), to)
#define stbds_arrcopy(to, from)					stbds_arrcopy_impl(to,from, __FILE__, __LINE__, __FUNCTION__, "arrcopy")
#define stbds_arrcap(a)							((a) ? stbds_header(a)->capacity : 0)
#define stbds_arrlen(a)							((a) ? (ptrdiff_t) stbds_header(a)->length : 0)
#define stbds_arrlenu(a)						((a) ?             stbds_header(a)->length : 0)
#define stbds_arrback(a)						((a) && stbds_arrlen(a) > 0 ? &((a)[stbds_arrlen(a) - 1]) : NULL )
#define stbds_arrput_impl(a,v,f,l,fn,p)			(stbds_arrmaybegrow_impl(a, 1, f, l, fn, p), (a)[stbds_header(a)->length++] = (v))
#define stbds_arrput(a,v)						stbds_arrput_impl(a, v, __FILE__, __LINE__, __FUNCTION__, "arrput")
#define stbds_arrpush							stbds_arrput  // synonym
#define stbds_arrpop(a)							(stbds_header(a)->length--, (a)[stbds_header(a)->length])
#define stbds_arrfree_impl(a, f, l, fn, p)		(((a) ? stbds_arrfree_func((a) STBDS_IF_MEM_TRACKING(,f,l,fn,p)) : (void)0), (a) = NULL)
#define stbds_arrfree(a)						stbds_arrfree_impl(a, __FILE__, __LINE__, __FUNCTION__, "arrfree")
#define stbds_arraddn(a,n)						((void)(stbds_arraddnindex(a, n)))    // deprecated, use one of the following instead:
#define stbds_arraddnptr(a,n)					(stbds_arrmaybegrow_impl(a,n, __FILE__, __LINE__, __FUNCTION__, "arraddnptr"), (n) ? (stbds_header(a)->length += (n), &(a)[stbds_header(a)->length-(n)]) : (a))
#define stbds_arraddnindex(a,n)					(stbds_arrmaybegrow_impl(a,n, __FILE__, __LINE__, __FUNCTION__, "arraddnindex"), (n) ? (stbds_header(a)->length += (n), stbds_header(a)->length-(n)) : stbds_arrlen(a))
#define stbds_arraddnoff						stbds_arraddnindex
#define stbds_arrlast(a)						((a)[stbds_header(a)->length-1])
#define stbds_arrdel(a,i)						stbds_arrdeln(a,i,1)
#define stbds_arrdeln(a,i,n)					(memmove(&(a)[i], &(a)[(i)+(n)], sizeof *(a) * (stbds_header(a)->length-(n)-(i))), stbds_header(a)->length -= (n))
#define stbds_arrdelswap(a,i)					((a)[i] = stbds_arrlast(a), stbds_header(a)->length -= 1)
#define stbds_arrinsn(a,i,n)					(stbds_arraddn((a),(n)), memmove(&(a)[(i)+(n)], &(a)[i], sizeof *(a) * (stbds_header(a)->length-(n)-(i))))
#define stbds_arrins(a,i,v)						(stbds_arrinsn((a),(i),1), (a)[i]=(v))

#define stbds_arrmaybegrow_impl(a,n,f,l,fn,p)	((!(a) || stbds_header(a)->length + (n) > stbds_header(a)->capacity) \
												? (stbds_arrgrow_impl(a,n,0,f,l,fn,p),0) : 0)
#define stbds_arrmaybegrow(a,n)					stbds_arrmaybegrow_impl(a,n,__FILE__, __LINE__, __FUNCTION__, "arrmaybegrow")

#define stbds_arrgrow_impl(a,b,c,f,l,fn,p)		((a) = stbds_arrgrowf_wrapper((a), sizeof *(a), STBDS_ALIGNOF_PTR((a)), (b), (c) STBDS_IF_MEM_TRACKING(,f,l,fn,p) ))
#define stbds_arrgrow(a,b,c)					stbds_arrgrow_impl((a),(b),(c), __FILE__, __LINE__, __FUNCTION__, "arrgrow")

#define stbds_hmput_impl(t, k, v, f, l, fn, p) \
    (STBDS_ASSERT_KEY_SIZE((t)->key, k ), \
     (t) = stbds_hmput_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, 0 STBDS_IF_MEM_TRACKING(,f,l,fn,p)),   \
     (t)[stbds_temp((t)-1)].key = (k),    \
     (t)[stbds_temp((t)-1)].value = (v))

#define stbds_hmput(t, k, v) stbds_hmput_impl(t, k, v, __FILE__, __LINE__, __FUNCTION__, "hmput")

#define stbds_hmputs_impl(t, s, f, l, fn, p) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), &(s).key, sizeof (s).key, STBDS_HM_BINARY STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
     (t)[stbds_temp((t)-1)] = (s))
#define stbds_hmputs(t, s) stbds_hmputs_impl(t, s, __FILE__, __LINE__, __FUNCTION__, "hmputs")

/*
 * Note: NULL check ensures that there will be no memory allocation,
 *       otherwise  stbds_hmget_key_wrapper can allocate memory for default block
 */
#define stbds_hmgeti_unsafe_impl(t, k, f, l, fn, p) \
    ((t) == NULL ? -1 : \
      ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, STBDS_HM_BINARY STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
        stbds_temp((t)-1)))
#define stbds_hmgeti_unsafe(t,k) stbds_hmgeti_unsafe_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "hmgeti_unsafe")

#define stbds_hmgeti_impl(t, k, f, l, fn, p) \
    ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, STBDS_HM_BINARY STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
      stbds_temp((t)-1))
#define stbds_hmgeti(t,k) stbds_hmgeti_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "hmgeti")


#define stbds_hmgeti_ts_impl(t, k, temp, f, l, fn, p) \
    ((t) = stbds_hmget_key_ts_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, &(temp), STBDS_HM_BINARY STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
      (temp))
#define stbds_hmgeti_ts(t, k, temp) stbds_hmgeti_ts_impl(t, k, temp, __FILE__, __LINE__, __FUNCTION__, "hmgeti_ts")

#define stbds_hmgetp_impl(t, k, f, l, fn, p) \
    ((void) stbds_hmgeti_impl(t,k,f,l,fn,p), &(t)[stbds_temp((t)-1)])
#define stbds_hmgetp(t, k) stbds_hmgetp_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "hmgetp")

#define stbds_hmgetp_ts_impl(t, k, temp, f, l, fn, p) \
    ((void) stbds_hmgeti_ts_impl(t, k, temp, f, l, fn, p), &(t)[temp])
#define stbds_hmgetp_ts(t, k, temp) stbds_hmgetp_ts_impl(t, k, temp, __FILE__, __LINE__, __FUNCTION__, "hmgetp_ts")

#define stbds_hmdel_impl(t, k, f, l, fn, p) \
    (((t) = stbds_hmdel_key_wrapper((t),sizeof *(t), (void*) STBDS_ADDRESSOF((t)->key, (k)), sizeof (t)->key, STBDS_OFFSETOF((t),key), STBDS_HM_BINARY STBDS_IF_MEM_TRACKING(,f,l,fn,p))),(t)?stbds_temp((t)-1):0)
#define stbds_hmdel(t, k) stbds_hmdel_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "hmdel")

#define stbds_hmdefault_impl(t, v, f, l, fn, p) \
    ((t) = stbds_hmput_default_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)) STBDS_IF_MEM_TRACKING(,f,l,fn,p)), (t)[-1].value = (v))
#define stbds_hmdefault(t, v) stbds_hmdefault_impl(t, v, __FILE__, __LINE__, __FUNCTION__, "hmdefault")

#define stbds_hmdefaults_impl(t, s, f, l, fn, p) \
    ((t) = stbds_hmput_default_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)) STBDS_IF_MEM_TRACKING(,f,l,fn,p)), (t)[-1] = (s))
#define stbds_hmdefaults(t, s) stbds_hmdefaults_impl(t, s, __FILE__, __LINE__, __FUNCTION__, "hmdefaults")

#define stbds_hmfree_impl(ptr, f, l, fn, p)        \
    ((void) ((ptr) != NULL ? stbds_hmfree_func((ptr)-1,sizeof*(ptr) STBDS_IF_MEM_TRACKING(,f,l,fn,p)),0 : 0),(ptr)=NULL)
#define stbds_hmfree(ptr)	stbds_hmfree_impl(ptr, __FILE__, __LINE__, __FUNCTION__, "hmfree")

#define stbds_hmgets(t, k)    (*stbds_hmgetp_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "hmgets"))
#define stbds_hmget(t, k)     (stbds_hmgetp_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "hmgets")->value)
#define stbds_hmget_ts(t, k, temp)  (stbds_hmgetp_ts_impl(t, k, temp, __FILE__, __LINE__, __FUNCTION__, "hmget_ts")->value)
#define stbds_hmlen(t)        ((t) ? (ptrdiff_t) stbds_header((t)-1)->length-1 : 0)
#define stbds_hmlenu(t)       ((t) ?             stbds_header((t)-1)->length-1 : 0)
#define stbds_hmgetp_null(t,k)  (stbds_hmgeti_unsafe_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "hmgetp_null") == -1 ? NULL : &(t)[stbds_temp((t)-1)])

#define stbds_shput_impl(t, k, v, f, l, fn, p) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) (k), sizeof (t)->key, STBDS_HM_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p)),   \
     (t)[stbds_temp((t)-1)].value = (v))
#define stbds_shput(t, k, v)  stbds_shput_impl(t, k, v, __FILE__, __LINE__, __FUNCTION__, "shput")

#define stbds_shputi_impl(t, k, v, f, l, fn, p) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) (k), sizeof (t)->key, STBDS_HM_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p)),   \
     (t)[stbds_temp((t)-1)].value = (v), stbds_temp((t)-1))
#define stbds_shputi(t, k, v) stbds_shputi_impl(t, k, v, __FILE__, __LINE__, __FUNCTION__, "shputi")

#define stbds_shputs_impl(t, s, f, l, fn, p) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) (s).key, sizeof (s).key, STBDS_HM_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
     (t)[stbds_temp((t)-1)] = (s), \
     (t)[stbds_temp((t)-1)].key = stbds_temp_key((t)-1)) // above line overwrites whole structure, so must rewrite key here if it was allocated internally
#define stbds_shputs(t, s) stbds_shputs_impl(t, s,  __FILE__, __LINE__, __FUNCTION__, "shputs")

#define stbds_pshput_impl(t, ptr, f, l, fn, p) \
    ((t) = stbds_hmput_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) (ptr)->key, sizeof (ptr)->key, STBDS_HM_PTR_TO_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
     (t)[stbds_temp((t)-1)] = (ptr))
#define stbds_pshput(t, ptr) stbds_pshput_impl(t, ptr, __FILE__, __LINE__, __FUNCTION__, "pshput")

/* 
 * Note: NULL check ensures that there will be no memory allocation, 
 *       otherwise  stbds_hmget_key_wrapper can allocate memory for default block
 */
#define stbds_shgeti_unsafe_impl(t, k, f, l, fn, p) \
    ((t) == NULL ? -1 : \
      (stbds_hmget_key_wrapper((void*)(t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*)(k), sizeof(t)->key, STBDS_HM_STRING STBDS_IF_MEM_TRACKING(, f, l, fn, p)), \
        stbds_temp((t)-1)))
#define stbds_shgeti_unsafe(t, k) stbds_shgeti_unsafe_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "shgeti_unsafe")

#define stbds_shgeti_impl(t, k, f, l, fn, p) \
     ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR((t)), (void*) (k), sizeof (t)->key, STBDS_HM_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
      stbds_temp((t)-1))
#define stbds_shgeti(t, k) stbds_shgeti_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "shgeti")


#define stbds_pshgeti_impl(t, k, f, l, fn, p) \
     ((t) = stbds_hmget_key_wrapper((t), sizeof *(t), STBDS_ALIGNOF_PTR(t), (void*) (k), sizeof (*(t))->key, STBDS_HM_PTR_TO_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p)), \
      stbds_temp((t)-1))
#define stbds_pshgeti(t, k) stbds_pshgeti_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "pshgeti")

#define stbds_shgetp_impl(t, k, f, l, fn, p) \
    ((void) stbds_shgeti_impl(t,k, f, l, fn, p), &(t)[stbds_temp((t)-1)])
#define stbds_shgetp(t, k) stbds_shgetp_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "shgetp")

#define stbds_pshget_impl(t, k, f, l, fn, p) \
    ((void) stbds_pshgeti_impl(t, k, f, l, fn, p), (t)[stbds_temp((t)-1)])
#define stbds_pshget(t, k) stbds_pshget_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "pshget")

#define stbds_shdel_impl(t, k, f, l, fn, p) \
    (((t) = stbds_hmdel_key_wrapper((t),sizeof *(t), (void*) (k), sizeof (t)->key, STBDS_OFFSETOF((t),key), STBDS_HM_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p))),(t)?stbds_temp((t)-1):0)
#define stbds_shdel(t,k) stbds_shdel_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "shdel")
#define stbds_pshdel_impl(t, k, f, l, fn, p) \
    (((t) = stbds_hmdel_key_wrapper((t),sizeof *(t), (void*) (k), sizeof (*(t))->key, STBDS_OFFSETOF(*(t),key), STBDS_HM_PTR_TO_STRING STBDS_IF_MEM_TRACKING(,f,l,fn,p))),(t)?stbds_temp((t)-1):0)
#define stbds_pshdel(t, k) stbds_pshdel_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "pshdel")

#define stbds_sh_new_arena_impl(t, f, l, fn, p)  \
    (stbds_shfree_impl((t), f, l, fn, p), ((t) = stbds_shmode_func_wrapper(t, sizeof *(t), STBDS_ALIGNOF_PTR(t), STBDS_SH_ARENA STBDS_IF_MEM_TRACKING(,f,l,fn,p))))
#define stbds_sh_new_arena(t) stbds_sh_new_arena_impl(t, __FILE__, __LINE__, __FUNCTION__, "sh_new_arena")
#define stbds_sh_new_strdup_impl(t, f, l, fn, p)  \
    (stbds_shfree_impl((t), f, l, fn, p), ((t) = stbds_shmode_func_wrapper(t, sizeof(*(t)), STBDS_ALIGNOF_PTR(t), STBDS_SH_STRDUP STBDS_IF_MEM_TRACKING(,f,l,fn,p))))
#define stbds_sh_new_strdup(t)  stbds_sh_new_strdup_impl(t, __FILE__, __LINE__, __FUNCTION__, "sh_new_strdup")

#define stbds_stralloc_impl(a, str, f, l, fn, p) stbds_stralloc_func(a, str STBDS_IF_MEM_TRACKING(,f,l,fn,p))
#define stbds_stralloc(a, str) stbds_stralloc_impl(a, str, __FILE__, __LINE__, __FUNCTION__, "stralloc")
#define stbds_strreset_impl(a, f, l, fn, p) stbds_strreset_func(a STBDS_IF_MEM_TRACKING(,f,l,fn,p))
#define stbds_strreset(a) stbds_strreset_impl(a, __FILE__, __LINE__, __FUNCTION__, "strreset")


#define stbds_shdefault_impl	stbds_hmdefault_impl
#define stbds_shdefault			stbds_hmdefault
#define stbds_shdefaults_impl	stbds_hmdefaults_impl
#define stbds_shdefaults		stbds_hmdefaults

#define stbds_shfree_impl	stbds_hmfree_impl
#define stbds_shfree(t)		stbds_shfree_impl(t, __FILE__, __LINE__, __FUNCTION__, "shfree")
#define stbds_shlenu		stbds_hmlenu

#define stbds_shgets(t, k) (*stbds_shgetp_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "shgets"))
#define stbds_shget(t, k)  (stbds_shgetp_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "shget")->value)
#define stbds_shgetp_null(t, k)  (stbds_shgeti_unsafe_impl(t, k, __FILE__, __LINE__, __FUNCTION__, "shgetp_null") == -1 ? NULL : &(t)[stbds_temp((t)-1)])
#define stbds_shlen        stbds_hmlen

typedef struct ALIGNAS(MIN_MALLOC_ALIGNMENT)
{
  size_t      length;
  size_t      capacity;
  void      * hash_table;
  ptrdiff_t   temp;
  uint16_t    offset; // offset to the begining of alloc
} stbds_array_header;

typedef struct stbds_string_block
{
  struct stbds_string_block *next;
  char storage[8];
} stbds_string_block;

struct stbds_string_arena
{
  stbds_string_block *storage;
  size_t remaining;
  unsigned char block;
  unsigned char mode;  // this isn't used by the string arena itself
};


/*
 * TF: stb_ds was extended to allow different modes
 *     In order to add new mode do following:
 *     1. Add new enum value
 *     2. Add enum to STBDS_HM_DISPATCH macro in implementation section
 *     2. Add following function definitions at implementation section:
 *        + int <ENUM_NAME>_compare(void* left, void* right)
 *          should return 0 if equal
 *        +
 */
typedef enum StbDsHModes
{
	STBDS_HM_BINARY = 0,
	STBDS_HM_STRING,
	/*
	 * TF: Doesn't manage bstrings,
	 *     key should be of type bstring, not a bstring*
	 */
	STBDS_HM_CONST_BSTRING,

}StbDsHModes;


enum
{
   STBDS_SH_NONE,
   STBDS_SH_DEFAULT,
   STBDS_SH_STRDUP,
   STBDS_SH_ARENA
};

#ifdef __cplusplus
// in C we use implicit assignment from these void*-returning functions to T*.
// in C++ these templates make the same code work
template<class T> static T * stbds_arrgrowf_wrapper(T *a, size_t elemsize, size_t elemalign, size_t addlen, size_t min_cap STBDS_FN_ALLOC_ARGS) 
{
  return (T*)stbds_arrgrowf((void *)a, elemsize, elemalign, addlen, min_cap STBDS_FN_ALLOC_PARAMS);
}
template<class T> static T * stbds_hmget_key_wrapper(T *a, size_t elemsize, size_t elemalign, void *key, size_t keysize, int mode STBDS_FN_ALLOC_ARGS) {
  return (T*)stbds_hmget_key((void*)a, elemsize, elemalign, key, keysize, mode STBDS_FN_ALLOC_PARAMS);
}
template<class T> static T * stbds_hmget_key_ts_wrapper(T *a, size_t elemsize, size_t elemalign, void *key, size_t keysize, ptrdiff_t *temp, int mode STBDS_FN_ALLOC_ARGS) {
  return (T*)stbds_hmget_key_ts((void*)a, elemsize, elemalign, key, keysize, temp, mode STBDS_FN_ALLOC_PARAMS);
}
template<class T> static T * stbds_hmput_default_wrapper(T *a, size_t elemsize, size_t elemalign STBDS_FN_ALLOC_ARGS) {
  return (T*)stbds_hmput_default((void *)a, elemsize, elemalign STBDS_FN_ALLOC_PARAMS);
}
template<class T> static T * stbds_hmput_key_wrapper(T *a, size_t elemsize, size_t elemalign, const void *key, size_t keysize, int mode STBDS_FN_ALLOC_ARGS) {
  return (T*)stbds_hmput_key((void*)a, elemsize, elemalign, key, keysize, mode STBDS_FN_ALLOC_PARAMS);
}
template<class T> static T * stbds_hmdel_key_wrapper(T *a, size_t elemsize, void *key, size_t keysize, size_t keyoffset, int mode STBDS_FN_ALLOC_ARGS){
  return (T*)stbds_hmdel_key((void*)a, elemsize, key, keysize, keyoffset, mode STBDS_FN_ALLOC_PARAMS);
}
template<class T> static T * stbds_shmode_func_wrapper(T *, size_t elemsize, size_t elemalign, int mode STBDS_FN_ALLOC_ARGS) {
  return (T*)stbds_shmode_func(elemsize, elemalign, mode STBDS_FN_ALLOC_PARAMS);
}
#else
#define stbds_arrgrowf_wrapper            stbds_arrgrowf
#define stbds_hmget_key_wrapper           stbds_hmget_key
#define stbds_hmget_key_ts_wrapper        stbds_hmget_key_ts
#define stbds_hmput_default_wrapper       stbds_hmput_default
#define stbds_hmput_key_wrapper           stbds_hmput_key
#define stbds_hmdel_key_wrapper           stbds_hmdel_key
#define stbds_shmode_func_wrapper(t,e,m)  stbds_shmode_func(e,m)
#endif

#endif // INCLUDE_STB_DS_H


//////////////////////////////////////////////////////////////////////////////
//
//   IMPLEMENTATION
//

#ifdef STB_DS_IMPLEMENTATION
#include "../../../Interfaces/ILog.h"
#include "../../../Threading/Atomics.h"
#include "../bstrlib/bstrlib.h"

#include <string.h>

#ifdef STBDS_STATISTICS
#define STBDS_STATS(x)   x
size_t stbds_array_grow;
size_t stbds_hash_grow;
size_t stbds_hash_shrink;
size_t stbds_hash_rebuild;
size_t stbds_hash_probes;
size_t stbds_hash_alloc;
size_t stbds_rehash_probes;
size_t stbds_rehash_items;
#else
#define STBDS_STATS(x)
#endif


//
// stbds_arr implementation
//

//int *prev_allocs[65536];
//int num_prev;

void *stbds_arrgrowf(void *a, size_t elemsize, size_t elemalign, size_t addlen, size_t min_cap STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif

  stbds_array_header temp={0}; // force debugging
  void *b0, *b1;
  size_t min_len = stbds_arrlen(a) + addlen;
  (void) sizeof(temp);

  // compute the minimum capacity needed
  if (min_len > min_cap)
    min_cap = min_len;

  if (min_cap <= stbds_arrcap(a))
    return a;

  // increase needed capacity to guarantee O(1) amortized
  if (min_cap < 2 * stbds_arrcap(a))
    min_cap = 2 * stbds_arrcap(a);
  else if (min_cap < 4)
    min_cap = 4;

  //if (num_prev < 65536) if (a) prev_allocs[num_prev++] = (int *) ((char *) a+1);
  //if (num_prev == 2201)
  //  num_prev = num_prev;
  size_t max_offset = sizeof(stbds_array_header);
  max_offset += elemalign <= MIN_MALLOC_ALIGNMENT ? 0 : elemalign - 1;
  ASSERT((elemalign & (elemalign - 1)) == 0 && "Alignment is not a power of 2");
  const uint16_t old_offset = a ? stbds_header(a)->offset : UINT16_MAX;
  // orig pointer
  b0 = tf_realloc_internal((a) ? stbds_mem_begin(a) : NULL, elemsize * min_cap + max_offset,
	  FILE_NAME, FILE_LINE, pFunction);
  ASSERT((uintptr_t)b0 % MIN_MALLOC_ALIGNMENT == 0 && "Pointer produced by tf_realloc_internal is not aligned to MIN_MALLOC_ALIGNMENT");
  //if (num_prev < 65536) prev_allocs[num_prev++] = (int *) (char *) b;
  // Align b1
  b1 = (void*)(((uintptr_t)b0 + max_offset) & ~(elemalign - 1));

  ASSERT((void*)stbds_header(b1) >= b0 && "Logical error in stb_ds code.");
  ASSERT((uintptr_t)stbds_header(b1) % ALIGNOF(stbds_array_header) == 0 && "Header is misaligned.");
  ASSERT((uintptr_t)b1 % elemalign == 0 && "Pointer is misaligned");
  ASSERT(((char*)b1 - (char*)b0) <= UINT16_MAX);

  const uint16_t new_offset = (uint16_t)((char*)b1 - (char*)b0);
  // When doing realloc pointer can get different alignment
  // Move memory accordingly when this happens
  if (a && new_offset != old_offset)
    memmove(stbds_header(b1), stbds_header((char*)b0 + old_offset), elemsize * min_len + sizeof(stbds_array_header));

  if (a == NULL) {
    stbds_header(b1)->length = 0;
    stbds_header(b1)->hash_table = 0;
    stbds_header(b1)->temp = 0;
  } else {
    STBDS_STATS(++stbds_array_grow);
  }
  stbds_header(b1)->capacity = min_cap;
  stbds_header(b1)->offset = new_offset;

  return b1;
}

void  stbds_arrfree_func(const void* a STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif
	tf_free_internal(((a) ? stbds_mem_begin(a) : NULL), FILE_NAME, FILE_LINE, pFunction);
}

//
// stbds_hm hash table implementation
//

#ifdef STBDS_INTERNAL_SMALL_BUCKET
#define STBDS_BUCKET_LENGTH      4
#else
#define STBDS_BUCKET_LENGTH      8
#endif

#define STBDS_BUCKET_SHIFT      (STBDS_BUCKET_LENGTH == 8 ? 3 : 2)
#define STBDS_BUCKET_MASK       (STBDS_BUCKET_LENGTH-1)
#define STBDS_CACHE_LINE_SIZE   64

#define STBDS_ALIGN_FWD(n,a)   (((n) + (a) - 1) & ~((a)-1))

typedef struct
{
   size_t    hash [STBDS_BUCKET_LENGTH];
   ptrdiff_t index[STBDS_BUCKET_LENGTH];
} stbds_hash_bucket; // in 32-bit, this is one 64-byte cache line; in 64-bit, each array is one 64-byte cache line

typedef struct
{
  char * temp_key; // this MUST be the first field of the hash table
  size_t slot_count;
  size_t used_count;
  size_t used_count_threshold;
  size_t used_count_shrink_threshold;
  size_t tombstone_count;
  size_t tombstone_count_threshold;
  size_t seed;
  size_t slot_count_log2;
  stbds_string_arena string;
  stbds_hash_bucket *storage; // not a separate allocation, just 64-byte aligned storage after this struct
} stbds_hash_index;

/*
 * TF: Dispatch functions for different modes of hash table
 */
#define STBDS_CONCATIMPL(x,y) x ## y
#define STBDS_CONCAT(x,y) STBDS_CONCATIMPL(x,y)

#define STBDS_HM_DISPATCH_IMPL(mode, CALL, fnName, ...)\
	switch (mode) {													\
	case STBDS_HM_BINARY:											\
		CALL(STBDS_CONCAT(STBDS_HM_BINARY, fnName)(__VA_ARGS__));	\
		break;														\
	case STBDS_HM_STRING:											\
		CALL(STBDS_CONCAT(STBDS_HM_STRING, fnName)(__VA_ARGS__));	\
		break;														\
	case STBDS_HM_CONST_BSTRING:											\
		CALL(STBDS_CONCAT(STBDS_HM_CONST_BSTRING, fnName)(__VA_ARGS__));	\
		break;														\
	default:														\
		ASSERT(0 && "Invalid mode");								\
	};
#define STBDS_EXPAND(x) x

#define STBDS_HM_DISPATCH(mode, fnName, ...) \
		STBDS_HM_DISPATCH_IMPL(mode, STBDS_EXPAND, fnName, __VA_ARGS__)

#define STBDS_HM_DISPATCH_ASSIGN(mode, val, fnName, ...) \
		STBDS_HM_DISPATCH_IMPL(mode, (val) = , fnName, __VA_ARGS__)


static inline int STBDS_HM_BINARY_is_equal(const void* p0, const void* p1, size_t keysize)
{
	return memcmp(p0, p1, keysize) == 0;
}
static inline int STBDS_HM_STRING_is_equal(const void* p0, const void* p1, size_t keysize)
{
	ASSERT(keysize == sizeof(char*));
	return strcmp((const char*)p0, *(const char**)p1) == 0;
}
static inline int STBDS_HM_CONST_BSTRING_is_equal(const void* p0, const void* p1, size_t keysize)
{
	ASSERT(keysize == sizeof(bstring));
	return biseq((bstring*)p0, (bstring*)p1) == 1;
}

static inline size_t STBDS_HM_BINARY_hash(const void* key, size_t keysize, size_t seed)
{
	return stbds_hash_bytes(key, keysize, seed);
}
static inline size_t STBDS_HM_STRING_hash(const void* key, size_t keysize, size_t seed)
{
	ASSERT(keysize == sizeof(char*));
	return stbds_hash_string((const char*)key, seed);
}
static inline size_t STBDS_HM_CONST_BSTRING_hash(const void* key, size_t keysize, size_t seed)
{
	ASSERT(keysize == sizeof(bstring));
	const bstring* b = (const bstring*)key;
	return stbds_hash_bytes(b->data, b->slen, seed);
}

static inline int STBDS_HM_BINARY_default_storage_mode(void)
{
	return STBDS_SH_NONE;
}
static inline int STBDS_HM_STRING_default_storage_mode(void)
{
	return STBDS_SH_DEFAULT;
}
static inline int STBDS_HM_CONST_BSTRING_default_storage_mode(void)
{
	return STBDS_SH_NONE;
}

static inline void STBDS_HM_BINARY_free_key(stbds_hash_index* table, const void* key, size_t keysize STBDS_FN_ALLOC_ARGS)
{
	#ifdef ENABLE_MEMORY_TRACKING
    UNREF_PARAM(PARENT_FUNCTION_NAME);
	UNREF_PARAM(FUNCTION_NAME);
	UNREF_PARAM(FILE_NAME);
	UNREF_PARAM(FILE_LINE);
    #endif
    UNREF_PARAM(table); 
    UNREF_PARAM(key); 
    UNREF_PARAM(keysize); 
}

static inline void STBDS_HM_STRING_free_key(stbds_hash_index* table, const void* key, size_t keysize STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif
	ASSERT(keysize == sizeof(char*));
	if (table->string.mode == STBDS_SH_STRDUP)
		tf_free_internal(*(char**)(key), FILE_NAME, FILE_LINE, pFunction);
}

static inline void STBDS_HM_CONST_BSTRING_free_key(stbds_hash_index* table, void* key, size_t keysize STBDS_FN_ALLOC_ARGS)
{
}


static ptrdiff_t stbds_hm_find_slot(void *a, size_t elemsize, const void *key, size_t keysize, size_t keyoffset, int mode);

static inline ptrdiff_t STBDS_HM_BINARY_find_slot(void *a, size_t elemsize, const void *key, size_t keysize, size_t keyoffset, int mode)
{
	return stbds_hm_find_slot(a, elemsize, key, keysize, keyoffset, mode);
}

static inline ptrdiff_t STBDS_HM_STRING_find_slot(void *a, size_t elemsize, const void* key, size_t keysize, size_t keyoffset, int mode)
{
	ASSERT(keysize == sizeof(char*));
	return stbds_hm_find_slot(a, elemsize, *(const char**)key, keysize, keyoffset, mode);
}

static inline ptrdiff_t STBDS_HM_CONST_BSTRING_find_slot(void *a, size_t elemsize, const void *key, size_t keysize, size_t keyoffset, int mode)
{
	ASSERT(keysize == sizeof(bstring));
	return stbds_hm_find_slot(a, elemsize, key, keysize, keyoffset, mode);
}

#define STBDS_INDEX_EMPTY    -1
#define STBDS_INDEX_DELETED  -2
#define STBDS_INDEX_IN_USE(x)  ((x) >= 0)

#define STBDS_HASH_EMPTY      0
#define STBDS_HASH_DELETED    1

static tfrg_atomic64_t stbds_hash_seed=0x31415926;

void stbds_rand_seed(size_t seed)
{
  tfrg_atomic64_store_relaxed(&stbds_hash_seed, (uint64_t)seed);
}

#define stbds_load_32_or_64(var, temp, v32, v64_hi, v64_lo)                                          \
  temp = v64_lo ^ v32, temp <<= 16, temp <<= 16, temp >>= 16, temp >>= 16, /* discard if 32-bit */   \
  var = v64_hi, var <<= 16, var <<= 16,                                    /* discard if 32-bit */   \
  var ^= temp ^ v32

#define STBDS_SIZE_T_BITS           ((sizeof (size_t)) * 8)

static size_t stbds_probe_position(size_t hash, size_t slot_count, size_t slot_log2)
{
  size_t pos;
  STBDS_NOTUSED(slot_log2);
  pos = hash & (slot_count-1);
  #ifdef STBDS_INTERNAL_BUCKET_START
  pos &= ~STBDS_BUCKET_MASK;
  #endif
  return pos;
}

static size_t stbds_log2(size_t slot_count)
{
  size_t n=0;
  while (slot_count > 1) {
    slot_count >>= 1;
    ++n;
  }
  return n;
}

static stbds_hash_index *stbds_make_hash_index(size_t slot_count, stbds_hash_index *ot STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif
  stbds_hash_index *t;
  t = (stbds_hash_index *) tf_realloc_internal(NULL, (slot_count >> STBDS_BUCKET_SHIFT) * sizeof(stbds_hash_bucket) + sizeof(stbds_hash_index) + STBDS_CACHE_LINE_SIZE-1, 
											   FILE_NAME, FILE_LINE, pFunction);
  t->storage = (stbds_hash_bucket *) STBDS_ALIGN_FWD((size_t) (t+1), STBDS_CACHE_LINE_SIZE);
  t->slot_count = slot_count;
  t->slot_count_log2 = stbds_log2(slot_count);
  t->tombstone_count = 0;
  t->used_count = 0;

  #if 0 // A1
  t->used_count_threshold        = slot_count*12/16; // if 12/16th of table is occupied, grow
  t->tombstone_count_threshold   = slot_count* 2/16; // if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold = slot_count* 4/16; // if table is only 4/16th full, shrink
  #elif 1 // A2
  //t->used_count_threshold        = slot_count*12/16; // if 12/16th of table is occupied, grow
  //t->tombstone_count_threshold   = slot_count* 3/16; // if tombstones are 3/16th of table, rebuild
  //t->used_count_shrink_threshold = slot_count* 4/16; // if table is only 4/16th full, shrink

  // compute without overflowing
  t->used_count_threshold        = slot_count - (slot_count>>2);
  t->tombstone_count_threshold   = (slot_count>>3) + (slot_count>>4);
  t->used_count_shrink_threshold = slot_count >> 2;

  #elif 0 // B1
  t->used_count_threshold        = slot_count*13/16; // if 13/16th of table is occupied, grow
  t->tombstone_count_threshold   = slot_count* 2/16; // if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold = slot_count* 5/16; // if table is only 5/16th full, shrink
  #else // C1
  t->used_count_threshold        = slot_count*14/16; // if 14/16th of table is occupied, grow
  t->tombstone_count_threshold   = slot_count* 2/16; // if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold = slot_count* 6/16; // if table is only 6/16th full, shrink
  #endif
  // Following statistics were measured on a Core i7-6700 @ 4.00Ghz, compiled with clang 7.0.1 -O2
    // Note that the larger tables have high variance as they were run fewer times
  //     A1            A2          B1           C1
  //    0.10ms :     0.10ms :     0.10ms :     0.11ms :      2,000 inserts creating 2K table
  //    0.96ms :     0.95ms :     0.97ms :     1.04ms :     20,000 inserts creating 20K table
  //   14.48ms :    14.46ms :    10.63ms :    11.00ms :    200,000 inserts creating 200K table
  //  195.74ms :   196.35ms :   203.69ms :   214.92ms :  2,000,000 inserts creating 2M table
  // 2193.88ms :  2209.22ms :  2285.54ms :  2437.17ms : 20,000,000 inserts creating 20M table
  //   65.27ms :    53.77ms :    65.33ms :    65.47ms : 500,000 inserts & deletes in 2K table
  //   72.78ms :    62.45ms :    71.95ms :    72.85ms : 500,000 inserts & deletes in 20K table
  //   89.47ms :    77.72ms :    96.49ms :    96.75ms : 500,000 inserts & deletes in 200K table
  //   97.58ms :    98.14ms :    97.18ms :    97.53ms : 500,000 inserts & deletes in 2M table
  //  118.61ms :   119.62ms :   120.16ms :   118.86ms : 500,000 inserts & deletes in 20M table
  //  192.11ms :   194.39ms :   196.38ms :   195.73ms : 500,000 inserts & deletes in 200M table

  if (slot_count <= STBDS_BUCKET_LENGTH)
    t->used_count_shrink_threshold = 0;
  // to avoid infinite loop, we need to guarantee that at least one slot is empty and will terminate probes
  ASSERT(t->used_count_threshold + t->tombstone_count_threshold < t->slot_count);
  STBDS_STATS(++stbds_hash_alloc);
  if (ot) {
    t->string = ot->string;
    // reuse old seed so we can reuse old hashes so below "copy out old data" doesn't do any hashing
    t->seed = ot->seed;
  } else {
    size_t a,b,temp;
    memset(&t->string, 0, sizeof(t->string));
    // LCG
    // in 32-bit, a =          2147001325   b =  715136305
    // in 64-bit, a = 2862933555777941757   b = 3037000493
    stbds_load_32_or_64(a,temp, 2147001325, 0x27bb2ee6, 0x87b0b0fd);
    stbds_load_32_or_64(b,temp,  715136305,          0, 0xb504f32d);
	uint64_t newSeed;
    do 
    {
        t->seed = tfrg_atomic64_load_relaxed(&stbds_hash_seed);
        newSeed = (uint64_t)(t->seed * a + b);
    } while(tfrg_atomic64_cas_relaxed(&stbds_hash_seed, (uint64_t)t->seed, newSeed) != (uint64_t)t->seed);
  }

  {
    size_t i,j;
    for (i=0; i < slot_count >> STBDS_BUCKET_SHIFT; ++i) {
      stbds_hash_bucket *b = &t->storage[i];
      for (j=0; j < STBDS_BUCKET_LENGTH; ++j)
        b->hash[j] = STBDS_HASH_EMPTY;
      for (j=0; j < STBDS_BUCKET_LENGTH; ++j)
        b->index[j] = STBDS_INDEX_EMPTY;
    }
  }

  // copy out the old data, if any
  if (ot) {
    size_t i,j;
    t->used_count = ot->used_count;
    for (i=0; i < ot->slot_count >> STBDS_BUCKET_SHIFT; ++i) {
      stbds_hash_bucket *ob = &ot->storage[i];
      for (j=0; j < STBDS_BUCKET_LENGTH; ++j) {
        if (STBDS_INDEX_IN_USE(ob->index[j])) {
          size_t hash = ob->hash[j];
          size_t pos = stbds_probe_position(hash, t->slot_count, t->slot_count_log2);
          size_t step = STBDS_BUCKET_LENGTH;
          STBDS_STATS(++stbds_rehash_items);
          for (;;) {
            size_t limit,z;
            stbds_hash_bucket *bucket;
            bucket = &t->storage[pos >> STBDS_BUCKET_SHIFT];
            STBDS_STATS(++stbds_rehash_probes);

            for (z=pos & STBDS_BUCKET_MASK; z < STBDS_BUCKET_LENGTH; ++z) {
              if (bucket->hash[z] == 0) {
                bucket->hash[z] = hash;
                bucket->index[z] = ob->index[j];
                goto done;
              }
            }

            limit = pos & STBDS_BUCKET_MASK;
            for (z = 0; z < limit; ++z) {
              if (bucket->hash[z] == 0) {
                bucket->hash[z] = hash;
                bucket->index[z] = ob->index[j];
                goto done;
              }
            }

            pos += step;                  // quadratic probing
            step += STBDS_BUCKET_LENGTH;
            pos &= (t->slot_count-1);
          }
        }
       done:
        ;
      }
    }
  }

  return t;
}

#define STBDS_ROTATE_LEFT(val, n)   (((val) << (n)) | ((val) >> (STBDS_SIZE_T_BITS - (n))))
#define STBDS_ROTATE_RIGHT(val, n)  (((val) >> (n)) | ((val) << (STBDS_SIZE_T_BITS - (n))))

size_t stbds_hash_string(const char *str, size_t seed)
{
  size_t hash = seed;
  while (*str)
     hash = STBDS_ROTATE_LEFT(hash, 9) + (unsigned char) *str++;

  // Thomas Wang 64-to-32 bit mix function, hopefully also works in 32 bits
  hash ^= seed;
  hash = (~hash) + (hash << 18);
  hash ^= hash ^ STBDS_ROTATE_RIGHT(hash,31);
  hash = hash * 21;
  hash ^= hash ^ STBDS_ROTATE_RIGHT(hash,11);
  hash += (hash << 6);
  hash ^= STBDS_ROTATE_RIGHT(hash,22);
  return hash+seed;
}
size_t stbds_hash_bstring(const bstring* bstr, size_t seed)
{
	return stbds_hash_bytes(bstr->data, bstr->slen, seed);
}

#ifdef STBDS_SIPHASH_2_4
#define STBDS_SIPHASH_C_ROUNDS 2
#define STBDS_SIPHASH_D_ROUNDS 4
typedef int STBDS_SIPHASH_2_4_can_only_be_used_in_64_bit_builds[sizeof(size_t) == 8 ? 1 : -1];
#endif

#ifndef STBDS_SIPHASH_C_ROUNDS
#define STBDS_SIPHASH_C_ROUNDS 1
#endif
#ifndef STBDS_SIPHASH_D_ROUNDS
#define STBDS_SIPHASH_D_ROUNDS 1
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4127) // conditional expression is constant, for do..while(0) and sizeof()==
#endif

static size_t stbds_siphash_bytes(const void *p, size_t len, size_t seed)
{
  unsigned char *d = (unsigned char *) p;
  size_t i,j;
  size_t v0,v1,v2,v3, data;

  // hash that works on 32- or 64-bit registers without knowing which we have
  // (computes different results on 32-bit and 64-bit platform)
  // derived from siphash, but on 32-bit platforms very different as it uses 4 32-bit state not 4 64-bit
  v0 = ((((size_t) 0x736f6d65 << 16) << 16) + 0x70736575) ^  seed;
  v1 = ((((size_t) 0x646f7261 << 16) << 16) + 0x6e646f6d) ^ ~seed;
  v2 = ((((size_t) 0x6c796765 << 16) << 16) + 0x6e657261) ^  seed;
  v3 = ((((size_t) 0x74656462 << 16) << 16) + 0x79746573) ^ ~seed;

  #ifdef STBDS_TEST_SIPHASH_2_4
  // hardcoded with key material in the siphash test vectors
  v0 ^= 0x0706050403020100ull ^  seed;
  v1 ^= 0x0f0e0d0c0b0a0908ull ^ ~seed;
  v2 ^= 0x0706050403020100ull ^  seed;
  v3 ^= 0x0f0e0d0c0b0a0908ull ^ ~seed;
  #endif

  #define STBDS_SIPROUND() \
    do {                   \
      v0 += v1; v1 = STBDS_ROTATE_LEFT(v1, 13);  v1 ^= v0; v0 = STBDS_ROTATE_LEFT(v0,STBDS_SIZE_T_BITS/2); \
      v2 += v3; v3 = STBDS_ROTATE_LEFT(v3, 16);  v3 ^= v2;                                                 \
      v2 += v1; v1 = STBDS_ROTATE_LEFT(v1, 17);  v1 ^= v2; v2 = STBDS_ROTATE_LEFT(v2,STBDS_SIZE_T_BITS/2); \
      v0 += v3; v3 = STBDS_ROTATE_LEFT(v3, 21);  v3 ^= v0;                                                 \
    } while (0)

  for (i=0; i+sizeof(size_t) <= len; i += sizeof(size_t), d += sizeof(size_t)) {
    data = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
    data |= (size_t) (d[4] | (d[5] << 8) | (d[6] << 16) | (d[7] << 24)) << 16 << 16; // discarded if size_t == 4

    v3 ^= data;
    for (j=0; j < STBDS_SIPHASH_C_ROUNDS; ++j)
      STBDS_SIPROUND();
    v0 ^= data;
  }
  data = len << (STBDS_SIZE_T_BITS-8);
  switch (len - i) {
    case 7: data |= ((size_t) d[6] << 24) << 24; // fall through
    case 6: data |= ((size_t) d[5] << 20) << 20; // fall through
    case 5: data |= ((size_t) d[4] << 16) << 16; // fall through
    case 4: data |= (d[3] << 24); // fall through
    case 3: data |= (d[2] << 16); // fall through
    case 2: data |= (d[1] << 8); // fall through
    case 1: data |= d[0]; // fall through
    case 0: break;
  }
  v3 ^= data;
  for (j=0; j < STBDS_SIPHASH_C_ROUNDS; ++j)
    STBDS_SIPROUND();
  v0 ^= data;
  v2 ^= 0xff;
  for (j=0; j < STBDS_SIPHASH_D_ROUNDS; ++j)
    STBDS_SIPROUND();

#ifdef STBDS_SIPHASH_2_4
  return v0^v1^v2^v3;
#else
  return v1^v2^v3; // slightly stronger since v0^v3 in above cancels out final round operation? I tweeted at the authors of SipHash about this but they didn't reply
#endif
}

size_t stbds_hash_bytes(const void *p, size_t len, size_t seed)
{
#ifdef STBDS_SIPHASH_2_4
  return stbds_siphash_bytes(p,len,seed);
#else
  unsigned char *d = (unsigned char *) p;

  if (len == 4) {
    unsigned int hash = (unsigned)d[0] | ((unsigned)d[1] << 8) | ((unsigned)d[2] << 16) | ((unsigned)d[3] << 24);
    #if 0
    // HASH32-A  Bob Jenkin's hash function w/o large constants
    hash ^= seed;
    hash -= (hash<<6);
    hash ^= (hash>>17);
    hash -= (hash<<9);
    hash ^= seed;
    hash ^= (hash<<4);
    hash -= (hash<<3);
    hash ^= (hash<<10);
    hash ^= (hash>>15);
    #elif 1
    // HASH32-BB  Bob Jenkin's presumably-accidental version of Thomas Wang hash with rotates turned into shifts.
    // Note that converting these back to rotates makes it run a lot slower, presumably due to collisions, so I'm
    // not really sure what's going on.
    hash ^= seed;
    hash = (hash ^ 61) ^ (hash >> 16);
    hash = hash + (hash << 3);
    hash = hash ^ (hash >> 4);
    hash = hash * 0x27d4eb2d;
    hash ^= seed;
    hash = hash ^ (hash >> 15);
    #else  // HASH32-C   -  Murmur3
    hash ^= seed;
    hash *= 0xcc9e2d51;
    hash = (hash << 17) | (hash >> 15);
    hash *= 0x1b873593;
    hash ^= seed;
    hash = (hash << 19) | (hash >> 13);
    hash = hash*5 + 0xe6546b64;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= seed;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;
    #endif
    // Following statistics were measured on a Core i7-6700 @ 4.00Ghz, compiled with clang 7.0.1 -O2
    // Note that the larger tables have high variance as they were run fewer times
    //  HASH32-A   //  HASH32-BB  //  HASH32-C
    //    0.10ms   //    0.10ms   //    0.10ms :      2,000 inserts creating 2K table
    //    0.96ms   //    0.95ms   //    0.99ms :     20,000 inserts creating 20K table
    //   14.69ms   //   14.43ms   //   14.97ms :    200,000 inserts creating 200K table
    //  199.99ms   //  195.36ms   //  202.05ms :  2,000,000 inserts creating 2M table
    // 2234.84ms   // 2187.74ms   // 2240.38ms : 20,000,000 inserts creating 20M table
    //   55.68ms   //   53.72ms   //   57.31ms : 500,000 inserts & deletes in 2K table
    //   63.43ms   //   61.99ms   //   65.73ms : 500,000 inserts & deletes in 20K table
    //   80.04ms   //   77.96ms   //   81.83ms : 500,000 inserts & deletes in 200K table
    //  100.42ms   //   97.40ms   //  102.39ms : 500,000 inserts & deletes in 2M table
    //  119.71ms   //  120.59ms   //  121.63ms : 500,000 inserts & deletes in 20M table
    //  185.28ms   //  195.15ms   //  187.74ms : 500,000 inserts & deletes in 200M table
    //   15.58ms   //   14.79ms   //   15.52ms : 200,000 inserts creating 200K table with varying key spacing

    return (((size_t) hash << 16 << 16) | hash) ^ seed;
  } else if (len == 8 && sizeof(size_t) == 8) {
    size_t hash = (size_t)d[0] | ((size_t)d[1] << 8) | ((size_t)d[2] << 16) | ((size_t)d[3] << 24);
    hash |= (size_t) ((size_t)d[4] | ((size_t)d[5] << 8) | ((size_t)d[6] << 16) | ((size_t)d[7] << 24)) << 16 << 16; // avoid warning if size_t == 4
    hash ^= seed;
    hash = (~hash) + (hash << 21);
    hash ^= STBDS_ROTATE_RIGHT(hash,24);
    hash *= 265;
    hash ^= STBDS_ROTATE_RIGHT(hash,14);
    hash ^= seed;
    hash *= 21;
    hash ^= STBDS_ROTATE_RIGHT(hash,28);
    hash += (hash << 31);
    hash = (~hash) + (hash << 18);
    return hash;
  } else {
    return stbds_siphash_bytes(p,len,seed);
  }
#endif
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif


static int stbds_is_key_equal(void *a, size_t elemsize, const void *key, size_t keysize, size_t keyoffset, int mode, size_t i)
{
	int ret = 0;
	STBDS_HM_DISPATCH_ASSIGN(mode, ret, _is_equal, key, (char *)a + elemsize * i + keyoffset, keysize);
	return ret;
}

#define STBDS_HASH_TO_ARR(x,elemsize) ((char*) (x) - (elemsize))
#define STBDS_ARR_TO_HASH(x,elemsize) ((char*) (x) + (elemsize))

#define stbds_hash_table(a)  ((stbds_hash_index *) stbds_header(a)->hash_table)

void stbds_hmfree_func(const void *a, size_t elemsize STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif

  if (a == NULL) return;
  if (stbds_hash_table(a) != NULL) {
    if (stbds_hash_table(a)->string.mode == STBDS_SH_STRDUP) {
      size_t i;
      // skip 0th element, which is default
      for (i=1; i < stbds_header(a)->length; ++i)
        tf_free_internal(*(char**) ((char *) a + elemsize*i), FILE_NAME, FILE_LINE, pFunction);
    }
    stbds_strreset_func(&stbds_hash_table(a)->string STBDS_FN_ALLOC_PARAMS);
  }
  tf_free_internal(stbds_header(a)->hash_table, FILE_NAME, FILE_LINE, pFunction);
  tf_free_internal(stbds_mem_begin(a), FILE_NAME, FILE_LINE, pFunction);
}

static ptrdiff_t stbds_hm_find_slot(void *a, size_t elemsize, const void *key, size_t keysize, size_t keyoffset, int mode)
{
  void *raw_a = STBDS_HASH_TO_ARR(a,elemsize);
  stbds_hash_index *table = stbds_hash_table(raw_a);
  size_t hash = 0;
  STBDS_HM_DISPATCH_ASSIGN(mode, hash, _hash, key, keysize, table->seed);
  size_t step = STBDS_BUCKET_LENGTH;
  size_t limit,i;
  size_t pos;
  stbds_hash_bucket *bucket;

  if (hash < 2) hash += 2; // stored hash values are forbidden from being 0, so we can detect empty slots

  pos = stbds_probe_position(hash, table->slot_count, table->slot_count_log2);

  for (;;) {
    STBDS_STATS(++stbds_hash_probes);
    bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];

    // start searching from pos to end of bucket, this should help performance on small hash tables that fit in cache
    for (i=pos & STBDS_BUCKET_MASK; i < STBDS_BUCKET_LENGTH; ++i) {
      if (bucket->hash[i] == hash) {
        if (stbds_is_key_equal(a, elemsize, key, keysize, keyoffset, mode, bucket->index[i])) {
          return (pos & ~STBDS_BUCKET_MASK)+i;
        }
      } else if (bucket->hash[i] == STBDS_HASH_EMPTY) {
        return -1;
      }
    }

    // search from beginning of bucket to pos
    limit = pos & STBDS_BUCKET_MASK;
    for (i = 0; i < limit; ++i) {
      if (bucket->hash[i] == hash) {
        if (stbds_is_key_equal(a, elemsize, key, keysize, keyoffset, mode, bucket->index[i])) {
          return (pos & ~STBDS_BUCKET_MASK)+i;
        }
      } else if (bucket->hash[i] == STBDS_HASH_EMPTY) {
        return -1;
      }
    }

    // quadratic probing
    pos += step;
    step += STBDS_BUCKET_LENGTH;
    pos &= (table->slot_count-1);
  }
  /* NOTREACHED */
}

void * stbds_hmget_key_ts(void *a, size_t elemsize, size_t elemalign, const void *key, size_t keysize, ptrdiff_t *temp, int mode STBDS_FN_ALLOC_ARGS)
{
  size_t keyoffset = 0;
  if (a == NULL) {
    // make it non-empty so we can return a temp
    a = stbds_arrgrowf(0, elemsize, elemalign, 0, 1 STBDS_FN_ALLOC_PARAMS);
    stbds_header(a)->length += 1;
    memset(a, 0, elemsize);
    *temp = STBDS_INDEX_EMPTY;
    // adjust a to point after the default element
    return STBDS_ARR_TO_HASH(a,elemsize);
  } else {
    stbds_hash_index *table;
    void *raw_a = STBDS_HASH_TO_ARR(a,elemsize);
    // adjust a to point to the default element
    table = (stbds_hash_index *) stbds_header(raw_a)->hash_table;
    if (table == 0) {
      *temp = -1;
    } else {
      ptrdiff_t slot = stbds_hm_find_slot(a, elemsize, key, keysize, keyoffset, mode);
      if (slot < 0) {
        *temp = STBDS_INDEX_EMPTY;
      } else {
        stbds_hash_bucket *b = &table->storage[slot >> STBDS_BUCKET_SHIFT];
        *temp = b->index[slot & STBDS_BUCKET_MASK];
      }
    }
    return a;
  }
}

void * stbds_hmget_key(void *a, size_t elemsize, size_t elemalign, const void *key, size_t keysize, int mode STBDS_FN_ALLOC_ARGS)
{
  ptrdiff_t temp;
  void *p = stbds_hmget_key_ts(a, elemsize, elemalign, key, keysize, &temp, mode STBDS_FN_ALLOC_PARAMS);
  stbds_temp(STBDS_HASH_TO_ARR(p,elemsize)) = temp;
  return p;
}

void * stbds_hmput_default(void *a, size_t elemsize, size_t elemalign STBDS_FN_ALLOC_ARGS)
{
  // three cases:
  //   a is NULL <- allocate
  //   a has a hash table but no entries, because of shmode <- grow
  //   a has entries <- do nothing
  if (a == NULL || stbds_header(STBDS_HASH_TO_ARR(a,elemsize))->length == 0) {
    a = stbds_arrgrowf(a ? STBDS_HASH_TO_ARR(a,elemsize) : NULL, elemsize, elemalign, 0, 1 STBDS_FN_ALLOC_PARAMS);
    stbds_header(a)->length += 1;
    memset(a, 0, elemsize);
    a=STBDS_ARR_TO_HASH(a,elemsize);
  }
  return a;
}

static char *stbds_strdup(char *str STBDS_FN_ALLOC_ARGS);

void *stbds_hmput_key(void *a, size_t elemsize, size_t elemalign, const void *key, size_t keysize, int mode STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif

  size_t keyoffset=0;
  void *raw_a;
  stbds_hash_index *table;

  if (a == NULL) {
    a = stbds_arrgrowf(0, elemsize, elemalign, 0, 1 STBDS_FN_ALLOC_PARAMS);
    memset(a, 0, elemsize);
    stbds_header(a)->length += 1;
    // adjust a to point AFTER the default element
    a = STBDS_ARR_TO_HASH(a,elemsize);
  }

  // adjust a to point to the default element
  raw_a = a;
  a = STBDS_HASH_TO_ARR(a,elemsize);

  table = (stbds_hash_index *) stbds_header(a)->hash_table;

  if (table == NULL || table->used_count >= table->used_count_threshold) {
    stbds_hash_index *nt;
    size_t slot_count;

    slot_count = (table == NULL) ? STBDS_BUCKET_LENGTH : table->slot_count*2;
    nt = stbds_make_hash_index(slot_count, table STBDS_FN_ALLOC_PARAMS);
    if (table)
      tf_free_internal(table, FILE_NAME, FILE_LINE, pFunction);
	else
	{
		STBDS_HM_DISPATCH_ASSIGN(mode, nt->string.mode, _default_storage_mode);
	}
      
    stbds_header(a)->hash_table = table = nt;
    STBDS_STATS(++stbds_hash_grow);
  }

  // we iterate hash table explicitly because we want to track if we saw a tombstone
  {
	size_t hash = 0;
	STBDS_HM_DISPATCH_ASSIGN(mode, hash, _hash, key, keysize, table->seed);
    size_t step = STBDS_BUCKET_LENGTH;
    size_t pos;
    ptrdiff_t tombstone = -1;
    stbds_hash_bucket *bucket;

    // stored hash values are forbidden from being 0, so we can detect empty slots to early out quickly
    if (hash < 2) hash += 2;

    pos = stbds_probe_position(hash, table->slot_count, table->slot_count_log2);

    for (;;) {
      size_t limit, i;
      STBDS_STATS(++stbds_hash_probes);
      bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];

      // start searching from pos to end of bucket
      for (i=pos & STBDS_BUCKET_MASK; i < STBDS_BUCKET_LENGTH; ++i) {
        if (bucket->hash[i] == hash) {
          if (stbds_is_key_equal(raw_a, elemsize, key, keysize, keyoffset, mode, bucket->index[i])) {
            stbds_temp(a) = bucket->index[i];
            if (mode == STBDS_HM_STRING)
              stbds_temp_key(a) = * (char **) ((char *) raw_a + elemsize*bucket->index[i] + keyoffset);
            return STBDS_ARR_TO_HASH(a,elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~STBDS_BUCKET_MASK) + i);
        }
      }

      // search from beginning of bucket to pos
      limit = pos & STBDS_BUCKET_MASK;
      for (i = 0; i < limit; ++i) {
        if (bucket->hash[i] == hash) {
          if (stbds_is_key_equal(raw_a, elemsize, key, keysize, keyoffset, mode, bucket->index[i])) {
            stbds_temp(a) = bucket->index[i];
            return STBDS_ARR_TO_HASH(a,elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~STBDS_BUCKET_MASK) + i);
        }
      }

      // quadratic probing
      pos += step;
      step += STBDS_BUCKET_LENGTH;
      pos &= (table->slot_count-1);
    }
   found_empty_slot:
    if (tombstone >= 0) {
      pos = tombstone;
      --table->tombstone_count;
    }
    ++table->used_count;

    {
      ptrdiff_t i = (ptrdiff_t) stbds_arrlen(a);
      // we want to do stbds_arraddn(1), but we can't use the macros since we don't have something of the right type
      if ((size_t) i+1 > stbds_arrcap(a))
        *(void **) &a = stbds_arrgrowf(a, elemsize, elemalign, 1, 0 STBDS_FN_ALLOC_PARAMS);
      raw_a = STBDS_ARR_TO_HASH(a,elemsize);

      ASSERT((size_t) i+1 <= stbds_arrcap(a));
      stbds_header(a)->length = i+1;
      bucket = &table->storage[pos >> STBDS_BUCKET_SHIFT];
      bucket->hash[pos & STBDS_BUCKET_MASK] = hash;
      bucket->index[pos & STBDS_BUCKET_MASK] = i-1;
      stbds_temp(a) = i-1;

      switch (table->string.mode) {
         case STBDS_SH_STRDUP:  stbds_temp_key(a) = *(char **) ((char *) a + elemsize*i) = stbds_strdup((char*) key STBDS_FN_ALLOC_PARAMS); break;
         case STBDS_SH_ARENA:   stbds_temp_key(a) = *(char **) ((char *) a + elemsize*i) = stbds_stralloc_func(&table->string, (char*)key STBDS_FN_ALLOC_PARAMS); break;
         case STBDS_SH_DEFAULT: stbds_temp_key(a) = *(char **) ((char *) a + elemsize*i) = (char *) key; break;
         default:                memcpy((char *) a + elemsize*i, key, keysize); break;
      }
    }
    return STBDS_ARR_TO_HASH(a,elemsize);
  }
}

void * stbds_shmode_func(size_t elemsize, size_t elemalign, int mode STBDS_FN_ALLOC_ARGS)
{
  void *a = stbds_arrgrowf(0, elemsize, elemalign, 0, 1 STBDS_FN_ALLOC_PARAMS);
  stbds_hash_index *h;
  memset(a, 0, elemsize);
  stbds_header(a)->length = 1;
  stbds_header(a)->hash_table = h = (stbds_hash_index *) stbds_make_hash_index(STBDS_BUCKET_LENGTH, NULL STBDS_FN_ALLOC_PARAMS);
  h->string.mode = (unsigned char) mode;
  return STBDS_ARR_TO_HASH(a,elemsize);
}

void * stbds_hmdel_key(void *a, size_t elemsize, const void *key, size_t keysize, size_t keyoffset, int mode STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif

  if (a == NULL) {
    return 0;
  } else {
    stbds_hash_index *table;
    void *raw_a = STBDS_HASH_TO_ARR(a,elemsize);
    table = (stbds_hash_index *) stbds_header(raw_a)->hash_table;
    stbds_temp(raw_a) = 0;
    if (table == 0) {
      return a;
    } else {
      ptrdiff_t slot;
      slot = stbds_hm_find_slot(a, elemsize, key, keysize, keyoffset, mode);
      if (slot < 0)
        return a;
      else {
        stbds_hash_bucket *b = &table->storage[slot >> STBDS_BUCKET_SHIFT];
        int i = slot & STBDS_BUCKET_MASK;
        ptrdiff_t old_index = b->index[i];
        ptrdiff_t final_index = (ptrdiff_t) stbds_arrlen(raw_a)-1-1; // minus one for the raw_a vs a, and minus one for 'last'
        ASSERT(slot < (ptrdiff_t) table->slot_count);
        --table->used_count;
        ++table->tombstone_count;
        stbds_temp(raw_a) = 1;
        ASSERT(table->used_count >= 0);
        //ASSERT(table->tombstone_count < table->slot_count/4);
        b->hash[i] = STBDS_HASH_DELETED;
        b->index[i] = STBDS_INDEX_DELETED;

		STBDS_HM_DISPATCH(mode, _free_key, table, ((char *)a + elemsize * old_index), keysize STBDS_FN_ALLOC_PARAMS);

        // if indices are the same, memcpy is a no-op, but back-pointer-fixup will fail, so skip
        if (old_index != final_index) {
          // swap delete
          memmove((char*) a + elemsize*old_index, (char*) a + elemsize*final_index, elemsize);

          // now find the slot for the last element
		  STBDS_HM_DISPATCH_ASSIGN(mode, slot, _find_slot, a, elemsize,
			  (char*)a + elemsize * old_index + keyoffset, keysize, keyoffset, mode);

          ASSERT(slot >= 0);
          b = &table->storage[slot >> STBDS_BUCKET_SHIFT];
          i = slot & STBDS_BUCKET_MASK;
          ASSERT(b->index[i] == final_index);
          b->index[i] = old_index;
        }
        stbds_header(raw_a)->length -= 1;

        if (table->used_count < table->used_count_shrink_threshold && table->slot_count > STBDS_BUCKET_LENGTH) {
          stbds_header(raw_a)->hash_table = stbds_make_hash_index(table->slot_count>>1, table STBDS_FN_ALLOC_PARAMS);
          tf_free_internal(table, FILE_NAME, FILE_LINE, pFunction);
          STBDS_STATS(++stbds_hash_shrink);
        } else if (table->tombstone_count > table->tombstone_count_threshold) {
          stbds_header(raw_a)->hash_table = stbds_make_hash_index(table->slot_count, table STBDS_FN_ALLOC_PARAMS);
		  tf_free_internal(table, FILE_NAME, FILE_LINE, pFunction);
          STBDS_STATS(++stbds_hash_rebuild);
        }

        return a;
      }
    }
  }
  /* NOTREACHED */
}

static char *stbds_strdup(char *str STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif

  // to keep replaceable allocator simple, we don't want to use strdup.
  // rolling our own also avoids problem of strdup vs _strdup
  size_t len = strlen(str)+1;
  char *p = (char*) tf_realloc_internal(NULL, len, FILE_NAME, FILE_LINE, pFunction);
  memmove(p, str, len);
  return p;
}

#ifndef STBDS_STRING_ARENA_BLOCKSIZE_MIN
#define STBDS_STRING_ARENA_BLOCKSIZE_MIN  512u
#endif
#ifndef STBDS_STRING_ARENA_BLOCKSIZE_MAX
#define STBDS_STRING_ARENA_BLOCKSIZE_MAX  (1u<<20)
#endif

#ifdef __clang__
#ifdef __has_feature
__attribute__((no_sanitize("bounds")))
#endif
#endif
inline static char* stbds_string_arena_offset(stbds_string_arena *a, size_t offset)
{
  return a->storage->storage + offset;
}

char *stbds_stralloc_func(stbds_string_arena *a, char *str STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif

  char *p;
  size_t len = strlen(str)+1;
  if (len > a->remaining) {
    // compute the next blocksize
    size_t blocksize = a->block;

    // size is 512, 512, 1024, 1024, 2048, 2048, 4096, 4096, etc., so that
    // there are log(SIZE) allocations to free when we destroy the table
    blocksize = (size_t) (STBDS_STRING_ARENA_BLOCKSIZE_MIN) << (blocksize>>1);

    // if size is under 1M, advance to next blocktype
    if (blocksize < (size_t)(STBDS_STRING_ARENA_BLOCKSIZE_MAX))
      ++a->block;

    if (len > blocksize) {
      // if string is larger than blocksize, then just allocate the full size.
      // note that we still advance string_block so block size will continue
      // increasing, so e.g. if somebody only calls this with 1000-long strings,
      // eventually the arena will start doubling and handling those as well
      stbds_string_block *sb = (stbds_string_block *) tf_realloc_internal(NULL, sizeof(*sb)-8 + len, FILE_NAME, FILE_LINE, pFunction);
      memmove(sb->storage, str, len);
      if (a->storage) {
        // insert it after the first element, so that we don't waste the space there
        sb->next = a->storage->next;
        a->storage->next = sb;
      } else {
        sb->next = 0;
        a->storage = sb;
        a->remaining = 0; // this is redundant, but good for clarity
      }
      return sb->storage;
    } else {
      stbds_string_block *sb = (stbds_string_block *) tf_realloc_internal(NULL, sizeof(*sb)-8 + blocksize, FILE_NAME, FILE_LINE, pFunction);
      sb->next = a->storage;
      a->storage = sb;
      a->remaining = blocksize;
    }
  }

  ASSERT(len <= a->remaining);
  p = stbds_string_arena_offset(a, a->remaining - len);
  a->remaining -= len;
  memmove(p, str, len);
  return p;
}

void stbds_strreset_func(stbds_string_arena *a STBDS_FN_ALLOC_ARGS)
{
#ifdef ENABLE_MEMORY_TRACKING
	unsigned char fnNameBuf[256];
	bstring fnName = bemptyfromarr(fnNameBuf);
	bformat(&fnName, "%s(propagated from %s)", FUNCTION_NAME, PARENT_FUNCTION_NAME);
	ASSERT(!bownsdata(&fnName));
	const char* pFunction = (const char*)fnName.data;
#else
	#define FILE_NAME __FILE__
	#define FILE_LINE  __LINE__
	#define FUNCTION_NAME __FUNCTION__
	const char* pFunction = FUNCTION_NAME;
#endif

  stbds_string_block *x,*y;
  ASSERT(a);
  x = a->storage;
  while (x) {
    y = x->next;
	tf_free_internal(x, FILE_NAME, FILE_LINE, pFunction);
    x = y;
  }
  memset(a, 0, sizeof(*a));
}

#endif

//////////////////////////////////////////////////////////////////////////////
//
//   UNIT TESTS
//

#ifdef STBDS_UNIT_TESTS
#include <stdio.h>
#include "../../../Interfaces/ILog.h"

typedef struct { int key,b,c,d; } stbds_struct;
typedef struct { int key[2],b,c,d; } stbds_struct2;

static char buffer[256];
char *strkey(int n)
{
#if defined(_WIN32) && defined(__STDC_WANT_SECURE_LIB__)
   sprintf_s(buffer, sizeof(buffer), "test_%d", n);
#else
   snprintf(buffer,256, "test_%d", n);
#endif
   return buffer;
}

#ifdef _MSC_VER
#define STBDS_TEST_ALIGNMENT ( 1 << STBDS_MSVC_MAX_ALIGNMENT_POWER)
#else
#define STBDS_TEST_ALIGNMENT 64
#endif

typedef struct alignas(STBDS_TEST_ALIGNMENT) alignedStruct
{
	int key;
	int value;
}alignedStruct;

void stbds_unit_tests(void)
{
#if defined(_MSC_VER) && _MSC_VER <= 1200 && defined(__cplusplus)
  // VC6 C++ doesn't like the template<> trick on unnamed structures, so do nothing!
  ASSERT(0);
#else
  const int testsize = 100000;
  int *arr=NULL;
  static const alignedStruct                alignedVal = { 0,0 };
  alignedStruct                            *aligned = NULL;
  struct { int   key;        int value; }  *intmap  = NULL;
  struct { char *key;        int value; }  *strmap  = NULL, s;
  struct { stbds_struct key; int value; }  *map     = NULL;
  stbds_struct                             *map2    = NULL;
  stbds_struct2                            *map3    = NULL;
  stbds_string_arena                        sa      = { 0 };

  ptrdiff_t temp;

  int i,j;

  ASSERT(arrlen(arr)==0);
  for (i=0; i < 20000; i += 50) {
	  for (j = 0; j < i; ++j)
	  {
		  arrpush(arr, j);
	  }
    arrfree(arr);
  }

  for (i=0; i < 4; ++i) {
    arrpush(arr,1); arrpush(arr,2); arrpush(arr,3); arrpush(arr,4);
    arrdel(arr,i);
    arrfree(arr);
    arrpush(arr,1); arrpush(arr,2); arrpush(arr,3); arrpush(arr,4);
    arrdelswap(arr,i);
    arrfree(arr);
  }

  for (i=0; i < 5; ++i) {
    arrpush(arr,1); arrpush(arr,2); arrpush(arr,3); arrpush(arr,4);
    stbds_arrins(arr,i,5);
    ASSERT(arr[i] == 5);
	if (i < 4) { ASSERT(arr[4] == 4); }
    arrfree(arr);
  }

  i = 1;
  ASSERT(hmgeti(intmap,i) == -1);
  hmdefault(intmap, -2);
  ASSERT(hmgeti(intmap, i) == -1);
  ASSERT(hmget (intmap, i) == -2);
  for (i=0; i < testsize; i+=2)
    hmput(intmap, i, i*5);
  int res = INT_MAX;
  for (i=0; i < testsize; i+=1) {
	  if (i & 1) { ASSERT((res = hmget(intmap, i)) == -2);             }
	  else       { ASSERT((res = hmget(intmap, i)) == i * 5);          }
	  if (i & 1) { ASSERT((res = hmget_ts(intmap, i, temp)) == -2);    }
	  else       { ASSERT((res = hmget_ts(intmap, i, temp)) == i * 5); }
  }
  for (i=0; i < testsize; i+=2)
    hmput(intmap, i, i*3);
  for (i=0; i < testsize; i+=1)
	  if (i & 1) { ASSERT(hmget(intmap, i) == -2); }
	  else       { ASSERT(hmget(intmap, i) == i * 3); }
  for (i=2; i < testsize; i+=4)
    hmdel(intmap, i); // delete half the entries
  for (i=0; i < testsize; i+=1)
    if (i & 3) { ASSERT(hmget(intmap, i) == -2 ); }
    else       { ASSERT(hmget(intmap, i) == i*3); }
  for (i=0; i < testsize; i+=1)
    hmdel(intmap, i); // delete the rest of the entries
  for (i = 0; i < testsize; i += 1)
  {
	  ASSERT(hmget(intmap, i) == -2);
  }
  hmfree(intmap);
  for (i=0; i < testsize; i+=2)
    hmput(intmap, i, i*3);
  hmfree(intmap);

  #if defined(__clang__) || defined(__GNUC__)
  #ifndef __cplusplus
  intmap = NULL;
  hmput(intmap, 15, 7);
  hmput(intmap, 11, 3);
  hmput(intmap,  9, 5);
  ASSERT(hmget(intmap, 9) == 5);
  ASSERT(hmget(intmap, 11) == 3);
  ASSERT(hmget(intmap, 15) == 7);
  #endif
  #endif

  for (i=0; i < testsize; ++i)
    stralloc(&sa, strkey(i));
  strreset(&sa);

  {
    s.key = (char*)"a", s.value = 1;
    shputs(strmap, s);
    ASSERT(*strmap[0].key == 'a');
    ASSERT(strmap[0].key == s.key);
    ASSERT(strmap[0].value == s.value);
    shfree(strmap);
  }

  {
    s.key = (char*)"a", s.value = 1;
    sh_new_strdup(strmap);
    shputs(strmap, s);
    ASSERT(*strmap[0].key == 'a');
    ASSERT(strmap[0].key != s.key);
    ASSERT(strmap[0].value == s.value);
    shfree(strmap);
  }

  {
    s.key = (char*)"a", s.value = 1;
    sh_new_arena(strmap);
    shputs(strmap, s);
    ASSERT(*strmap[0].key == 'a');
    ASSERT(strmap[0].key != s.key);
    ASSERT(strmap[0].value == s.value);
    shfree(strmap);
  }

  for (j=0; j < 2; ++j) {
    ASSERT(shgeti(strmap,"foo") == -1);

    if (j == 0)
      sh_new_strdup(strmap);
    else
      sh_new_arena(strmap);
    ASSERT(shgeti(strmap,"foo") == -1);
    shdefault(strmap, -2);
    ASSERT(shgeti(strmap,"foo") == -1);
    for (i=0; i < testsize; i+=2)
      shput(strmap, strkey(i), i*3);
    for (i=0; i < testsize; i+=1)
		if (i & 1) { ASSERT(shget(strmap, strkey(i)) == -2);    }
		else       { ASSERT(shget(strmap, strkey(i)) == i * 3); }
    for (i=2; i < testsize; i+=4)
      shdel(strmap, strkey(i)); // delete half the entries
    for (i=0; i < testsize; i+=1)
      if (i & 3) { ASSERT(shget(strmap, strkey(i)) == -2 ); }
      else       { ASSERT(shget(strmap, strkey(i)) == i*3); }
    for (i=0; i < testsize; i+=1)
      shdel(strmap, strkey(i)); // delete the rest of the entries
	for (i = 0; i < testsize; i += 1)
	{
		ASSERT(shget(strmap, strkey(i)) == -2);
	}
    shfree(strmap);
  }

  {
    struct { char *key; char value; } *hash = NULL;
    char name[4] = "jen";
    shput(hash, "bob"   , 'h');
    shput(hash, "sally" , 'e');
    shput(hash, "fred"  , 'l');
    shput(hash, "jen"   , 'x');
    shput(hash, "doug"  , 'o');

    shput(hash, name    , 'l');
    shfree(hash);
  }

  for (i=0; i < testsize; i += 2) {
    stbds_struct s = { i,i*2,i*3,i*4 };
    hmput(map, s, i*5);
  }

  for (i=0; i < testsize; i += 1) {
    stbds_struct s = { i,i*2,i*3  ,i*4 };
    if (i & 1) { ASSERT(hmget(map, s) == 0);			  }
    else       { ASSERT(hmget(map, s) == i*5);		  }
    if (i & 1) { ASSERT(hmget_ts(map, s, temp) == 0);	  }
    else       { ASSERT(hmget_ts(map, s, temp) == i*5); }
  }
  hmfree(map);

  for (i=0; i < testsize; i += 2) {
    stbds_struct s = { i,i*2,i*3,i*4 };
    hmputs(map2, s);
  }
  hmfree(map);

  for (i=0; i < testsize; i += 1) {
    stbds_struct s = { i,i*2,i*3,i*4 };
    if (i & 1) { ASSERT(hmgets(map2, s.key).d == 0);	 }
    else       { ASSERT(hmgets(map2, s.key).d == i*4); }
  }
  hmfree(map2);

  for (i=0; i < testsize; i += 2) {
    stbds_struct2 s = { { i,i*2 }, i*3,i*4, i*5 };
    hmputs(map3, s);
  }
  for (i=0; i < testsize; i += 1) {
    stbds_struct2 s = { { i,i*2}, i*3, i*4, i*5 };
    if (i & 1) { ASSERT(hmgets(map3, s.key).d == 0);	 }
    else       { ASSERT(hmgets(map3, s.key).d == i*5); }
  }
  hmfree(map3);


  arrpush(aligned, alignedVal);
  ptrdiff_t ptrVal = (ptrdiff_t)aligned;
  ASSERT(ptrVal % ALIGNOF(alignedStruct) == 0);

  arrfree(aligned);

  hmputs(aligned, alignedVal);
  ptrVal = (ptrdiff_t)aligned;
  ASSERT(ptrVal % ALIGNOF(alignedStruct) == 0);
  hmfree(aligned);

#endif
}
#endif


/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2019 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
