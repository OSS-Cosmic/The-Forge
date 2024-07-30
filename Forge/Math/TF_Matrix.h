#include "Internal/SimdTypes.h"
#include "Internal/ScalarTypes.h"

#include "TF_Simd4x32.h"
#include "TF_Simd3x32.h"
#include "TF_Simd2x32.h"

#include "Forge/TF_Log.h"

static inline TSimdFloat4x4 tfMatMul4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
static inline TSimdFloat3x4 tfMatMul4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat3x4 a1);
static inline TSimdFloat2x4 tfMatMul4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat2x4 a1);
static inline TSimdFloat1x4 tfMatMul4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat1x4  a1);

static inline TSimdFloat3x3 tfMatrixMul2x2F_2x2F(TSimdFloat2x2 a0, TSimdFloat2x2  a1);
static inline TSimdFloat3x3 tfMatrixMul2x2F_1x2F(TSimdFloat2x2 a0, TSimdFloat1x2  a1);

static inline TSimdFloat3x3 tfMatrixMul(const TSimdFloat3x3 a0, const TSimdFloat3x3 a1);
static inline TSimdFloat3x3 tfMatrixMul(const TSimdFloat3x3 a0, const TSimdFloat2x3 a1);
static inline TSimdFloat3x3 tfMatrixMul(const TSimdFloat3x3 a0, const TSimdFloat1x3 a1);

static inline TSimdFloat4 tfVectorMul4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1);
static inline TSimdFloat3 tfVectorMul3x3F(const TSimdFloat3x3 a0, const TSimdFloat3 a1);
static inline TSimdFloat2 tfVectorMul2x2F(const TSimdFloat2x2 a0, const TSimdFloat2 a1);

static inline TSimdFloat2 tfVectorEleAdd2F(TSimdFloat2 a0, TSimdFloat2  a1);
static inline TSimdFloat2 tfVectorEleAdd3F(TSimdFloat2 a0, TSimdFloat2  a1);
static inline TSimdFloat2 tfVectorEleAdd4F(TSimdFloat2 a0, TSimdFloat2  a1);



// conviences if cpp is avaliable
#ifdef __cplusplus
static inline TSimdFloat4 operator*(const TSimdFloat4x4 a0, const TSimdFloat4 a1) { return tfVectorMul4x4F(a0, a1); }
#endif

/**
  * Multiplication of a 4x4 matrix and a 4 element vector
  **/
static inline TSimdFloat4 tfVectorMul4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1)
{
    TSimdFloat32x4 xxxx = tfSimd4fSplatIndex0(a1.mRow);
    TSimdFloat32x4 yyyy = tfSimd4fSplatIndex1(a1.mRow);
    TSimdFloat32x4 zzzz = tfSimd4fSplatIndex2(a1.mRow);
    TSimdFloat32x4 wwww = tfSimd4fSplatIndex3(a1.mRow);
    TSimdFloat32x4 res = tfSimd4fMul(a0.mCol0, xxxx);
    res = tfSimd4fMadd(a0.mCol1, yyyy, res);
    res = tfSimd4fMadd(a0.mCol2, zzzz, res);
    res = tfSimd4fMadd(a0.mCol3, wwww, res);
    return { res };
}

/**
  * Multiplication of a 3x3 matrix and a 4 element vector
  **/
static inline TSimdFloat3 tfVectorMul3x3F(const TSimdFloat3x3 a0, const TSimdFloat3 a1) {
  TSimdFloat32x3 xxxx = tfSimd3fSplatIndex0(a1.mRow);
  TSimdFloat32x3 yyyy = tfSimd3fSplatIndex1(a1.mRow);
  TSimdFloat32x3 zzzz = tfSimd3fSplatIndex2(a1.mRow);
  TSimdFloat32x3 res = tfSimd3fMul(a0.mCol0, xxxx);
  res = tfSimd3fMadd(a0.mCol1, yyyy, res);
  res = tfSimd3fMadd(a0.mCol2, zzzz, res);
  return {res};
}

/**
  * Multiplication of a 2x2 matrix and a 4 element vector
  **/
static inline TSimdFloat2 tfVectorMul2x2F(const TSimdFloat2x2 a0, const TSimdFloat2 a1)
{
    TSimdFloat32x2 xx = tfSimd2fSplatIndex0(a1.mRow);
    TSimdFloat32x2 yy = tfSimd2fSplatIndex1(a1.mRow);
    TSimdFloat32x2 res = tfSimd2fMul(a0.mCol0, xx);
    res = tfSimd2fMadd(a0.mCol1, yy, res);
    return { res };
}
