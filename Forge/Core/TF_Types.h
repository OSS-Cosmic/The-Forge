#ifndef _TF_TYPES_H
#define _TF_TYPES_H

#include <cstddef>
#include <stdint.h>
#include <cstdarg>

#define TF_ARRAY_COUNT(array) (sizeof(array) / (sizeof(array[0]) * (sizeof(array) != PTR_SIZE || sizeof(array[0]) <= PTR_SIZE)))
#ifndef TF_MIN
#define TF_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef TF_MAX
#define TF_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifdef __cplusplus
#define TF_FORGE_CONSTEXPR constexpr
#define TF_FORGE_EXTERN_C  extern "C"
#else
#define TF_FORGE_CONSTEXPR
#define TF_FORGE_EXTERN_C
#endif

#ifdef __cplusplus
#ifndef TF_ENUM_FLAG
#define TF_ENUM_FLAG(TYPE, ENUM_TYPE)                                                                                      \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator|(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) | ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator|=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) |= ((TYPE)b)); } \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator&(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) & ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator&=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) &= ((TYPE)b)); } \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator~(ENUM_TYPE a) { return ENUM_TYPE(~((TYPE)a)); }                                \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator^(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) ^ ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator^=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) ^= ((TYPE)b)); }
#endif
#else
#define TF_ENUM_FLAG(TYPE, ENUM_TYPE)
#endif

#endif
