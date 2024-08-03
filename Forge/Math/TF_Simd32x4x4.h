#pragma once
#ifndef TF_MATH_SIMD_FLOAT4x4_H
#define TF_MATH_SIMD_FLOAT4x4_H

#include "Internal/SimdTypes.h"

static inline struct Tsimd_f32x4x4_s tfSimdLoad_f32x4x4(
  float m00, float m01, float m02, float m03, 
  float m10, float m11, float m12, float m13,
  float m20, float m21, float m22, float m23, 
  float m30, float m31, float m32, float m33);
static inline struct Tsimd_f32x4x4_s tfSimdLoadIdentity_f32x4x4();

// tranlsation/rotation/scale
static inline struct Tsimd_f32x4x4_s tfSimdLoadRotationYX(const float radiansY, const float radiansX);
static inline struct Tsimd_f32x4x4_s tfSimdLoadTranslation_f32x3(Tsimd_f32x3_t translation);

// perspective
static inline struct Tsimd_f32x4x4_s tfSimdLoadOrthographicLH_f32x4x4(float left, float right, float bottom, float top, float zNear, float zFar);
static inline struct Tsimd_f32x4x4_s tfSimdLoadOrthographicLH_ReverseZ_f32x4x4(float left, float right, float bottom, float top, float zNear, float zFar);
static inline struct Tsimd_f32x4x4_s tfSimdLoadOrthographicRH_f32x4x4(float left, float right, float bottom, float top, float zNear, float zFar);

static inline Tsimd_f32x4_t tfSimdGetRow_f32x4x4(struct Tsimd_f32x4x4_s input, int row);
static inline Tsimd_f32x4_t tfSimdGetColumn_f32x4x4(struct Tsimd_f32x4x4_s input, int column);
static inline float tfSimdGet_f32x4x4(struct Tsimd_f32x4x4_s input, int column, int row);

static inline struct Tsimd_f32x4x4_s tfSimdReplace_f32x4x4(struct Tsimd_f32x4x4_s input, float value, uint column, uint row);

static inline Tsimd_f32x4x4_s tfSimdMul_f32x4x4_f32x4x4(struct Tsimd_f32x4x4_s a0, struct Tsimd_f32x4x4_s a1);
static inline Tsimd_f32x4_t tfSimdMul_f32x4x4_f32x4x1(struct Tsimd_f32x4x4_s a0, Tsimd_f32x4_t a1);

static inline struct Tsimd_f32x4x4_s tfSimdTranspose_f32x4x4(struct Tsimd_f32x4x4_s a0);

static inline bool tfSimdIsClose_f32x4x4(struct Tsimd_f32x4x4_s ar0,struct Tsimd_f32x4x4_s ar1, float epsilon);

//static inline struct Tsimd_f32x4x4_s tfSimdSetTranslation_f32x4x4(struct Tsimd_f32x4x4_s ar0,Tsimd_f32x3_t translation);

#include "Internal/TF_Simd32x4x4.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd32x4x4_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd32x4x4_neon.inl"
#else
#include "Internal/TF_Simd32x4x4_scalar.inl"
#endif
#endif
