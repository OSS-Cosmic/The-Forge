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

#include "Internal/TF_SimdFloat4.inl"

#endif
