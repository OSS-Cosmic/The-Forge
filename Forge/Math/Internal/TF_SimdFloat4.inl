#if defined(__CLANGD__)
#include "../TF_SimdFloat4.h"
#endif

static inline float tfGetElemSimd4F(TSimdFloat4 a,int elem) {
    ASSERT(elem >= 0 && elem < 4);
    switch(elem) {
        case 0:
            return tfSimd4fSelectIndex0(a.mRow);
        case 1:
            return tfSimd4fSelectIndex1(a.mRow);
        case 2:
            return tfSimd4fSelectIndex2(a.mRow);
        case 3:
            return tfSimd4fSelectIndex3(a.mRow);
    }
    return 0;
}
static inline float tfGetXSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex0(a.mRow); }
static inline float tfGetYSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex1(a.mRow); }
static inline float tfGetZSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex2(a.mRow); }
static inline float tfGetWSimd4F(TSimdFloat4 a) { return tfSimd4fSelectIndex3(a.mRow); }

static inline float tfGetElemSimd3F(TSimdFloat3 a, int elem) {
    ASSERT(elem >= 0 && elem < 3);
    switch (elem) {
    case 0:
        return tfSimd3fSelectIndex0(a.mRow);
    case 1:
        return tfSimd3fSelectIndex1(a.mRow);
    case 2:
        return tfSimd3fSelectIndex2(a.mRow);
    }
    return 0;
}
static inline float tfGetXSimd3F(TSimdFloat3 a) { return tfSimd3fSelectIndex0(a.mRow); }
static inline float tfGetYSimd3F(TSimdFloat3 a) { return tfSimd3fSelectIndex1(a.mRow); }
static inline float tfGetZSimd3F(TSimdFloat3 a) { return tfSimd3fSelectIndex2(a.mRow); }

static inline float tfGetElemSimd2F(TSimdFloat2 a, int elem) {
    ASSERT(elem >= 0 && elem < 2);
    switch (elem) {
    case 0:
        return tfSimd2fSelectIndex0(a.mRow);
    case 1:
        return tfSimd2fSelectIndex1(a.mRow);
    }
    return 0;
}
static inline float tfGetXSimd2F(TSimdFloat2 a) { return tfSimd2fSelectIndex0(a.mRow); }
static inline float tfGetYSimd2F(TSimdFloat2 a) { return tfSimd2fSelectIndex1(a.mRow); }

static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return {tfSimdFloat32x4Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1),
                    tfSimd4fSelectIndex0(input.mCol2),
                    tfSimd4fSelectIndex0(input.mCol3))};
    case 1: return {tfSimdFloat32x4Load(
                    tfSimd4fSelectIndex1(input.mCol0),
                    tfSimd4fSelectIndex1(input.mCol1),
                    tfSimd4fSelectIndex1(input.mCol2),
                    tfSimd4fSelectIndex1(input.mCol3))};
    case 2: return {tfSimdFloat32x4Load(
                    tfSimd4fSelectIndex2(input.mCol0),
                    tfSimd4fSelectIndex2(input.mCol1),
                    tfSimd4fSelectIndex2(input.mCol2),
                    tfSimd4fSelectIndex2(input.mCol3))};
    case 3: return {tfSimdFloat32x4Load(
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
    return tfIsCloseSimd4F({a.mCol0}, {b.mCol0}, epsilon) && 
           tfIsCloseSimd4F({a.mCol1}, {b.mCol1}, epsilon) &&
           tfIsCloseSimd4F({a.mCol2}, {b.mCol2}, epsilon) && 
           tfIsCloseSimd4F({a.mCol3}, {b.mCol3}, epsilon);
}

static inline bool tfIsCloseSimd3x4F(TSimdFloat3x4 a, TSimdFloat3x4 b, float epsilon)
{
    return tfIsCloseSimd4F({a.mCol0}, {b.mCol0}, epsilon) && 
           tfIsCloseSimd4F({a.mCol1}, {b.mCol1}, epsilon) &&
           tfIsCloseSimd4F({a.mCol2}, {b.mCol2}, epsilon);
}

static inline bool tfIsCloseSimd2x4F(TSimdFloat2x4 a, TSimdFloat2x4 b, float epsilon)
{
    return tfIsCloseSimd4F({a.mCol0}, {b.mCol0}, epsilon) && 
           tfIsCloseSimd4F({a.mCol1}, {b.mCol1}, epsilon);
}


static inline bool tfIsCloseSimd1x4F(TSimdFloat1x4 a, TSimdFloat1x4 b, float epsilon)
{
    return tfSimd4fCmpEqEpsilon(a.mCol0, b.mCol0, epsilon);
}

static inline bool tfIsCloseSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon) {
    return tfSimd4fCmpAllLt(tfSimd4fAbs(tfSimd4fSub(a.mRow, b.mRow)), tfSimd4fSplat(epsilon));
}
//static inline bool        tfIsCloseSimd3F(TSimdFloat3 a, TSimdFloat3 b, float epsilon) {
//    return tfSimd3fCmpAllLt(tfSimd3fAbs(tfSimd3fSub(a.mRow, b.mRow)), tfSimd3fSplat(epsilon));
//}
//static inline bool        tfIsCloseSimd2F(TSimdFloat2 a, TSimdFloat2 b, float epsilon) {
//    return tfSimd3fCmpAllLt(tfSimd3fAbs(tfSimd3fSub(a.mRow, b.mRow)), tfSimd3fSplat(epsilon));
//}
static inline TSimdFloat4 tfLoadSimd4F(float x, float y, float z, float w) {
  TSimdFloat4 res;
  res.mRow = tfSimdFloat32x4Load(x,y,z,w);
  return res;
}

static inline TSimdFloat4x4 tfLoadSimd4x4F(
  float m00, float m01, float m02, float m03,  
  float m10, float m11, float m12, float m13,  
  float m20, float m21, float m22, float m23,  
  float m30, float m31, float m32, float m33  
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat32x4Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat32x4Load(m01, m11, m21, m31);
  result.mCol2 = tfSimdFloat32x4Load(m02, m12, m22, m32);
  result.mCol3 = tfSimdFloat32x4Load(m03, m13, m23, m33);
  return result;
}

static inline TSimdFloat4x4 tfLoadSimd3x4F(
  float m00, float m01, float m02,   
  float m10, float m11, float m12,   
  float m20, float m21, float m22,   
  float m30, float m31, float m32  
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat32x4Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat32x4Load(m01, m11, m21, m31);
  result.mCol2 = tfSimdFloat32x4Load(m02, m12, m22, m32);
  return result;
}

static inline TSimdFloat4x4 tfLoadSimd2x4F(
  float m00, float m01,   
  float m10, float m11,   
  float m20, float m21,   
  float m30, float m31 
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat32x4Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat32x4Load(m01, m11, m21, m31);
  return result;
}

static inline TSimdFloat4x4 tfLoadSimd1x4F(
  float m00,   
  float m10,   
  float m20,   
  float m30
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat32x4Load(m00, m10, m20, m30);
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
    value.mCol0 = tfSimdFloat32x4Load(1, 0, 0, 0);
    value.mCol1 = tfSimdFloat32x4Load(0, 1, 0, 0);
    value.mCol2 = tfSimdFloat32x4Load(0, 0, 1, 0);
    value.mCol3 = tfSimdFloat32x4Load(0, 0, 0, 1);
    return value;
}
