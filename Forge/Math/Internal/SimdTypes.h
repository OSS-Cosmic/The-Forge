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

    typedef __m128 TSimdFloat4;
    typedef __m128i TSimdInt4;

    typedef __m128 TSimdFloat3;
    typedef __m128i TSimdInt3;

    typedef __m128 TSimdFloat2;
    typedef __m128i TSimdInt2;
#elif defined(TF_FEATURE_CPU_NEON)
    #include <arm_neon.h>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef float32x4_t TSimdFloat4;
    typedef int32x4_t TSimdInt4;

    typedef float32x4_t TSimdFloat3;
    typedef int32x4_t TSimdInt3;

    typedef float32x2_t TSimdFloat2;
    typedef int32x2_t TSimdInt2;
#elif defined(TF_FEATURE_CPU_SCALAR)
    #include <cmath>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef struct { float   v[4]; } TSimdFloat4;
    typedef struct { int32_t v[4]; } TSimdInt4;

    typedef struct { float   v[3]; } TSimdFloat3;
    typedef struct { int32_t v[3]; } TSimdInt3;
    
    typedef struct { float   v[2]; } TSimdFloat2;
    typedef struct { int32_t v[2]; } TSimdInt2;
#endif

// TODO: keep it simple only implement square matricies
// everything is column major

//struct TSimdFloat4x2
//{
//  TSimdFloat4 mCol0; 
//  TSimdFloat4 mCol1; 
//};
//
//struct TSimdFloat4x3
//{
//  TSimdFloat4 mCol0; 
//  TSimdFloat4 mCol1; 
//  TSimdFloat4 mCol2; 
//};

struct TSimdFloat4x4
{
  TSimdFloat4 mCol0; 
  TSimdFloat4 mCol1; 
  TSimdFloat4 mCol2; 
  TSimdFloat4 mCol3; 
};

//struct TSimdFloat3
//{
//  TSimdFloat3 mCol0; 
//};
//
//struct TSimdFloat3x2
//{
//  TSimdFloat3 mCol0; 
//  TSimdFloat3 mCol1; 
//};

struct TSimdFloat3x3
{
  TSimdFloat3 mCol0; 
  TSimdFloat3 mCol1; 
  TSimdFloat3 mCol2; 
};

//struct TSimdFloat3x4
//{
//  TSimdFloat3 mCol0; 
//  TSimdFloat3 mCol1; 
//  TSimdFloat3 mCol2; 
//  TSimdFloat3 mCol3; 
//};


struct TSimdFloat2x2
{
  TSimdFloat2 mCol0; 
  TSimdFloat2 mCol1; 
};

//struct TSimdFloat2x3
//{
//  TSimdFloat2 mCol0; 
//  TSimdFloat2 mCol1; 
//  TSimdFloat2 mCol2; 
//};
//
//struct TSimdFloat2x4
//{
//  TSimdFloat2 mCol0; 
//  TSimdFloat2 mCol1; 
//  TSimdFloat2 mCol2; 
//  TSimdFloat2 mCol3; 
//};


#endif
