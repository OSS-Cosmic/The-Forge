/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once
#ifndef TF_SIMD_4_32_H
#define TF_SIMD_4_32_H

#include "Forge/Math/Internal/SimdTypes.h"
#include "Forge/TF_Log.h"

// Tsimd_f32x4_t
static inline Tsimd_f32x4_t tfSimdLoad_f32x4(float x, float y, float z, float w);
static inline Tsimd_f32x4_t tfSimdZero_f32x4();

// Splat
static inline Tsimd_f32x4_t tfSimdSplat_f32_f32x4(float value);
static inline Tsimd_f32x4_t tfSimdSplat_f32x4_f32x4(Tsimd_f32x4_t value, int index);

// Get 
static inline float tfSimdGet_f32x4(Tsimd_f32x4_t value, int index);

// these operations will be slower for scalar
static inline Tsimd_f32x4_t tfSimdDot_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline Tsimd_f32x4_t tfSimdLengthSqr_f32x4(Tsimd_f32x4_t a) { return tfSimdDot_f32x4(a,a);}
static inline Tsimd_f32x4_t tfSimdLength_f32x4(Tsimd_f32x4_t a);
static Tsimd_f32x4_t tfNormWithLength_f32x4(Tsimd_f32x4_t input, float* outLength); 

static inline float tfSimdDot_f32x4_f32(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline float tfSimdLength_f32x4_f32(Tsimd_f32x4_t a);
static inline float tfSimdLengthSqr_f32x4_f32(Tsimd_f32x4_t a);

static inline Tsimd_f32x4_t tfSimdReplace_f32_f32x4(Tsimd_f32x4_t a, int index,  float b);
static inline Tsimd_f32x4_t tfSimdReplace_f32x4_f32x4(Tsimd_f32x4_t a, int index,  Tsimd_f32x4_t b);

static inline float tfSimdMaxElem_f32x4_f32(Tsimd_f32x4_t a);
static inline float tfSimdMinElem_f32x4_f32(Tsimd_f32x4_t a); 

static inline Tsimd_f32x4_t tfSimdMaxElem_f32x4(Tsimd_f32x4_t a); 
static inline Tsimd_f32x4_t tfSimdMaxPerElem_f32x4(Tsimd_f32x4_t a,Tsimd_f32x4_t b); 
static inline Tsimd_f32x4_t tfSimdMinElem_f32x4(Tsimd_f32x4_t a); 
static inline Tsimd_f32x4_t tfSimdMinPerElem_f32x4(Tsimd_f32x4_t a,Tsimd_f32x4_t b); 

static inline Tsimd_f32x4_t tfSimdRcp_f32x4(Tsimd_f32x4_t a);
static inline Tsimd_f32x4_t tfSimdSqrt_f32x4(Tsimd_f32x4_t a);

static inline Tsimd_f32x4_t tfSimdAdd_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline Tsimd_f32x4_t tfSimdSub_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline Tsimd_f32x4_t tfSimdMul_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline Tsimd_f32x4_t tfSimdDiv_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline Tsimd_f32x4_t tfSimdAbs_f32x4(Tsimd_f32x4_t a);
static inline Tsimd_f32x4_t tfSimdMadd_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b, Tsimd_f32x4_t c);

static inline Tsimd_f32x4_t tfSimdNot_f32x4(Tsimd_f32x4_t value);
static inline Tsimd_f32x4_t tfSimdAnd_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdAndNot_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdOr_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdXor_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);

static inline Tsimd_f32x4_t tfSimdCmpEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdCmpNeq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdCmpGt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdCmpGtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdCmpLt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline Tsimd_f32x4_t tfSimdCmpLtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);

static inline bool tfSimdCmpAllEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline bool tfSimdCmpAllNeq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline bool tfSimdCmpAllGt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline bool tfSimdCmpAllGtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline bool tfSimdCmpAllLt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
static inline bool tfSimdCmpAllLtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);

static inline bool tfSimdIsClose_f32x4(Tsimd_f32x4_t ar0,Tsimd_f32x4_t ar1, float epsilon);

// Tsimd_i32x4_t
static inline Tsimd_i32x4_t tfSimdLoad_i32x4(int32_t x, int32_t y, int32_t z, int32_t w);

static inline Tsimd_i32x4_t tfSimdSplat_i32_i32x4(int value);
static inline Tsimd_i32x4_t tfSimdSplat_i32x4_i32x4(Tsimd_i32x4_t value, int index);
 
static inline int32_t tfSimdSelect_i32x4(Tsimd_i32x4_t value, int index);

static inline Tsimd_i32x4_t tfSimdAdd_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b);
static inline Tsimd_i32x4_t tfSimdMul_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b);
static inline Tsimd_i32x4_t tfSimdAbs_i32x4(Tsimd_i32x4_t a);
static inline Tsimd_i32x4_t tfSimdMadd_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b, Tsimd_i32x4_t c);

static inline Tsimd_i32x4_t tfSimdNot_i32x4(Tsimd_i32x4_t value);
static inline Tsimd_i32x4_t tfSimdAnd_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdAndNot_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdOr_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdXor_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);

static inline Tsimd_i32x4_t tfSimdCmpEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdCmpNeq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdCmpGt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdCmpGtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdCmpLt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline Tsimd_i32x4_t tfSimdCmpLtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);

static inline bool tfSimdCmpAllEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline bool tfSimdCmpAllNeq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline bool tfSimdCmpAllGt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline bool tfSimdCmpAllGtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline bool tfSimdCmpAllLt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
static inline bool tfSimdCmpAllLtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);

// --------------------------------------------

static inline Tsimd_i32x4_t tfSimd_f32x4_To_i32x4(Tsimd_f32x4_t a);
static inline Tsimd_f32x4_t tfSimd_i32x4_To_f32x4(Tsimd_i32x4_t a);
static inline Tsimd_f32x3_t tfSimd_f32x4_To_f32x3(Tsimd_f32x4_t a);

#include "Internal/TF_Simd32x4.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd32x4_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd32x4_neon.inl"
#else
#include "Internal/TF_Simd32x4_scalar.inl"
#endif

#endif
