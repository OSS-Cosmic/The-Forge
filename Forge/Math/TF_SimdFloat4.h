#pragma once
#include "TF_Simd2x32.h"
#include "TF_Simd3x32.h"
#ifndef TF_SIMD_COMMON_H
#define TF_SIMD_COMMON_H

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

static inline bool tfIsCloseSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4 b, float epsilon);
static inline bool tfIsCloseSimd3x4F(TSimdFloat3x4 a, TSimdFloat3x4 b, float epsilon);
static inline bool tfIsCloseSimd2x4F(TSimdFloat2x4 a, TSimdFloat2x4 b, float epsilon);
static inline bool tfIsCloseSimd1x4F(TSimdFloat1x4 a, TSimdFloat1x4 b, float epsilon);
static inline bool tfIsCloseSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon);

static inline void tfSetElemSimd4x4F(TSimdFloat4x4* input, int col, int row, float value);
static inline void tfSetElemSimd3x4F(TSimdFloat3x4* input, int col, int row, float value);
static inline void tfSetElemSimd2x4F(TSimdFloat2x4* input, int col, int row, float value);
static inline void tfSetElemSimd1x4F(TSimdFloat1x4* input, int col, int row, float value);

static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row);
static inline TSimdFloat3 tfGetRowSimd3x4F(TSimdFloat3x4 input, int row);
static inline TSimdFloat2 tfGetRowSimd2x4F(TSimdFloat2x4 input, int row);
static inline float tfGetRowSimd1x4F(TSimdFloat1x4 input, int row);



// ------------------------------
// implementation 
// -------------------------------

static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return {tfSimdFloat4Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1),
                    tfSimd4fSelectIndex0(input.mCol2),
                    tfSimd4fSelectIndex0(input.mCol3))};
    case 1: return {tfSimdFloat4Load(
                    tfSimd4fSelectIndex1(input.mCol0),
                    tfSimd4fSelectIndex1(input.mCol1),
                    tfSimd4fSelectIndex1(input.mCol2),
                    tfSimd4fSelectIndex1(input.mCol3))};
    case 2: return {tfSimdFloat4Load(
                    tfSimd4fSelectIndex2(input.mCol0),
                    tfSimd4fSelectIndex2(input.mCol1),
                    tfSimd4fSelectIndex2(input.mCol2),
                    tfSimd4fSelectIndex2(input.mCol3))};
    case 3: return {tfSimdFloat4Load(
                    tfSimd4fSelectIndex3(input.mCol0),
                    tfSimd4fSelectIndex3(input.mCol1),
                    tfSimd4fSelectIndex3(input.mCol2),
                    tfSimd4fSelectIndex3(input.mCol3))};
  }
  return {};
}
static inline TSimdFloat3 tfGetRowSimd3x4F(TSimdFloat3x4 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return {tfSimdFloat3Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1),
                    tfSimd4fSelectIndex0(input.mCol2))};
    case 1: return {tfSimdFloat3Load(
                    tfSimd4fSelectIndex1(input.mCol0),
                    tfSimd4fSelectIndex1(input.mCol1),
                    tfSimd4fSelectIndex1(input.mCol2))};
    case 2: return {tfSimdFloat3Load(
                    tfSimd4fSelectIndex2(input.mCol0),
                    tfSimd4fSelectIndex2(input.mCol1),
                    tfSimd4fSelectIndex2(input.mCol2))};
    case 3: return {tfSimdFloat3Load(
                    tfSimd4fSelectIndex3(input.mCol0),
                    tfSimd4fSelectIndex3(input.mCol1),
                    tfSimd4fSelectIndex3(input.mCol2))};
  }
  return {};

}
static inline TSimdFloat2 tfGetRowSimd2x4F(TSimdFloat2x4 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return {tfSimdFloat2Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1))};
    case 1: return {tfSimdFloat2Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1))};
    case 2: return {tfSimdFloat2Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1))};
    case 3: return {tfSimdFloat2Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1))};
  }
  return {};

}
static inline float tfGetRowSimd1x4F(TSimdFloat1x4 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return tfSimd4fSelectIndex0(input.mCol0);
    case 1: return tfSimd4fSelectIndex1(input.mCol0);
    case 2: return tfSimd4fSelectIndex2(input.mCol0);
    case 3: return tfSimd4fSelectIndex3(input.mCol0);
  }
  return {};

}



static inline void tfSetElemSimd4x4F(TSimdFloat4x4* input, int col, int row, float value){
  ASSERT(col >= 0 && col < 4);
  ASSERT(row >= 0 && row < 4);
  switch (col)
  {
    case 0: input->mCol[row] = tfSimd4fReplaceIndex0ByValue(input->mCol[row], value); break;
    case 1: input->mCol[row] = tfSimd4fReplaceIndex1ByValue(input->mCol[row], value); break;
    case 2: input->mCol[row] = tfSimd4fReplaceIndex2ByValue(input->mCol[row], value); break;
    case 3: input->mCol[row] = tfSimd4fReplaceIndex3ByValue(input->mCol[row], value); break;
  }
}
static inline void tfSetElemSimd3x4F(TSimdFloat3x4* input, int col, int row, float value){
  ASSERT(col >= 0 && col < 3);
  ASSERT(row >= 0 && row < 4);
  switch (col)
  {
    case 0: input->mCol[row] = tfSimd4fReplaceIndex0ByValue(input->mCol[row], value); break;
    case 1: input->mCol[row] = tfSimd4fReplaceIndex1ByValue(input->mCol[row], value); break;
    case 2: input->mCol[row] = tfSimd4fReplaceIndex2ByValue(input->mCol[row], value); break;
  }
}
static inline void tfSetElemSimd2x4F(TSimdFloat2x4* input, int col, int row, float value){
  ASSERT(col >= 0 && col < 2);
  ASSERT(row >= 0 && row < 4);
  switch (col)
  {
    case 0: input->mCol[row] = tfSimd4fReplaceIndex0ByValue(input->mCol[row], value); break;
    case 1: input->mCol[row] = tfSimd4fReplaceIndex1ByValue(input->mCol[row], value); break;
  }
}
static inline void tfSetElemSimd1x4F(TSimdFloat1x4* input, int col, int row, float value){
  ASSERT(col == 0);
  ASSERT(row >= 0 && row < 4);
  switch (col)
  {
    case 0: input->mCol[row] = tfSimd4fReplaceIndex0ByValue(input->mCol[row], value); break;
  }
}


static inline bool tfIsCloseSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4 b, float epsilon)
{
    return tfSimd4fCmpEqEpsilon(a.mCol0, b.mCol0, epsilon) && tfSimd4fCmpEqEpsilon(a.mCol1, b.mCol1, epsilon) &&
           tfSimd4fCmpEqEpsilon(a.mCol2, b.mCol2, epsilon) && tfSimd4fCmpEqEpsilon(a.mCol3, b.mCol3, epsilon);
}

static inline bool tfIsCloseSimd3x4F(TSimdFloat3x4 a, TSimdFloat3x4 b, float epsilon)
{
    return tfSimd4fCmpEqEpsilon(a.mCol0, b.mCol0, epsilon) && tfSimd4fCmpEqEpsilon(a.mCol1, b.mCol1, epsilon) &&
           tfSimd4fCmpEqEpsilon(a.mCol2, b.mCol2, epsilon);
}

static inline bool tfIsCloseSimd2x4F(TSimdFloat2x4 a, TSimdFloat2x4 b, float epsilon)
{
    return tfSimd4fCmpEqEpsilon(a.mCol0, b.mCol0, epsilon) && tfSimd4fCmpEqEpsilon(a.mCol1, b.mCol1, epsilon);
}

static inline bool tfIsCloseSimd1x4F(TSimdFloat1x4 a, TSimdFloat1x4 b, float epsilon)
{
    return tfSimd4fCmpEqEpsilon(a.mCol0, b.mCol0, epsilon);
}

static inline bool tfIsCloseSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon) {
  return tfSimd4fCmpEqEpsilon(a.mRow, b.mRow, epsilon);
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

static inline TSimdFloat4x4 tfLoadSimd3x4F(
  float m00, float m01, float m02,   
  float m10, float m11, float m12,   
  float m20, float m21, float m22,   
  float m30, float m31, float m32  
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat4Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat4Load(m01, m11, m21, m31);
  result.mCol2 = tfSimdFloat4Load(m02, m12, m22, m32);
  return result;
}

static inline TSimdFloat4x4 tfLoadSimd2x4F(
  float m00, float m01,   
  float m10, float m11,   
  float m20, float m21,   
  float m30, float m31 
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat4Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat4Load(m01, m11, m21, m31);
  return result;
}

static inline TSimdFloat4x4 tfLoadSimd1x4F(
  float m00,   
  float m10,   
  float m20,   
  float m30
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat4Load(m00, m10, m20, m30);
  return result;
}
static inline TSimdFloat4x4 tfLoadZeroSimd4x4F()
{
    TSimdFloat4x4 value;
    value.mCol0 = tfSimd4fZero();
    value.mCol1 = tfSimd4fZero();
    value.mCol2 = tfSimd4fZero();
    value.mCol3 = tfSimd4fZero();
    return value;
}

static inline TSimdFloat4x4 tfLoadIdentitySimd4x4F()
{
    TSimdFloat4x4 value;
    value.mCol0 = tfSimdFloat4Load(1, 0, 0, 0);
    value.mCol1 = tfSimdFloat4Load(0, 1, 0, 0);
    value.mCol2 = tfSimdFloat4Load(0, 0, 1, 0);
    value.mCol3 = tfSimdFloat4Load(0, 0, 0, 1);
    return value;
}

#endif
