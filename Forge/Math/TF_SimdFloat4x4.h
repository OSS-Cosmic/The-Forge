#pragma once
#ifndef TF_MATH_SIMD_FLOAT4x4_H
#define TF_MATH_SIMD_FLOAT4x4_H

#include "Internal/SimdTypes.h"

static inline TSimdFloat4x4 tfLoadZeroSimd4x4F();
static inline TSimdFloat4x4 tfLoadIdentitySimd4x4F();
static inline TSimdFloat4x4 tfLoadSimd4x4F(
  float m00, float m01, float m02, float m03, 
  float m10, float m11, float m12, float m13,
  float m20, float m21, float m22, float m23, 
  float m30, float m31, float m32, float m33);

static inline TSimdFloat4   tfVectorMul4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1);
static inline TSimdFloat4x4 tfMatMul4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
static inline TSimdFloat4x3 tfMatMul4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat4x3 a1);
static inline TSimdFloat4x2 tfMatMul4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat4x2 a1);
static inline TSimdFloat4x1 tfMatMul4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat4x1 a1);
static inline TSimdFloat4x4 tfMatTranpose4x4F(TSimdFloat4x4 a0);

static inline TSimdFloat4x1 tfMatInverseFull4x4F(TSimdFloat4x4 a0);

#include "Internal/TF_SimdFloat4x4.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_SimdFloat4x4_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_SimdFloat4x4_neon.inl"
#else
#include "Internal/TF_SimdFloat4x4_scalar.inl"
#endif
#endif
