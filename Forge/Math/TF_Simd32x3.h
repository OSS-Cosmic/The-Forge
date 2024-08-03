/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once
#ifndef TF_SIMD_3_32_H
#define TF_SIMD_3_32_H

#include "Forge/Math/Internal/SimdTypes.h"

static inline Tsimd_f32x3_t tfSimdLoad_f32x3(float x, float y, float z);
static inline Tsimd_f32x3_t tfSimdZero_f32x3();


//inline Tsimd_f32x3_t tfS32x3FSplat(float value);
//inline Tsimd_i32x3_t tfS32x3iSplat(int32_t value);
//
//inline Tsimd_f32x3_t tfS32x3FZero();
//inline Tsimd_i32x3_t tfS32x3iZero();
//
//inline Tsimd_f32x2_t tfS32x3FToSimd2f(Tsimd_f32x3_t value);
//inline Tsimd_i32x3_t tfS32x3FToSimd3i(Tsimd_f32x3_t value);
//inline Tsimd_f32x3_t tfS32x3iToSimd3f(Tsimd_i32x3_t value);
//
//inline Tsimd_f32x3_t tfS32x3FSplatIndex0(Tsimd_f32x3_t value);
//inline Tsimd_f32x3_t tfS32x3FSplatIndex1(Tsimd_f32x3_t value);
//inline Tsimd_f32x3_t tfS32x3FSplatIndex2(Tsimd_f32x3_t value);
//
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat0(Tsimd_f32x3_t value);
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat1(Tsimd_f32x3_t value);
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat2(Tsimd_f32x3_t value);
//
//inline Tsimd_f32x3_t tfS32x3FSelect(Tsimd_f32x3_t arg0, Tsimd_f32x3_t arg1, Tsimd_f32x3_t mask);
//inline Tsimd_i32x3_t tfS32x3iSelect(Tsimd_i32x3_t arg0, Tsimd_i32x3_t arg1, Tsimd_i32x3_t mask);
//
//inline float tfS32x3FSelectIndex0(Tsimd_f32x3_t value);
//inline float tfS32x3FSelectIndex1(Tsimd_f32x3_t value);
//inline float tfS32x3FSelectIndex2(Tsimd_f32x3_t value);
//
//static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex0ByValue(Tsimd_f32x3_t input, float value);
//static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex1ByValue(Tsimd_f32x3_t input, float value);
//static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex2ByValue(Tsimd_f32x3_t input, float value);
//
//inline Tsimd_f32x3_t tfSimd3x32FLoad(float x, float y, float z);
//inline Tsimd_i32x3_t tfSimd3x32ILoad(int32_t x, int32_t y, int32_t z);
//
//inline Tsimd_f32x3_t tfS32x3FAdd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FSub(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FMul(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FMadd(Tsimd_f32x3_t mul1, Tsimd_f32x3_t mul2, Tsimd_f32x3_t add);
//inline Tsimd_f32x3_t tfS32x3FDiv(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FAbs(Tsimd_f32x3_t value);
//
//inline Tsimd_f32x3_t tfS32x3FNot(Tsimd_f32x3_t value);
//inline Tsimd_f32x3_t tfS32x3FAnd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FAndNot(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FOr(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FXor(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//
//inline Tsimd_i32x3_t tfS32x3iNot(Tsimd_i32x3_t value);
//inline Tsimd_i32x3_t tfS32x3iAnd(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iAndNot(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iOr(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iXor(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//
//inline Tsimd_f32x3_t tfS32x3FFloor(Tsimd_f32x3_t value);
//inline Tsimd_f32x3_t tfS32x3FCeil(Tsimd_f32x3_t value);
//inline Tsimd_f32x3_t tfS32x3FRound(Tsimd_f32x3_t value); // Ties to even (banker's rounding)
//inline Tsimd_f32x3_t tfS32x3FTruncate(Tsimd_f32x3_t value);
//inline Tsimd_f32x3_t tfS32x3FMin(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FMax(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FClamp(Tsimd_f32x3_t value, Tsimd_f32x3_t min, Tsimd_f32x3_t max);
//
//inline Tsimd_i32x3_t tfS32x3iCmpEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iCmpNeq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iCmpGt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iCmpGtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iCmpLt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline Tsimd_i32x3_t tfS32x3iCmpLtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//
//inline Tsimd_f32x3_t tfS32x3FCmpEq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FCmpNeq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FCmpGt(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FCmpGtEq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FCmpLt(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//inline Tsimd_f32x3_t tfS32x3FCmpLtEq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//
//inline bool tfS32x3iCmpAllEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2);
//inline bool tfS32x3FCmpAllEq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2);
//
//static inline bool tfSimdFloat32x3CmpAllLt(Tsimd_f32x3_t a, Tsimd_f32x3_t b);

#include "Internal/TF_Simd32x3.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd32x3_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd32x3_neon.inl"
#else
#include "Internal/TF_Simd32x3_scalar.inl"
#endif

#endif
