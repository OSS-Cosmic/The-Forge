#pragma once
#ifndef TF_SIMD_COMMON_H
#define TF_SIMD_COMMON_H

#include "Internal/SimdTypes.h"

#include "TF_Simd4x32.h"
#include "TF_Simd3x32.h"
#include "TF_Simd2x32.h"

#include "Forge/TF_Log.h"


static inline TSimdFloat4  tfLoadSimd4F(float x, float y, float z, float w);
static inline TSimdFloat4x4 tfLoadSimd4x4F(
  float m00, float m01, float m02, float m03,  
  float m10, float m11, float m12, float m13,  
  float m20, float m21, float m22, float m23,  
  float m30, float m31, float m32, float m33  
); 

static inline bool tfCmpEqSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon);
static inline bool tfCmpEqSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4  b, float epsilon);

static inline bool tfCmpEqSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon) {
    const TSimdFloat32x4 diff = tfSimd4fSub(a.mRow, b.mRow);
    return tfSimd4fCmpAllLt(tfSimd4fAbs(diff), tfSimd4fSplat(epsilon));
}

static inline bool tfCmpEqSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4  b, float epsilon) {
    return 
      tfSimd4fCmpAllLt(tfSimd4fAbs(tfSimd4fSub({a.mCol0}, {b.mCol0})), tfSimd4fSplat(epsilon)) && 
      tfSimd4fCmpAllLt(tfSimd4fAbs(tfSimd4fSub({a.mCol1}, {b.mCol1})), tfSimd4fSplat(epsilon)) && 
      tfSimd4fCmpAllLt(tfSimd4fAbs(tfSimd4fSub({a.mCol2}, {b.mCol2})), tfSimd4fSplat(epsilon)) && 
      tfSimd4fCmpAllLt(tfSimd4fAbs(tfSimd4fSub({a.mCol3}, {b.mCol3})), tfSimd4fSplat(epsilon)); 
}


static inline TSimdFloat4 tfLoadSimd4F(float x, float y, float z, float w) {
  TSimdFloat4 res;
  res.mRow = tfSimdFloat4Load(x,y,z,w);
  return res;
}

static inline TSimdFloat4x4 tfLoadSimd4x4F(
  float m00, float m01, float m02, float m03,  
  float m10, float m11, float m12, float m13,  
  float m20, float m21, float m22, float m23,  
  float m30, float m31, float m32, float m33  
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat4Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat4Load(m01, m11, m21, m31);
  result.mCol2 = tfSimdFloat4Load(m02, m12, m22, m32);
  result.mCol3 = tfSimdFloat4Load(m03, m13, m23, m33);
  return result;
}

#endif
