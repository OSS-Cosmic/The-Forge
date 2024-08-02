
#if defined(__CLANGD__)
#include "../TF_SimdFloat4x4.h"
#endif

#include "Forge/Math/TF_Simd32x4.h"

static inline TSimdFloat4 tfGetRowSimd4x4F(TSimdFloat4x4 input, int row) {
  ASSERT(row >= 0 && row < 4);
  switch(row) {
    case 0: return {tfS32x4FLoad(
                    tfSimd4fSelectIndex0(input.mCol0),
                    tfSimd4fSelectIndex0(input.mCol1),
                    tfSimd4fSelectIndex0(input.mCol2),
                    tfSimd4fSelectIndex0(input.mCol3)
                    )};
    case 1: return {tfS32x4FLoad(
                    tfS32x4FSelectIndex1(input.mCol0),
                    tfS32x4FSelectIndex1(input.mCol1),
                    tfS32x4FSelectIndex1(input.mCol2),
                    tfS32x4FSelectIndex1(input.mCol3))};
    case 2: return {tfS32x4FLoad(
                    tfS32x4FSelectIndex2(input.mCol0),
                    tfS32x4FSelectIndex2(input.mCol1),
                    tfS32x4FSelectIndex2(input.mCol2),
                   tfS32x4FSelectIndex2(input.mCol3))};
    case 3: return {tfS32x4FLoad(
                    tfS32x4FSelectIndex3(input.mCol0),
                    tfS32x4FSelectIndex3(input.mCol1),
                    tfS32x4FSelectIndex3(input.mCol2),
                    tfS32x4FSelectIndex3(input.mCol3))};
  }
  return {};
}

static inline void tfSetRowSimd4x4F(TSimdFloat4x4* input, int row, TSimdFloat4 value) {
   // ASSERT(row >= 0 && row < 4);
   // switch (row) {
   // case 0:
   //     input->mCol0 = tfS32x4FReplaceIndex0(input->mCol0, tfS32x4FSplatIndex0(value));
   // }
    return {};
}
static inline TSimdFloat4 tfGetColumnSimd4x4F(int column);
static inline void tfSetColumnSimd4x4F(TSimdFloat4x4* input, int row);
static inline void tfSetElemSimd4x4F(TSimdFloat4x4* input, int col, int row, float value);


//static inline void tfSetElemSimd3x4F(TSimdFloat4x3* input, int col, int row, float value){
//  ASSERT(col >= 0 && col < 3);
//  ASSERT(row >= 0 && row < 4);
//  switch (row)
//  {
//    case 0: input->mCol[col] = tfSimd4fReplaceIndex0ByValue(input->mCol[col], value); break;
//    case 1: input->mCol[col] = tfSimd4fReplaceIndex1ByValue(input->mCol[col], value); break;
//    case 2: input->mCol[col] = tfSimd4fReplaceIndex2ByValue(input->mCol[col], value); break;
//    case 3: input->mCol[col] = tfSimd4fReplaceIndex3ByValue(input->mCol[col], value); break;
//  }
//}


static inline TSimdFloat4 tfVectorMulSimd4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1) {
    Tsimd_f32x4_t xxxx = tfSimd4fSplatIndex0(a1.mRow);
    Tsimd_f32x4_t yyyy = tfSimd4fSplatIndex1(a1.mRow);
    Tsimd_f32x4_t zzzz = tfSimd4fSplatIndex2(a1.mRow);
    Tsimd_f32x4_t wwww = tfSimd4fSplatIndex3(a1.mRow);
    Tsimd_f32x4_t res = tfSimd4fMul(a0.mCol0, xxxx);
    res = tfSimd4fMadd(a0.mCol1, yyyy, res);
    res = tfSimd4fMadd(a0.mCol2, zzzz, res);
    res = tfSimd4fMadd(a0.mCol3, wwww, res);
    return { res };
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
    value.mCol0 = tfSimdFloat4x32Load(1, 0, 0, 0);
    value.mCol1 = tfSimdFloat4x32Load(0, 1, 0, 0);
    value.mCol2 = tfSimdFloat4x32Load(0, 0, 1, 0);
    value.mCol3 = tfSimdFloat4x32Load(0, 0, 0, 1);
    return value;
}

static inline TSimdFloat4x4 tfMulSimd4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1) {
    TSimdFloat4x4 res;
    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    res.mCol2 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
    res.mCol3 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol3 }).mRow;
    return res;
}

static inline TSimdFloat4x3 tfMulSimd4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat4x3 a1) {
    TSimdFloat4x3 res;
    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    res.mCol2 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
    return res;
}
static inline TSimdFloat4x2 tfMulSimd4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat4x2 a1) {
    TSimdFloat4x2 res;
    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    return res;
}
static inline TSimdFloat4x1 tfMulSimd4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat4x1 a1) {
    TSimdFloat4x1 res;
    res.mCol0 = tfVectorMulSimd4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    return res;
}
