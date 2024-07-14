#ifndef _TF_TYPES_H
#define _TF_TYPES_H

#include <cstddef>
#include <stdint.h>
#include <cstdarg>

#define TF_ARRAY_COUNT(array) (sizeof(array) / (sizeof(array[0]) * (sizeof(array) != PTR_SIZE || sizeof(array[0]) <= PTR_SIZE)))


#ifdef __cplusplus
#ifndef TF_ENUM_FLAG
#define TF_ENUM_FLAG(TYPE, ENUM_TYPE)                                                                                      \
    inline FORGE_CONSTEXPR ENUM_TYPE operator|(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) | ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator|=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) |= ((TYPE)b)); } \
    inline FORGE_CONSTEXPR ENUM_TYPE operator&(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) & ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator&=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) &= ((TYPE)b)); } \
    inline FORGE_CONSTEXPR ENUM_TYPE operator~(ENUM_TYPE a) { return ENUM_TYPE(~((TYPE)a)); }                                \
    inline FORGE_CONSTEXPR ENUM_TYPE operator^(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) ^ ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator^=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) ^= ((TYPE)b)); }
#endif
#else
#define TF_ENUM_FLAG(TYPE, ENUM_TYPE)
#endif

#endif
