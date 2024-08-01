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

inline TSimdFloat32x4 tfSimd4fSplat(float value);
inline TSimdInt32x4 tfSimd4iSplat(int32_t value);

inline TSimdFloat32x4 tfSimd4fZero();
inline TSimdInt32x4 tfSimd4iZero();

inline TSimdFloat32x2 tfSimd4fToSimd2f(TSimdFloat32x4 value);
inline TSimdFloat32x3 tfSimd4fToSimd3f(TSimdFloat32x4 value);
inline TSimdInt32x4 tfSimd4fToSimd4i(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4iToSimd4f(TSimdInt32x4 value);

inline TSimdFloat32x4 tfSimd4fSplatIndex0(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4fSplatIndex1(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4fSplatIndex2(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4fSplatIndex3(TSimdFloat32x4 value);

inline TSimdFloat32x4 tfSimd4fSelect(TSimdFloat32x4 arg0, TSimdFloat32x4 arg1, TSimdFloat32x4 mask);
inline TSimdInt32x4 tfSimd4iSelect(TSimdInt32x4 arg0, TSimdInt32x4 arg1, TSimdInt32x4 mask);

inline float tfSimd4fSelectIndex0(TSimdFloat32x4 value);
inline float tfSimd4fSelectIndex1(TSimdFloat32x4 value);
inline float tfSimd4fSelectIndex2(TSimdFloat32x4 value);
inline float tfSimd4fSelectIndex3(TSimdFloat32x4 value);

static inline TSimdFloat32x4 tfSimd4fReplaceIndex0ByValue(TSimdFloat32x4 input, float value);
static inline TSimdFloat32x4 tfSimd4fReplaceIndex1ByValue(TSimdFloat32x4 input, float value);
static inline TSimdFloat32x4 tfSimd4fReplaceIndex2ByValue(TSimdFloat32x4 input, float value);
static inline TSimdFloat32x4 tfSimd4fReplaceIndex3ByValue(TSimdFloat32x4 input, float value);

inline TSimdFloat32x4 tfSimdFloat4x32Load(float x, float y, float z, float w);
inline TSimdInt32x4 tfSimdInt4x32Load(int32_t x, int32_t y, int32_t z, int32_t w);

inline TSimdFloat32x4 tfSimd4fAdd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fSub(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fMul(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fMadd(TSimdFloat32x4 mul1, TSimdFloat32x4 mul2, TSimdFloat32x4 add);
inline TSimdFloat32x4 tfSimdFloat4x32Div(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fAbs(TSimdFloat32x4 value);

inline TSimdFloat32x4 tfSimd4fNot(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4fAnd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fAndNot(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fOr(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fXor(TSimdFloat32x4 arg1, TSimdFloat32x4  arg2);

inline TSimdInt32x4 tfSimd4iNot(TSimdInt32x4 value);
inline TSimdInt32x4 tfSimd4iAnd(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iAndNot(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iOr(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iXor(TSimdInt32x4 arg1, TSimdInt32x4 arg2);

inline TSimdFloat32x4 tfSimd4fFloor(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4fCeil(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4fRound(TSimdFloat32x4 value); // Ties to even (banker's rounding)
inline TSimdFloat32x4 tfSimd4fTruncate(TSimdFloat32x4 value);
inline TSimdFloat32x4 tfSimd4fMin(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fMax(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fClamp(TSimdFloat32x4 value, TSimdFloat32x4 min, TSimdFloat32x4 max);

inline TSimdInt32x4 tfSimd4iCmpEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iCmpNeq(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iCmpGt(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iCmpGtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iCmpLt(TSimdInt32x4 arg1, TSimdInt32x4 arg2);
inline TSimdInt32x4 tfSimd4iCmpLtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2);

inline TSimdFloat32x4 tfSimd4fCmpEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fCmpNeq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fCmpGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fCmpGtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fCmpLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline TSimdFloat32x4 tfSimd4fCmpLtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);

inline bool tfSimd4iCmpAllEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2);

inline bool tfSimd4fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline bool tfSimd4fCmpAllLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);
inline bool tfSimd4fCmpAllGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2);

#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_Simd32x4_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_Simd32x4_neon.inl"
#else
#include "Internal/TF_Simd32x4_scalar.inl"
#endif

#endif
