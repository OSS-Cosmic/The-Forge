
#if defined(__CLANGD__)
#include "../TF_SimdFloat4x4.h"
#endif

#include "Forge/Math/TF_Simd32x4.h"

static inline TSimdFloat4 tfVectorMul4x4F(const TSimdFloat4x4 a0, const TSimdFloat4 a1) {
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

static inline TSimdFloat4x4 tfMatMul4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1) {
    TSimdFloat4x4 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    res.mCol2 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
    res.mCol3 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol3 }).mRow;
    return res;
}

static inline TSimdFloat4x3 tfMatMul4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat4x3 a1) {
    TSimdFloat4x3 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    res.mCol2 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
    return res;
}
static inline TSimdFloat4x2 tfMatMul4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat4x2 a1) {
    TSimdFloat4x2 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    return res;
}
static inline TSimdFloat4x1 tfMatMul4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat4x1 a1) {
    TSimdFloat4x1 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    return res;
}
