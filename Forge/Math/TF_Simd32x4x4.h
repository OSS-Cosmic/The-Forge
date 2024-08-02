#pragma once
#ifndef TF_MATH_SIMD_FLOAT4x4_H
#define TF_MATH_SIMD_FLOAT4x4_H

#include "Internal/SimdTypes.h"

//static inline TSimdFloat4x4 tfLoadZeroSimd4x4F();
//static inline TSimdFloat4x4 tfLoadIdentitySimd4x4F();
//static inline TSimdFloat4x4 tfLoadSimd4x4F(
//  float m00, float m01, float m02, float m03, 
//  float m10, float m11, float m12, float m13,
//  float m20, float m21, float m22, float m23, 
//  float m30, float m31, float m32, float m33);
//
//static inline TSimdFloat4x4 tfAddPerElemSimd4x4(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
//static inline TSimdFloat4x4 tfMulPerElemSimd4x4(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
//static inline TSimdFloat4x4 tfDivPerElemSimd4x4(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
//
//static inline TSimdFloat4   tfVectorMulSimd4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1);
//
//static inline TSimdFloat4x4 tfMulSimd4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
//static inline TSimdFloat4x3 tfMulSimd4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat4x3 a1);
//static inline TSimdFloat4x2 tfMulSimd4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat4x2 a1);
//static inline TSimdFloat4x1 tfMulSimd4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat4x1 a1);
//static inline TSimdFloat4x4 tfTransposeSimd4x4F(TSimdFloat4x4 a0);
//static inline TSimdFloat4x1 tfInverseFullSimd4x4F(TSimdFloat4x4 a0);
//
//static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row);
//static inline void        tfSetRowSimd4x4F(TSimdFloat4x4* input, int row, TSimdFloat4 value);
//static inline TSimdFloat4 tfGetColumnSimd4x4F(int column);
//static inline void tfSetColumnSimd4x4F(TSimdFloat4x4* input, int row);
//static inline void tfSetElemSimd4x4F(TSimdFloat4x4* input, int col, int row, float value);
//
//static inline bool tfIsCloseSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4 b, float epsilon);


#include "Internal/TF_SimdFloat4x4.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_SimdFloat4x4_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_SimdFloat4x4_neon.inl"
#else
#include "Internal/TF_SimdFloat4x4_scalar.inl"
#endif
#endif
