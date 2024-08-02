#pragma once
#ifndef TF_MATH_SIMD_FLOAT3x3_H
#define TF_MATH_SIMD_FLOAT3x3_H

#include "Internal/SimdTypes.h"


static inline TSimdFloat3x3 tfLoadZeroSimd3x3F();
static inline TSimdFloat3x3 tfLoadIdentitySimd3x3F();
static inline TSimdFloat3x3 tfLoadSimd3x3F(
  float m00, float m01, float m02,  
  float m10, float m11, float m12, 
  float m20, float m21, float m22);


static inline TSimdFloat4x3 tfMatMul3x3F_3x3F(TSimdFloat3x3 a0, TSimdFloat3x3 a1);
static inline TSimdFloat4x2 tfMatMul3x3F_3x2F(TSimdFloat3x3 a0, TSimdFloat3x2 a1);

static inline void tfSetElemSimd3x3F(TSimdFloat3x3* input, int col, int row, float value);

#endif
