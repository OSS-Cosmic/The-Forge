#include "Internal/SimdTypes.h"
#include "Internal/ScalarTypes.h"
#include "TF_Simd4x32.h"

inline TSimdFloat2x2 tfMatrixTranspose(TSimdFloat2x2 a0);
inline TSimdFloat4x4 tfMatrixTranspose(TSimdFloat4x4 a0);
inline TSimdFloat3x3 tfMatrixTranspose(TSimdFloat3x3 a0);

inline TSimdFloat2x2 tfMatrixMul(TSimdFloat2x2 a0, TSimdFloat2x2 a1);
inline TSimdFloat3x3 tfMatrixMul(TSimdFloat3x3 a0, TSimdFloat3x3 a1);
inline TSimdFloat4x4 tfMatrixMul(TSimdFloat4x4 a0, TSimdFloat4x4 a1);


inline TSimdFloat4x4 tfVectorMul(TSimdFloat4x4 a0, TSimdFloat4 a1); 


/**
  * Multiplication of a 4x4 matrix and a 4 element vector
  **/
inline TSimdFloat4x4 tfVectorMul(TSimdFloat4x4 a0, TSimdFloat4 a1) {
  TSimdFloat4 xxxx = tfSimd4fSplatIndex0(a1);
  TSimdFloat4 yyyy = tfSimd4fSplatIndex1(a1);
  TSimdFloat4 zzzz = tfSimd4fSplatIndex2(a1);
  TSimdFloat4 wwww = tfSimd4fSplatIndex3(a1);
  TSimdFloat4 res = tfSimd4fMul(a0.mCol0, xxxx);
  res = tfSimd4fMadd(a0.mCol1, yyyy, res);
  res = tfSimd4fMadd(a0.mCol2, zzzz, res);
  res = tfSimd4fMadd(a0.mCol3, wwww, res);
  return {res};
}

