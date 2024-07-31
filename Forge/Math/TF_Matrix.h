
#pragma once
#ifndef TF_MATH_MATRIX_H
#define TF_MATH_MATRIX_H

#include "Internal/SimdTypes.h"
#include "Internal/ScalarTypes.h"

#include "TF_Simd4x32.h"
#include "TF_Simd3x32.h"
#include "TF_Simd2x32.h"

#include "Forge/TF_Log.h"

static inline TSimdFloat4x4 tfMatMul4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
static inline TSimdFloat3x4 tfMatMul4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat3x4 a1);
static inline TSimdFloat2x4 tfMatMul4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat2x4 a1);
static inline TSimdFloat1x4 tfMatMul4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat1x4  a1);

static inline TSimdFloat3x3 tfMatrixMul2x2F_2x2F(TSimdFloat2x2 a0, TSimdFloat2x2  a1);
static inline TSimdFloat3x3 tfMatrixMul2x2F_1x2F(TSimdFloat2x2 a0, TSimdFloat1x2  a1);

static inline TSimdFloat4 tfVectorMul4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1);
static inline TSimdFloat4 tfVectorMul3x4F(const TSimdFloat3x4 a0, const TSimdFloat3 a1);
static inline TSimdFloat4 tfVectorMul2x4F(const TSimdFloat2x4 a0, const TSimdFloat2 a1);

static inline TSimdFloat3 tfVectorMul3x3F(const TSimdFloat3x3 a0, const TSimdFloat3 a1);
static inline TSimdFloat2 tfVectorMul2x2F(const TSimdFloat2x2 a0, const TSimdFloat2 a1);

static inline TSimdFloat4 tfVectorEleDiv4F(TSimdFloat4 a0, TSimdFloat4  a1);
static inline TSimdFloat3 tfVectorEleDiv3F(TSimdFloat3 a0, TSimdFloat3  a1);
static inline TSimdFloat2 tfVectorEleDiv2F(TSimdFloat2 a0, TSimdFloat2  a1);

static inline TSimdFloat4 tfVectorEleAdd4F(TSimdFloat4 a0, TSimdFloat4  a1);
static inline TSimdFloat3 tfVectorEleAdd3F(TSimdFloat3 a0, TSimdFloat3  a1);
static inline TSimdFloat2 tfVectorEleAdd2F(TSimdFloat2 a0, TSimdFloat2  a1);

static inline TSimdFloat4 tfVectorEleSub4F(TSimdFloat4 a0, TSimdFloat4  a1);
static inline TSimdFloat3 tfVectorEleSub3F(TSimdFloat3 a0, TSimdFloat3  a1);
static inline TSimdFloat2 tfVectorEleSub2F(TSimdFloat2 a0, TSimdFloat2  a1);

static inline TSimdFloat4 tfVectorEleMul4F(TSimdFloat4 a0, TSimdFloat4  a1);
static inline TSimdFloat3 tfVectorEleMul3F(TSimdFloat3 a0, TSimdFloat3  a1);
static inline TSimdFloat2 tfVectorEleMul2F(TSimdFloat2 a0, TSimdFloat2  a1);


#include "Internal/TF_Matrix.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Matrix_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Matrix_neon.inl"
#else
#include "Internal/TF_Matrix_scalar.inl"
#endif

#endif
