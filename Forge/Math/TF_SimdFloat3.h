#pragma once
#ifndef TF_MATH_SIMD_FLOAT3_H
#define TF_MATH_SIMD_FLOAT3_H
#include "Internal/SimdTypes.h"


static inline TSimdFloat3   tfLoadSimd3F(float x, float y, float z);

static inline float tfVectorDot3F(TSimdFloat3 a0, TSimdFloat3 a1);
static inline bool  tfIsCloseSimd3F(TSimdFloat3 a, TSimdFloat3 b, float epsilon);

static inline TSimdFloat3 tfVectorEleDiv3F(TSimdFloat3 a0, TSimdFloat3 a1);
static inline TSimdFloat3 tfVectorEleAdd3F(TSimdFloat3 a0, TSimdFloat3 a1);
static inline TSimdFloat3 tfVectorEleSub3F(TSimdFloat3 a0, TSimdFloat3 a1);
static inline TSimdFloat3 tfVectorEleMul3F(TSimdFloat3 a0, TSimdFloat3 a1);

static inline float tfGetElemSimd3F(TSimdFloat3 a, int elem);
static inline float tfGetXSimd3F(TSimdFloat3 a);
static inline float tfGetYSimd3F(TSimdFloat3 a);
static inline float tfGetZSimd3F(TSimdFloat3 a);

#include "Internal/TF_SimdFloat3.inl"

#endif
