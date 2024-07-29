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

    typedef __m128 TSimdFloat32x4;
    typedef __m128i TSimdInt32x4;

    typedef __m128 TSimdFloat32x3;
    typedef __m128i TSimdInt32x3;

    typedef __m128 TSimdFloat32x2;
    typedef __m128i TSimdInt32x2;
#elif defined(TF_FEATURE_CPU_NEON)
    #include <arm_neon.h>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef float32x4_t TSimdFloat32x4;
    typedef int32x4_t TSimdInt32x4;

    typedef float32x4_t TSimdFloat32x3;
    typedef int32x4_t TSimdInt32x3;

    typedef float32x2_t TSimdFloat32x2;
    typedef int32x2_t TSimdInt32x2;
#elif defined(TF_FEATURE_CPU_SCALAR)
    #include <cmath>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef struct { float   v[4]; } TSimdFloat32x4;
    typedef struct { int32_t v[4]; } TSimdInt32x4;

    typedef struct { float   v[3]; } TSimdFloat32x3;
    typedef struct { int32_t v[3]; } TSimdInt32x3;
    
    typedef struct { float   v[2]; } TSimdFloat32x2;
    typedef struct { int32_t v[2]; } TSimdInt32x2;
#endif

// TODO: keep it simple only implement square matricies
// everything is column major

struct TSimdFloat4 {
  TSimdFloat32x4 mRow; 
};

struct TSimdQuatFloat {
  TSimdFloat32x4 mValue; 
};

struct TSimdFloat1x4 {
  TSimdFloat32x4 mCol0; 
};


struct TSimdFloat2x4 {
  TSimdFloat32x4 mCol0; 
  TSimdFloat32x4 mCol1; 
};

struct TSimdFloat3x4 {
  union {
    struct {
      TSimdFloat32x4 mCol0; 
      TSimdFloat32x4 mCol1; 
      TSimdFloat32x4 mCol2; 
    };
    TSimdFloat32x4 mCol[3]; 
  };
};

struct TSimdFloat4x4
{
  TSimdFloat32x4 mCol0; 
  TSimdFloat32x4 mCol1; 
  TSimdFloat32x4 mCol2; 
  TSimdFloat32x4 mCol3; 
};

struct TSimdFloat3
{
  TSimdFloat32x3 mValue; 
};

struct TSimdFloat1x3
{
  TSimdFloat32x3 mCol0; 
};

struct TSimdFloat2x3
{
  TSimdFloat32x3 mCol0; 
  TSimdFloat32x3 mCol1; 
};


struct TSimdFloat3x3
{
  TSimdFloat32x3 mCol0; 
  TSimdFloat32x3 mCol1; 
  TSimdFloat32x3 mCol2; 
};


struct TSimdFloat2 {
  TSimdFloat32x2 mValue; 
};

struct TSimdFloat1x2
{
  TSimdFloat32x2 mCol0; 
};

struct TSimdFloat2x2
{
  TSimdFloat32x2 mCol0; 
  TSimdFloat32x2 mCol1; 
};


#endif
