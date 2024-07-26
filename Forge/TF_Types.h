
#pragma once
#ifndef _TF_TYPES_H
#define _TF_TYPES_H

#include <cstddef>
#include <stdint.h>
#include <cstdarg>

#if INTPTR_MAX == 0x7FFFFFFFFFFFFFFFLL
  #define TF_PTR_SIZE 8
#elif INTPTR_MAX == 0x7FFFFFFF
  #define TF_PTR_SIZE 4
#else
  #error unsupported platform
#endif

#define TF_ALIGN_TO(size, alignment) (((size) + (alignment)-1) & ~((alignment)-1))
#define TF_ARRAY_COUNT(array) (sizeof(array) / (sizeof(array[0]) * (sizeof(array) != TF_PTR_SIZE || sizeof(array[0]) <= TF_PTR_SIZE)))
#define TF_MIN(a, b) ((a) < (b) ? (a) : (b))
#define TF_MAX(a, b) ((a) > (b) ? (a) : (b))

#ifdef __cplusplus
#define TF_FORGE_CONSTEXPR constexpr
#define TF_FORGE_EXTERN_C  extern "C"
#else
#define TF_FORGE_CONSTEXPR
#define TF_FORGE_EXTERN_C
#endif

#ifdef __cplusplus
#define TF_ENUM_FLAG(TYPE, ENUM_TYPE)                                                                                      \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator|(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) | ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator|=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) |= ((TYPE)b)); } \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator&(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) & ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator&=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) &= ((TYPE)b)); } \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator~(ENUM_TYPE a) { return ENUM_TYPE(~((TYPE)a)); }                                \
    inline TF_FORGE_CONSTEXPR ENUM_TYPE operator^(ENUM_TYPE a, ENUM_TYPE b) { return ENUM_TYPE(((TYPE)a) ^ ((TYPE)b)); }        \
    inline ENUM_TYPE&                operator^=(ENUM_TYPE& a, ENUM_TYPE b) { return (ENUM_TYPE&)(((TYPE&)a) ^= ((TYPE)b)); }
#else
#define TF_ENUM_FLAG(TYPE, ENUM_TYPE)
#endif

#ifdef __cplusplus
#define TF_FORGE_CONSTEXPR constexpr
#define TF_FORGE_EXTERN_C  extern "C"
#else
#define TF_FORGE_CONSTEXPR
#define TF_FORGE_EXTERN_C
#endif

#if defined(__clang__) && !defined(__cplusplus)
#define TF_COMPILE_ASSERT(exp) _Static_assert(exp, #exp)
#else
#define TF_COMPILE_ASSERT(exp) static_assert(exp, #exp)
#endif

#if defined(_MSC_VER)
#define TF_FORGE_EXPORT __declspec(dllexport)
#define TF_FORGE_IMPORT __declspec(dllimport)
#elif defined(__GNUC__) // clang & gcc
#define TF_FORGE_EXPORT __attribute__((visibility("default")))
#define TF_FORGE_IMPORT
#endif

#endif
