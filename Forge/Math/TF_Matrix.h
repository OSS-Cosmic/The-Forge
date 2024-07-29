#include "Forge/Math/Internal/SimdTypes.h"
#include "Internal/SimdTypes.h"
#include "Internal/ScalarTypes.h"
#include "TF_Simd4x32.h"

static inline TSimdFloat4x4 tfMatMul4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1);
static inline TSimdFloat3x4 tfMatMul4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat3x4 a1);
static inline TSimdFloat2x4 tfMatMul4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat2x4 a1);
static inline TSimdFloat1x4 tfMatMul4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat1x4  a1);

static inline TSimdFloat3x3 tfMatrixMul2x2F_2x2F(TSimdFloat2x2 a0, TSimdFloat2x2  a1);
static inline TSimdFloat3x3 tfMatrixMul2x2F_1x2F(TSimdFloat2x2 a0, TSimdFloat1x2  a1);

static inline TSimdFloat3x3 tfMatrixMul(TSimdFloat3x3 a0, TSimdFloat3x3  a1);
static inline TSimdFloat3x3 tfMatrixMul(TSimdFloat3x3 a0, TSimdFloat2x3  a1);
static inline TSimdFloat3x3 tfMatrixMul(TSimdFloat3x3 a0, TSimdFloat1x3  a1);

static inline TSimdFloat4x4 tfVectorMul4x4F(TSimdFloat4x4 a0, TSimdFloat4  a1);
static inline TSimdFloat4x4 tfVectorMul3x3F(TSimdFloat3x3 a0, TSimdFloat3  a1);
static inline TSimdFloat2x2 tfVectorMul2x2F(TSimdFloat2x2 a0, TSimdFloat2  a1);


// conviences if cpp is avaliable
#ifdef __cplusplus
  static inline TSimdFloat4x4 operator*(const TSimdFloat4x4& a, const TSimdFloat4x4& b) {  }
#endif

/**
  * Multiplication of a 4x4 matrix and a 4 element vector
  **/
static inline TSimdFloat4x4 tfVectorMul(TSimdFloat4x4 a0, TSimdFloat4  a1) {
  TSimdFloat32x4 xxxx = tfSimd4fSplatIndex0(a1.mRow);
  TSimdFloat32x4 yyyy = tfSimd4fSplatIndex1(a1.mRow);
  TSimdFloat32x4 zzzz = tfSimd4fSplatIndex2(a1.mRow);
  TSimdFloat32x4 wwww = tfSimd4fSplatIndex3(a1.mRow);
  TSimdFloat32x4 res = tfSimd4fMul(a0.mCol0, xxxx);
  res = tfSimd4fMadd(a0.mCol1, yyyy, res);
  res = tfSimd4fMadd(a0.mCol2, zzzz, res);
  res = tfSimd4fMadd(a0.mCol3, wwww, res);
  return {res};
}




