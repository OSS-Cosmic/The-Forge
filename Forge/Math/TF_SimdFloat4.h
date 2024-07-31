#pragma once
#ifndef TF_SIMD_FLOAT4_H
#define TF_SIMD_FLOAT4_H

#include "TF_Simd2x32.h"
#include "TF_Simd3x32.h"
#include "TF_Simd2x32.h"

#include "Internal/SimdTypes.h"

#include "TF_Simd4x32.h"

#include "Forge/TF_Log.h"

static inline TSimdFloat4x4 tfTransposeSimd4x4F(TSimdFloat4x4 input);

static inline TSimdFloat4x4 tfLoadZeroSimd4x4F();
static inline TSimdFloat4x4 tfLoadIdentitySimd4x4F();

static inline TSimdFloat4x4 tfLoadSimd4x4F(
  float m00, float m01, float m02, float m03,  
  float m10, float m11, float m12, float m13,  
  float m20, float m21, float m22, float m23,  
  float m30, float m31, float m32, float m33  
); 
static inline TSimdFloat4x4 tfLoadSimd3x4F(
  float m00, float m01, float m02,   
  float m10, float m11, float m12,   
  float m20, float m21, float m22,   
  float m30, float m31, float m32  
);
static inline TSimdFloat4x4 tfLoadSimd2x4F(
  float m00, float m01,   
  float m10, float m11,   
  float m20, float m21,   
  float m30, float m31 
);
static inline TSimdFloat4x4 tfLoadSimd1x4F(
  float m00,   
  float m10,   
  float m20,   
  float m30
);
static inline TSimdFloat4 tfLoadSimd4F(float x, float y, float z, float w);
static inline TSimdFloat3 tfLoadSimd3F(float x, float y, float z, float w);
static inline TSimdFloat2 tfLoadSimd2F(float x, float y, float z, float w);

static inline float tfGetElemSimd4F(TSimdFloat4 a, int elem);
static inline float tfGetXSimd4F(TSimdFloat4 a);
static inline float tfGetYSimd4F(TSimdFloat4 a);
static inline float tfGetZSimd4F(TSimdFloat4 a);
static inline float tfGetWSimd4F(TSimdFloat4 a);

static inline float tfGetElemSimd3F(TSimdFloat3 a,int elem);
static inline float tfGetXSimd3F(TSimdFloat3 a);
static inline float tfGetYSimd3F(TSimdFloat3 a);
static inline float tfGetZSimd3F(TSimdFloat3 a);

static inline float tfGetElemSimd2F(TSimdFloat2 a,int elem);
static inline float tfGetXSimd2F(TSimdFloat2 a);
static inline float tfGetYSimd2F(TSimdFloat2 a);

static inline bool tfIsCloseSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4 b, float epsilon);
static inline bool tfIsCloseSimd3x4F(TSimdFloat3x4 a, TSimdFloat3x4 b, float epsilon);
static inline bool tfIsCloseSimd2x4F(TSimdFloat2x4 a, TSimdFloat2x4 b, float epsilon);
static inline bool tfIsCloseSimd1x4F(TSimdFloat1x4 a, TSimdFloat1x4 b, float epsilon);

static inline bool tfIsCloseSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon);
static inline bool tfIsCloseSimd3F(TSimdFloat3 a, TSimdFloat3 b, float epsilon);
static inline bool tfIsCloseSimd2F(TSimdFloat2 a, TSimdFloat2 b, float epsilon);

static inline void tfSetElemSimd4x4F(TSimdFloat4x4* input, int col, int row, float value);
static inline void tfSetElemSimd3x4F(TSimdFloat3x4* input, int col, int row, float value);
static inline void tfSetElemSimd2x4F(TSimdFloat2x4* input, int col, int row, float value);
static inline void tfSetElemSimd1x4F(TSimdFloat1x4* input, int col, int row, float value);

static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row);
static inline TSimdFloat3 tfGetRowSimd3x4F(TSimdFloat3x4 input, int row);
static inline TSimdFloat2 tfGetRowSimd2x4F(TSimdFloat2x4 input, int row);
static inline float tfGetRowSimd1x4F(TSimdFloat1x4 input, int row);

static inline float tfVectorDot4F(TSimdFloat4 a0, TSimdFloat4  a1);
static inline float tfVectorDot3F(TSimdFloat4 a0, TSimdFloat4  a1);

#include "Internal/TF_SimdFloat4.inl"
#if defined(TF_FEATURE_CPU_SSE)
#include "Internal/TF_SimdFloat4_sse.inl"
#elif defined(TF_FEATURE_CPU_NEON)
#include "Internal/TF_SimdFloat4_neon.inl"
#else
#include "Internal/TF_SimdFloat4_scalar.inl"
#endif

#endif
