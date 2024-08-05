#pragma once
#ifndef TF_MATH_INTERNAL_SIMDTYPE_H_
#define TF_MATH_INTERNAL_SIMDTYPE_H_

#include "Forge/TF_Config.h"
#include "Forge/TF_Types.h"
#include <cmath>

#if defined(TF_FEATURE_CPU_SSE) 
    #include <xmmintrin.h>
    #include <pmmintrin.h>
    #include <emmintrin.h>
    #include <smmintrin.h>
   
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    #define TF_SIMDF_MAX 0xFFFFFFFF

    typedef __m128 Tsimd_f32x4_t;
    typedef __m128i Tsimd_i32x4_t;

    typedef __m128 Tsimd_f32x3_t;
    typedef __m128i Tsimd_i32x3_t;

    typedef __m128 Tsimd_f32x2_t;
    typedef __m128i Tsimd_i32x2_t;
#elif defined(TF_FEATURE_CPU_NEON)
    #include <arm_neon.h>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef float32x4_t Tsimd_f32x4_t;
    typedef int32x4_t Tsimd_i32x4_t;

    typedef float32x4_t Tsimd_f32x3_t;
    typedef int32x4_t Tsimd_i32x3_t;

    typedef float32x2_t Tsimd_f32x2_t;
    typedef int32x2_t Tsimd_i32x2_t;
#elif defined(TF_FEATURE_CPU_SCALAR)
    #include <cmath>
    
    #define TF_SIMD_TRUE 0xFFFFFFFF
    #define TF_SIMD_FALSE 0x0
    
    #define TF_SIMDI_MAX 0xFFFFFFFF
    
    typedef struct { float   v[4]; } Tsimd_f32x4_t;
    typedef struct { int32_t v[4]; } Tsimd_i32x4_t;

    typedef struct { float   v[3]; } Tsimd_f32x3_t;
    typedef struct { int32_t v[3]; } Tsimd_i32x3_t;
    
    typedef struct { float   v[2]; } Tsimd_f32x2_t;
    typedef struct { int32_t v[2]; } Tsimd_i32x2_t;
#endif

struct Tsimd_f32x4x4_s {
    union {
        struct {
            Tsimd_f32x4_t mCol0;
            Tsimd_f32x4_t mCol1;
            Tsimd_f32x4_t mCol2;
            Tsimd_f32x4_t mCol3;
        };
        Tsimd_f32x4_t mCol[4];
    };
};

struct Tsimd_f32x4x3_s {
    union {
        struct {
            Tsimd_f32x4_t mCol0;
            Tsimd_f32x4_t mCol1;
            Tsimd_f32x4_t mCol2;
        };
        Tsimd_f32x4_t mCol[3];
    };
};

struct Tsimd_f32x4x2_s {
    union {
        struct {
            Tsimd_f32x4_t mCol0;
            Tsimd_f32x4_t mCol1;
        };
        Tsimd_f32x4_t mCol[2];
    };
};


// deprecate anything past this 
// -------------------------------------------------------
//
struct TSimdFloat4x1 {
    union
    {
        struct
        {
            Tsimd_f32x4_t mCol0;
        };
        Tsimd_f32x4_t mCol[1];
    };
};

struct TSimdFloat4x2
{
    union
    {
        struct
        {
            Tsimd_f32x4_t mCol0;
            Tsimd_f32x4_t mCol1;
        };
        Tsimd_f32x4_t mCol[2];
    };
};

struct TSimdFloat4x3 {
  union {
    struct {
      Tsimd_f32x4_t mCol0; 
      Tsimd_f32x4_t mCol1; 
      Tsimd_f32x4_t mCol2; 
    };
    Tsimd_f32x4_t mCol[3]; 
  };
};

struct TSimdFloat4x4
{
    union
    {
        struct
        {
            Tsimd_f32x4_t mCol0;
            Tsimd_f32x4_t mCol1;
            Tsimd_f32x4_t mCol2;
            Tsimd_f32x4_t mCol3;
        };
        Tsimd_f32x4_t mCol[4];
    };
};

struct TSimdFloat3
{
  Tsimd_f32x3_t mRow; 
};

struct TSimdFloat3x1 {
    union {
        struct {
            Tsimd_f32x3_t mCol0;
        };
        Tsimd_f32x3_t mCol[1];
    };
};

struct TSimdFloat3x2
{
    union
    {
        struct
        {
            Tsimd_f32x3_t mCol0;
            Tsimd_f32x3_t mCol1;
        };
        Tsimd_f32x3_t mCol[2];
    };
};

struct TSimdFloat3x3
{
    union
    {
        struct
        {
            Tsimd_f32x3_t mCol0;
            Tsimd_f32x3_t mCol1;
            Tsimd_f32x3_t mCol2;
        };
        Tsimd_f32x3_t mCol[3];
    };
};

struct TSimdFloat2 {
  Tsimd_f32x2_t mRow; 
};

struct TSimdFloat2x1
{
    union {
        struct {
          Tsimd_f32x2_t mCol0; 
        };
        Tsimd_f32x2_t mCol[1];
    };
};

struct TSimdFloat2x2
{
    union {
        struct {
            Tsimd_f32x2_t mCol0;
            Tsimd_f32x2_t mCol1;
        };
        Tsimd_f32x2_t mCol[2];
    };
};



#endif
