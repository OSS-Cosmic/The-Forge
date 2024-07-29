#pragma once
#ifndef TF_MATH_INTERNAL_SIMDTYPE_H_
#define TF_MATH_INTERNAL_SIMDTYPE_H_

#include "Forge/TF_Config.h"
#include "Forge/TF_Types.h"

#if defined(TF_FEATURE_CPU_SSE) 
    #include <xmmintrin.h>
    #include <pmmintrin.h>
    #include <emmintrin.h>
    #include <smmintrin.h>
   
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    #define TF_SIMDF_MAX 0xFFFFFFFF

    typedef __m128 TSimdf32x4;
    typedef __m128i TSimdi32x4;

    typedef __m128 TSimdf32x3;
    typedef __m128i TSimdi32x3;

    typedef __m128 TSimdf32x2;
    typedef __m128i TSimdi32x2;
#elif defined(TF_FEATURE_CPU_NEON)
    #include <arm_neon.h>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef float32x4_t TSimdf32x4;
    typedef int32x4_t TSimdi32x4;

    typedef float32x4_t TSimdf32x3;
    typedef int32x4_t TSimdi32x3;

    typedef float32x2_t TSimdf32x2;
    typedef int32x2_t TSimdi32x2;
#elif defined(TF_FEATURE_CPU_SCALAR)
    #include <cmath>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef struct { float   v[4]; } TSimdf32x4;
    typedef struct { int32_t v[4]; } TSimdi32x4;

    typedef struct { float   v[3]; } TSimdf32x3;
    typedef struct { int32_t v[3]; } TSimdi32x3;
    
    typedef struct { float   v[2]; } TSimdf32x2;
    typedef struct { int32_t v[2]; } TSimdi32x2;
#endif

struct simd_float4
{
  TSimdf32x4 mCol0; 
};

struct simd_float4x2
{
  TSimdf32x4 mCol0; 
  TSimdf32x4 mCol1; 
};

struct simd_float4x3
{
  TSimdf32x4 mCol0; 
  TSimdf32x4 mCol1; 
  TSimdf32x4 mCol2; 
};

struct simd_float4x4
{
  TSimdf32x4 mCol0; 
  TSimdf32x4 mCol1; 
  TSimdf32x4 mCol2; 
  TSimdf32x4 mCol3; 
};


#endif
