#pragma once
#ifndef TF_MATH_SIMD_FLOAT_H
#define TF_MATH_SIMD_FLOAT_H

#include "Internal/SimdTypes.h"

static inline TSimdFloat4 tfVectorMul3x4F(const TSimdFloat4x3 a0, const TSimdFloat3 a1);

static inline TSimdFloat3 tfVectorMul3x3F(const TSimdFloat3x3 a0, const TSimdFloat3 a1);
static inline TSimdFloat2 tfVectorMul2x2F(const TSimdFloat2x2 a0, const TSimdFloat2 a1);

// -----------------------------------------------------------
// TSimdFloat2
// -----------------------------------------------------------
static inline TSimdFloat2 tfLoadSimd2F(float x, float y);

static inline TSimdFloat2 tfVectorEleDiv2F(TSimdFloat2 a0, TSimdFloat2 a1);
static inline TSimdFloat2 tfVectorEleAdd2F(TSimdFloat2 a0, TSimdFloat2 a1);
static inline TSimdFloat2 tfVectorEleSub2F(TSimdFloat2 a0, TSimdFloat2 a1);
static inline TSimdFloat2 tfVectorEleMul2F(TSimdFloat2 a0, TSimdFloat2 a1);

static inline TSimdFloat3x3 tfMatrixMul2x2F_2x2F(TSimdFloat2x2 a0, TSimdFloat2x2 a1);
static inline TSimdFloat3x3 tfMatrixMul2x2F_1x2F(TSimdFloat2x2 a0, TSimdFloat2x1 a1);

static inline float tfGetElemSimd2F(TSimdFloat2 a, int elem);
static inline float tfGetXSimd2F(TSimdFloat2 a);
static inline float tfGetYSimd2F(TSimdFloat2 a);

static inline bool tfIsCloseSimd2F(TSimdFloat2 a, TSimdFloat2 b, float epsilon);

// -----------------------------------------------------------
// TSimdFloat3
// -----------------------------------------------------------


// -----------------------------------------------------------
// TSimdFloat4
// -----------------------------------------------------------
#include "TF_SimdFloat3.h"
#include "TF_SimdFloat4.h"

// -----------------------------------------------------------
//  TSimdFloat3x3
// -----------------------------------------------------------
static inline TSimdFloat3x3 tfLoadIdentitySimd3x4F();
static inline void tfSetElemSimd3x3F(TSimdFloat3x3* input, int col, int row, float value);

// -----------------------------------------------------------
//  TSimdFloat3x4
// -----------------------------------------------------------

static inline TSimdFloat4x3  tfLoadSimd3x4F(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21,
                                           float m22, float m30, float m31, float m32);

// -----------------------------------------------------------
//  TSimdFloat4x4
// -----------------------------------------------------------
#include "TF_SimdFloat4x4.h"

static inline TSimdFloat4x2 tfLoadSimd4x2F(float m00, float m01, float m10, float m11, float m20, float m21, float m30, float m31);
static inline TSimdFloat4x1 tfLoadSimd4x1F(float m00, float m10, float m20, float m30);

static inline TSimdFloat3x3 tfLoadSimd3x3F(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21,
                                           float m22);
static inline TSimdFloat3x2 tfLoadSimd2x3F(float m00, float m01, float m10, float m11, float m20, float m21);
static inline TSimdFloat3x1 tfLoadSimd1x3F(float m00, float m10, float m20);


static inline void tfSetElemSimd2x3F(TSimdFloat3x2* input, int col, int row, float value);
static inline void tfSetElemSimd1x3F(TSimdFloat3x1* input, int col, int row, float value);

static inline TSimdFloat2x2 tfLoadSimd2x2F(float m00, float m01, float m10, float m11);
static inline TSimdFloat2x1 tfLoadSimd2x1F(float m00, float m10);

static inline TSimdFloat4x4 tfTransposeSimd4x4F(TSimdFloat4x4 input);

static inline bool tfIsCloseSimd3x4F(TSimdFloat4x3 a, TSimdFloat4x3 b, float epsilon);
static inline bool tfIsCloseSimd2x4F(TSimdFloat4x2 a, TSimdFloat4x2 b, float epsilon);
static inline bool tfIsCloseSimd1x4F(TSimdFloat4x1 a, TSimdFloat4x1 b, float epsilon);

static inline bool tfIsCloseSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon);

static inline void tfSetElemSimd3x4F(TSimdFloat4x3* input, int col, int row, float value);
static inline void tfSetElemSimd2x4F(TSimdFloat4x2* input, int col, int row, float value);
static inline void tfSetElemSimd1x4F(TSimdFloat4x1* input, int col, int row, float value);

static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row);
static inline TSimdFloat3 tfGetRowSimd3x4F(TSimdFloat4x3 input, int row);
static inline TSimdFloat2 tfGetRowSimd2x4F(TSimdFloat4x2 input, int row);
static inline float       tfGetRowSimd1x4F(TSimdFloat4x1 input, int row);

static inline float tfVectorDot4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline float tfVectorLengthSq4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline float tfVectorLength4F(TSimdFloat4 a0, TSimdFloat4 a1);

static inline TSimdFloat4 tfVectorEleDiv4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline TSimdFloat4 tfVectorEleAdd4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline TSimdFloat4 tfVectorEleSub4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline TSimdFloat4 tfVectorEleMul4F(TSimdFloat4 a0, TSimdFloat4 a1);

static inline bool tfIsCloseSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4 b, float epsilon);
static inline void tfSetElemSimd4x4F(TSimdFloat4x4* input, int col, int row, float value);


// conviences if cpp is avaliable
// #ifdef __cplusplus
// static inline TSimdFloat4 operator*(const TSimdFloat4x4 a0, const TSimdFloat4 a1) { return tfVectorMul4x4F(a0, a1); }
// static inline TSimdFloat3 operator*(const TSimdFloat3x3 a0, const TSimdFloat3 a1) { return tfVectorMul3x3F(a0, a1); }
// static inline TSimdFloat2 operator*(const TSimdFloat2x2 a0, const TSimdFloat2 a1) { return tfVectorMul2x2F(a0, a1); }
// #endif


#include "Forge/TF_Log.h"
#include "TF_Simd32x2.h"
#include "TF_Simd32x3.h"
#include "TF_Simd32x4.h"


#include "Internal/TF_SimdFloat.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_SimdFloat_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_SimdFloat_neon.inl"
#else
#include "Internal/TF_SimdFloat_scalar.inl"
#endif

#endif
