#pragma once
#ifndef TF_MATH_SIMD_FLOAT4_H
#define TF_MATH_SIMD_FLOAT4_H

#include "Internal/SimdTypes.h"

static inline TSimdFloat4 tfLoadSimd4F(float x, float y, float z, float w);

static inline float tfGetElemSimd4F(TSimdFloat4 a, int elem);
static inline float tfGetXSimd4F(TSimdFloat4 a);
static inline float tfGetYSimd4F(TSimdFloat4 a);
static inline float tfGetZSimd4F(TSimdFloat4 a);
static inline float tfGetWSimd4F(TSimdFloat4 a);

static inline bool tfIsCloseSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon);

static inline float tfVectorDot4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline float tfVectorLengthSq4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline float tfVectorLength4F(TSimdFloat4 a0, TSimdFloat4 a1);

static inline TSimdFloat4 tfVectorEleDiv4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline TSimdFloat4 tfVectorEleAdd4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline TSimdFloat4 tfVectorEleSub4F(TSimdFloat4 a0, TSimdFloat4 a1);
static inline TSimdFloat4 tfVectorEleMul4F(TSimdFloat4 a0, TSimdFloat4 a1);

#include "Internal/TF_SimdFloat4.inl"

#endif
