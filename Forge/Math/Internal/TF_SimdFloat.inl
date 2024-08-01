#if defined(__CLANGD__)
#include "../TF_SimdFloat.h"
#endif

//static inline TSimdFloat4x1 tfMatInverseFull4x4F(TSimdFloat4x4 a0) {
//
//        // Inverse = adjoint / det.
//        // pre-compute 2x2 dets for last two rows when computing
//        // cofactors of first two rows.
//        float d12 = ((*this)(2, 0) * (*this)(3, 1) - (*this)(3, 0) * (*this)(2, 1));
//        float d13 = ((*this)(2, 0) * (*this)(3, 2) - (*this)(3, 0) * (*this)(2, 2));
//        float d23 = ((*this)(2, 1) * (*this)(3, 2) - (*this)(3, 1) * (*this)(2, 2));
//        float d24 = ((*this)(2, 1) * (*this)(3, 3) - (*this)(3, 1) * (*this)(2, 3));
//        float d34 = ((*this)(2, 2) * (*this)(3, 3) - (*this)(3, 2) * (*this)(2, 3));
//        float d41 = ((*this)(2, 3) * (*this)(3, 0) - (*this)(3, 3) * (*this)(2, 0));
//}


static inline TSimdFloat4 tfVectorMul3x4F(const TSimdFloat4x3 a0, const TSimdFloat3 a1) {
    TSimdFloat32x4 xxxx = tfSimdFloat3To4Splat0(a1.mRow);
    TSimdFloat32x4 yyyy = tfSimdFloat3To4Splat1(a1.mRow);
    TSimdFloat32x4 zzzz = tfSimdFloat3To4Splat2(a1.mRow);
    TSimdFloat32x4 res = tfSimd4fMul(a0.mCol0, xxxx);
    res = tfSimd4fMadd(a0.mCol1, yyyy, res);
    res = tfSimd4fMadd(a0.mCol2, zzzz, res);
    return { res };
}

static inline TSimdFloat4 tfVectorMul2x4F(const TSimdFloat4x2 a0, const TSimdFloat2 a1) {
    TSimdFloat32x4 xxxx = tfSimdFloat2To4Splat0(a1.mRow);
    TSimdFloat32x4 yyyy = tfSimdFloat2To4Splat1(a1.mRow);
    TSimdFloat32x4 res = tfSimd4fMul(a0.mCol0, xxxx);
    res = tfSimd4fMadd(a0.mCol1, yyyy, res);
    return { res };
}

/**
 * Multiplication of a 3x3 matrix and a 4 element vector
 **/
static inline TSimdFloat3 tfVectorMul3x3F(const TSimdFloat3x3 a0, const TSimdFloat3 a1) {
    TSimdFloat32x3 xxx = tfSimd3fSplatIndex0(a1.mRow);
    TSimdFloat32x3 yyy = tfSimd3fSplatIndex1(a1.mRow);
    TSimdFloat32x3 zzz = tfSimd3fSplatIndex2(a1.mRow);
    TSimdFloat32x3 res = tfSimd3fMul(a0.mCol0, xxx);
    res = tfSimd3fMadd(a0.mCol1, yyy, res);
    res = tfSimd3fMadd(a0.mCol2, zzz, res);
    return { res };
}



static inline TSimdFloat3 tfGetRowSimd3x4F(TSimdFloat4x3 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return {tfSimdFloat3x32Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1),
                    tfSimd4fSelectIndex0(input.mCol2))};
    case 1: return {tfSimdFloat3x32Load(
                    tfSimd4fSelectIndex1(input.mCol0),
                    tfSimd4fSelectIndex1(input.mCol1),
                    tfSimd4fSelectIndex1(input.mCol2))};
    case 2: return {tfSimdFloat3x32Load(
                    tfSimd4fSelectIndex2(input.mCol0),
                    tfSimd4fSelectIndex2(input.mCol1),
                    tfSimd4fSelectIndex2(input.mCol2))};
    case 3: return {tfSimdFloat3x32Load(
                    tfSimd4fSelectIndex3(input.mCol0),
                    tfSimd4fSelectIndex3(input.mCol1),
                    tfSimd4fSelectIndex3(input.mCol2))};
  }
  return {};

}

static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return {tfSimdFloat4x32Load(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1),
                    tfSimd4fSelectIndex0(input.mCol2),
                    tfSimd4fSelectIndex0(input.mCol3)
                    )};
    case 1: return {tfSimdFloat4x32Load(
                    tfSimd4fSelectIndex1(input.mCol0),
                    tfSimd4fSelectIndex1(input.mCol1),
                    tfSimd4fSelectIndex1(input.mCol2),
                    tfSimd4fSelectIndex1(input.mCol3))};
    case 2: return {tfSimdFloat4x32Load(
                    tfSimd4fSelectIndex2(input.mCol0),
                    tfSimd4fSelectIndex2(input.mCol1),
                    tfSimd4fSelectIndex2(input.mCol2),
                    tfSimd4fSelectIndex2(input.mCol3))};
    case 3: return {tfSimdFloat4x32Load(
                    tfSimd4fSelectIndex3(input.mCol0),
                    tfSimd4fSelectIndex3(input.mCol1),
                    tfSimd4fSelectIndex3(input.mCol2),
                    tfSimd4fSelectIndex3(input.mCol3))};
  }
  return {};

}


static inline TSimdFloat2 tfGetRowSimd2x4F(TSimdFloat4x2 input, int row) {
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
static inline float tfGetRowSimd1x4F(TSimdFloat4x1 input, int row) {
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
  switch (row)
  {
    case 0: input->mCol[col] = tfSimd4fReplaceIndex0ByValue(input->mCol[col], value); break;
    case 1: input->mCol[col] = tfSimd4fReplaceIndex1ByValue(input->mCol[col], value); break;
    case 2: input->mCol[col] = tfSimd4fReplaceIndex2ByValue(input->mCol[col], value); break;
    case 3: input->mCol[col] = tfSimd4fReplaceIndex3ByValue(input->mCol[col], value); break;
  }
}
static inline void tfSetElemSimd3x4F(TSimdFloat4x3* input, int col, int row, float value){
  ASSERT(col >= 0 && col < 3);
  ASSERT(row >= 0 && row < 4);
  switch (row)
  {
    case 0: input->mCol[col] = tfSimd4fReplaceIndex0ByValue(input->mCol[col], value); break;
    case 1: input->mCol[col] = tfSimd4fReplaceIndex1ByValue(input->mCol[col], value); break;
    case 2: input->mCol[col] = tfSimd4fReplaceIndex2ByValue(input->mCol[col], value); break;
    case 3: input->mCol[col] = tfSimd4fReplaceIndex3ByValue(input->mCol[col], value); break;
  }
}
static inline void tfSetElemSimd2x4F(TSimdFloat4x2* input, int col, int row, float value){
  ASSERT(col >= 0 && col < 2);
  ASSERT(row >= 0 && row < 4);
  switch (row)
  {
    case 0: input->mCol[col] = tfSimd4fReplaceIndex0ByValue(input->mCol[col], value); break;
    case 1: input->mCol[col] = tfSimd4fReplaceIndex1ByValue(input->mCol[col], value); break;
    case 2: input->mCol[col] = tfSimd4fReplaceIndex2ByValue(input->mCol[col], value); break;
    case 3: input->mCol[col] = tfSimd4fReplaceIndex3ByValue(input->mCol[col], value); break;
  }
}
static inline void tfSetElemSimd1x4F(TSimdFloat4x1* input, int col, int row, float value){
  ASSERT(col == 0);
  ASSERT(row >= 0 && row < 4);
  switch (row)
  {
    case 0: input->mCol[col] = tfSimd4fReplaceIndex0ByValue(input->mCol[col], value); break;
    case 1: input->mCol[col] = tfSimd4fReplaceIndex1ByValue(input->mCol[col], value); break;
    case 2: input->mCol[col] = tfSimd4fReplaceIndex2ByValue(input->mCol[col], value); break;
    case 3: input->mCol[col] = tfSimd4fReplaceIndex3ByValue(input->mCol[col], value); break;
  }
}


static inline bool tfIsCloseSimd3x4F(TSimdFloat4x3 a, TSimdFloat4x3 b, float epsilon)
{
    return tfIsCloseSimd4F({a.mCol0}, {b.mCol0}, epsilon) && 
           tfIsCloseSimd4F({a.mCol1}, {b.mCol1}, epsilon) &&
           tfIsCloseSimd4F({a.mCol2}, {b.mCol2}, epsilon);
}

static inline bool tfIsCloseSimd2x4F(TSimdFloat4x2 a, TSimdFloat4x2 b, float epsilon)
{
    return tfIsCloseSimd4F({a.mCol0}, {b.mCol0}, epsilon) && 
           tfIsCloseSimd4F({a.mCol1}, {b.mCol1}, epsilon);
}


static inline bool tfIsCloseSimd1x4F(TSimdFloat4x1 a, TSimdFloat4x1 b, float epsilon)
{
    return tfIsCloseSimd4F({a.mCol0}, {b.mCol0}, epsilon);
}

static inline bool tfIsCloseSimd4F(TSimdFloat4 a, TSimdFloat4 b, float epsilon) {
    return tfSimd4fCmpAllLt(tfSimd4fAbs(tfSimd4fSub(a.mRow, b.mRow)), tfSimd4fSplat(epsilon));
}


static inline TSimdFloat4x4 tfLoadSimd4x4F(
  float m00, float m01, float m02, float m03,  
  float m10, float m11, float m12, float m13,  
  float m20, float m21, float m22, float m23,  
  float m30, float m31, float m32, float m33  
) {
  TSimdFloat4x4 result;
  result.mCol0 = tfSimdFloat4x32Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat4x32Load(m01, m11, m21, m31);
  result.mCol2 = tfSimdFloat4x32Load(m02, m12, m22, m32);
  result.mCol3 = tfSimdFloat4x32Load(m03, m13, m23, m33);
  return result;
}

static inline TSimdFloat4x3 tfLoadSimd3x4F(
  float m00, float m01, float m02,   
  float m10, float m11, float m12,   
  float m20, float m21, float m22,   
  float m30, float m31, float m32  
) {
  TSimdFloat4x3  result;
  result.mCol0 = tfSimdFloat4x32Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat4x32Load(m01, m11, m21, m31);
  result.mCol2 = tfSimdFloat4x32Load(m02, m12, m22, m32);
  return result;
}

static inline TSimdFloat4x2 tfLoadSimd4x2F(float m00, float m01, float m10, float m11, float m20, float m21, float m30, float m31) {
  TSimdFloat4x2  result;
  result.mCol0 = tfSimdFloat4x32Load(m00, m10, m20, m30);
  result.mCol1 = tfSimdFloat4x32Load(m01, m11, m21, m31);
  return result;
}

static inline TSimdFloat4x1  tfLoadSimd4x1F(
  float m00,   
  float m10,   
  float m20,   
  float m30
) {
  TSimdFloat4x1 result;
  result.mCol0 = tfSimdFloat4x32Load(m00, m10, m20, m30);
  return result;
}

static inline TSimdFloat4 tfVectorEleDiv4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimdFloat4x32Div(a0.mRow, a1.mRow) }; }
static inline TSimdFloat4 tfVectorEleSub4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimd4fSub(a0.mRow, a1.mRow) }; }
static inline TSimdFloat4 tfVectorEleAdd4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimd4fAdd(a0.mRow, a1.mRow) }; }
static inline TSimdFloat4 tfVectorEleMul4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimd4fMul(a0.mRow, a1.mRow) }; }


static inline TSimdFloat3x3 tfLoadSimd3x3F(
  float m00, float m01, float m02, 
  float m10, float m11, float m12,  
  float m20, float m21, float m22
) {
    TSimdFloat3x3 res;
    res.mCol0 = tfSimdFloat3x32Load(m00, m10, m20);
    res.mCol1 = tfSimdFloat3x32Load(m01, m11, m21);
    res.mCol2 = tfSimdFloat3x32Load(m02, m12, m22);
    return res;
}
static inline TSimdFloat3x2 tfLoadSimd2x3F(
  float m00, float m01, 
  float m10, float m11, 
  float m20, float m21
) {
    TSimdFloat3x2 res;
    res.mCol0 = tfSimdFloat3x32Load(m00, m10, m20);
    res.mCol1 = tfSimdFloat3x32Load(m01, m11, m21);
    return res;
}
static inline TSimdFloat3x1 tfLoadSimd1x3F(
  float m00,   
  float m10, 
  float m20 
) {
    TSimdFloat3x1 res;
    res.mCol0 = tfSimdFloat3x32Load(m00, m10, m20);
    return res;
}

static inline void tfSetElemSimd3x3F(TSimdFloat3x3* input, int col, int row, float value){
  ASSERT(col >= 0 && col < 3);
  ASSERT(row >= 0 && row < 3);
  switch (row)
  {
    case 0: input->mCol[col] = tfSimdFloat3x32ReplaceIndex0ByValue(input->mCol[col], value); break;
    case 1: input->mCol[col] = tfSimdFloat3x32ReplaceIndex1ByValue(input->mCol[col], value); break;
    case 2: input->mCol[col] = tfSimdFloat3x32ReplaceIndex2ByValue(input->mCol[col], value); break;
  }
}

static inline void tfSetElemSimd2x3F(TSimdFloat3x2* input, int col, int row, float value){

  ASSERT(col >= 0 && col < 2);
  ASSERT(row >= 0 && row < 3);
  switch (row)
  {
    case 0: input->mCol[col] = tfSimdFloat3x32ReplaceIndex0ByValue(input->mCol[col], value); break;
    case 1: input->mCol[col] = tfSimdFloat3x32ReplaceIndex1ByValue(input->mCol[col], value); break;
    case 2: input->mCol[col] = tfSimdFloat3x32ReplaceIndex2ByValue(input->mCol[col], value); break;
  }
}

static inline void tfSetElemSimd1x3F(TSimdFloat3x1* input, int col, int row, float value){
  ASSERT(col >= 0 && col < 1);
  ASSERT(row >= 0 && row < 3);
  switch (row)
  {
    case 0: input->mCol[col] = tfSimdFloat3x32ReplaceIndex0ByValue(input->mCol[col], value); break;
    case 1: input->mCol[col] = tfSimdFloat3x32ReplaceIndex1ByValue(input->mCol[col], value); break;
    case 2: input->mCol[col] = tfSimdFloat3x32ReplaceIndex2ByValue(input->mCol[col], value); break;
  }
}

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

static inline bool tfIsCloseSimd3F(TSimdFloat3 a, TSimdFloat3 b, float epsilon) {
    return tfSimdFloat32x3CmpAllLt(tfSimd3fAbs(tfSimd3fSub(a.mRow, b.mRow)), tfSimd3fSplat(epsilon));
}

static inline float tfVectorDot3F(TSimdFloat3 a0, TSimdFloat3 a1) {
    TSimdFloat32x3 x2 = tfSimd3fMul(a0.mRow, a1.mRow);
    TSimdFloat32x3 xy = tfSimd3fAdd(tfSimd3fSplatIndex1(x2), x2);
    TSimdFloat32x3 xyz = tfSimd3fAdd(tfSimd3fSplatIndex2(x2), xy);
    return tfSimd3fSelectIndex0(xyz);
}



static inline bool tfIsCloseSimd4x4F(TSimdFloat4x4 a, TSimdFloat4x4 b, float epsilon)
{
    return tfIsCloseSimd4F({a.mCol0}, {b.mCol0}, epsilon) && 
           tfIsCloseSimd4F({a.mCol1}, {b.mCol1}, epsilon) &&
           tfIsCloseSimd4F({a.mCol2}, {b.mCol2}, epsilon) && 
           tfIsCloseSimd4F({a.mCol3}, {b.mCol3}, epsilon);
}



static inline TSimdFloat2x2 tfLoadSimd2x2F(
  float m00, float m01,
  float m10, float m11 
) {
  TSimdFloat2x2 result;
  result.mCol0 = tfSimdFloat2x32Load(m00, m10);
  result.mCol1 = tfSimdFloat2x32Load(m01, m11);
  return result;
}
static inline TSimdFloat2x1 tfLoadSimd2x1F(
  float m00, 
  float m10 
) {
  TSimdFloat2x1  result;
  result.mCol0 = tfSimdFloat2x32Load(m00, m10);
  return result;
} 

static inline TSimdFloat2 tfLoadSimd2F(float x, float y) {
  TSimdFloat2 res;
  res.mRow = tfSimdFloat2x32Load(x,y);
  return res;

}

static inline TSimdFloat2 tfVectorMul2x2F(const TSimdFloat2x2 a0, const TSimdFloat2 a1) {
    TSimdFloat32x2 xx = tfSimd2fSplatIndex0(a1.mRow);
    TSimdFloat32x2 yy = tfSimd2fSplatIndex1(a1.mRow);
    TSimdFloat32x2 res = tfSimd2fMul(a0.mCol0, xx);
    res = tfSimd2fMadd(a0.mCol1, yy, res);
    return { res };
}

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

static inline TSimdFloat3 tfVectorEleDiv3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fDiv(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleDiv2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fDiv(a0.mRow, a1.mRow) }; }

static inline TSimdFloat3 tfVectorEleSub3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fSub(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleSub2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fSub(a0.mRow, a1.mRow) }; }

static inline TSimdFloat3 tfVectorEleAdd3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fAdd(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleAdd2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fAdd(a0.mRow, a1.mRow) }; }

static inline TSimdFloat3 tfVectorEleMul3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fMul(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleMul2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fMul(a0.mRow, a1.mRow) }; }

