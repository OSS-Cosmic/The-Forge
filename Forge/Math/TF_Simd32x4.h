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

static inline Tsimd_f32x4_t tfSimdSplat_f32_f32x4(float value);
static inline Tsimd_f32x4_t tfSimdSplat_f32x4_f32x4(Tsimd_f32x4_t value, uint index);

// these operations will be slower for scalar
static inline Tsimd_f32x4_t tfSimdDot_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline Tsimd_f32x4_t tfSimdLengthSqr_f32x4(Tsimd_f32x4_t a) { return tfSimdDot_f32x4(a,a);}
static inline Tsimd_f32x4_t tfSimdLength_f32x4(Tsimd_f32x4_t a);

static Tsimd_f32x4_t tfNormWithLength_f32x4(Tsimd_f32x4_t input, float* outLength); 

static inline float tfSimdDot_f32x4_f32(Tsimd_f32x4_t a, Tsimd_f32x4_t b);
static inline float tfSimdLength_f32x4_f32(Tsimd_f32x4_t a);

static inline Tsimd_f32x4_t tfSimdReplace_f32_f32x4(int index, Tsimd_f32x4_t a,  float b);
static inline Tsimd_f32x4_t tfSimdReplaceX_f32_f32x4(Tsimd_f32x4_t a, float b) { return tfSimdReplace_f32_f32x4(0, a, b); }
static inline Tsimd_f32x4_t tfSimdReplaceY_f32_f32x4(Tsimd_f32x4_t a, float b) { return tfSimdReplace_f32_f32x4(1, a, b); }
static inline Tsimd_f32x4_t tfSimdReplaceZ_f32_f32x4(Tsimd_f32x4_t a, float b) { return tfSimdReplace_f32_f32x4(2, a, b); }
static inline Tsimd_f32x4_t tfSimdReplaceW_f32_f32x4(Tsimd_f32x4_t a, float b) { return tfSimdReplace_f32_f32x4(3, a, b); }
static inline Tsimd_f32x4_t tfSimdReplace_f32x4_f32x4(int index, Tsimd_f32x4_t a, Tsimd_f32x4_t b);

static inline float tfSimdGet_f32x4(Tsimd_f32x4_t value, int index);
static inline float tfSimdGetX_f32x4(Tsimd_f32x4_t value) { return tfSimdGet_f32x4(value, 0); }
static inline float tfSimdGetY_f32x4(Tsimd_f32x4_t value) { return tfSimdGet_f32x4(value, 1); }
static inline float tfSimdGetZ_f32x4(Tsimd_f32x4_t value) { return tfSimdGet_f32x4(value, 2); }
static inline float tfSimdGetW_f32x4(Tsimd_f32x4_t value) { return tfSimdGet_f32x4(value, 3); } 

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
static inline Tsimd_i32x4_t tfSimdSplat_i32x4_i32x4(Tsimd_i32x4_t value, uint index);
 
static inline int32_t tfSimdGet_i32x4(Tsimd_i32x4_t value, int index);

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



//inline Tsimd_f32x4_t tfS32x4FSplat(float value);
//inline Tsimd_i32x4_t Tsimd_i32x4_tSplat(int32_t value);
//
//inline Tsimd_f32x4_t tfS32x4FLoad(float x, float y, float z, float w);
//inline Tsimd_i32x4_t tfSimdInt4x32Load(int32_t x, int32_t y, int32_t z, int32_t w);
//
//inline Tsimd_f32x4_t tfS32x4FZero();
//inline Tsimd_i32x4_t Tsimd_i32x4_tZero();
//
//inline Tsimd_f32x2_t tfS32x4FToS32x2F(Tsimd_f32x4_t value);
//inline Tsimd_f32x3_t tfS32x4FToS32x3F(Tsimd_f32x4_t value);
//inline Tsimd_i32x4_t tfS32x4FToS32x4I(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t Tsimd_i32x4_tToSimd4f(Tsimd_i32x4_t value);
//
//inline Tsimd_f32x4_t tfS32x4FSplatIndex0(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t tfS32x4FSplatIndex1(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t tfS32x4FSplatIndex2(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t tfS32x4FSplatIndex3(Tsimd_f32x4_t value);
//
//inline Tsimd_f32x4_t tfS32x4FSelect(Tsimd_f32x4_t arg0, Tsimd_f32x4_t arg1, Tsimd_f32x4_t mask);
//inline Tsimd_i32x4_t Tsimd_i32x4_tSelect(Tsimd_i32x4_t arg0, Tsimd_i32x4_t arg1, Tsimd_i32x4_t mask);
//
//inline float tfS32x4FSelectIndex0(Tsimd_f32x4_t value);
//inline float tfS32x4FSelectIndex1(Tsimd_f32x4_t value);
//inline float tfS32x4FSelectIndex2(Tsimd_f32x4_t value);
//inline float tfS32x4FSelectIndex3(Tsimd_f32x4_t value);
//
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex0ByValue(Tsimd_f32x4_t input, float value);
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex1ByValue(Tsimd_f32x4_t input, float value);
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex2ByValue(Tsimd_f32x4_t input, float value);
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex3ByValue(Tsimd_f32x4_t input, float value);
//
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex0(Tsimd_f32x4_t input, Tsimd_f32x4_t value);
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex1(Tsimd_f32x4_t input, Tsimd_f32x4_t value);
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex2(Tsimd_f32x4_t input, Tsimd_f32x4_t value);
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex3(Tsimd_f32x4_t input, Tsimd_f32x4_t value);
//
//inline Tsimd_f32x4_t tfS32x4FAdd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FSub(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FMul(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FMadd(Tsimd_f32x4_t mul1, Tsimd_f32x4_t mul2, Tsimd_f32x4_t add);
//inline Tsimd_f32x4_t tfS32x4FDiv(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FAbs(Tsimd_f32x4_t value);
//
//inline Tsimd_f32x4_t tfS32x4FNot(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t tfS32x4FAnd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FAndNot(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FOr(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FXor(Tsimd_f32x4_t arg1, Tsimd_f32x4_t  arg2);
//
//inline Tsimd_i32x4_t Tsimd_i32x4_tNot(Tsimd_i32x4_t value);
//inline Tsimd_i32x4_t Tsimd_i32x4_tAnd(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tAndNot(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tOr(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tXor(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//
//inline Tsimd_f32x4_t tfS32x4FFloor(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t tfS32x4FCeil(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t tfS32x4FRound(Tsimd_f32x4_t value); // Ties to even (banker's rounding)
//inline Tsimd_f32x4_t tfS32x4FTruncate(Tsimd_f32x4_t value);
//inline Tsimd_f32x4_t tfS32x4FMin(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FMax(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FClamp(Tsimd_f32x4_t value, Tsimd_f32x4_t min, Tsimd_f32x4_t max);
//
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpNeq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpGt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpGtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpLt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpLtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//
//inline Tsimd_f32x4_t tfS32x4FCmpEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FCmpNeq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FCmpGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FCmpGtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FCmpLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline Tsimd_f32x4_t tfS32x4FCmpLtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//
//inline bool Tsimd_i32x4_tCmpAllEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2);
//
//inline bool tfS32x4FCmpAllEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline bool tfS32x4FCmpAllLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);
//inline bool tfS32x4FCmpAllGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2);

#include "Internal/TF_Simd32x4.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd32x4_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd32x4_neon.inl"
#else
#include "Internal/TF_Simd32x4_scalar.inl"
#endif

#endif
