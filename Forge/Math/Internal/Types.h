#include "Forge/TF_Config.h"
#include "Forge/TF_Types.h"

#pragma once
#ifndef TF_MATH_INTERNAL_TYPE_H_INCLUDED
#define TF_MATH_INTERNAL_TYPE_H_INCLUDED

#if defined(TF_FEATURE_CPU_SSE) 
    #include <xmmintrin.h>
    #include <pmmintrin.h>
    #include <emmintrin.h>
    #include <smmintrin.h>
    
    typedef __m128 Simd_FloatType4;
    typedef __m128i Simd_Int32Type4;

    typedef __m128 Simd_FloatType3;
    typedef __m128i Simd_Int32Type3;

    typedef __m128 Simd_FloatType2;
    typedef __m128i Simd_Int32Type2;

    typedef __m128 Simd_FloatType;
    typedef __m128i Simd_Int32Type;
#elif defined(TF_FEATURE_CPU_NEON)
    #include <arm_neon.h>
    
    typedef float32x4_t Simd_FloatType4;
    typedef int32x4_t Simd_Int32Type4;

    typedef float32x4_t Simd_FloatType3;
    typedef int32x4_t Simd_Int32Type3;

    typedef float32x2_t Simd_FloatType2;
    typedef int32x2_t Simd_Int32Type2;
    
    typedef float Simd_FloatType;
    typedef int32_t Simd_Int32Type;
#elif defined(TF_FEATURE_CPU_SCALAR)
    typedef struct { float   v[4]; } Simd_FloatType4;
    typedef struct { int32_t v[4]; } Simd_Int32Type4;

    typedef struct { float   v[3]; } Simd_FloatType3;
    typedef struct { int32_t v[3]; } Simd_Int32Type3;
    
    typedef struct { float   v[2]; } Simd_FloatType2;
    typedef struct { int32_t v[2]; } Simd_Int32Type2;
    
    typedef float Simd_FloatType;
    typedef int32_t Simd_Int32Type;
#endif

#endif
