#if defined(__CLANGD__)
#include "../TF_Matrix.h"
#endif

// conviences if cpp is avaliable
#ifdef __cplusplus
static inline TSimdFloat4 operator*(const TSimdFloat4x4 a0, const TSimdFloat4 a1) { return tfVectorMul4x4F(a0, a1); }
static inline TSimdFloat3 operator*(const TSimdFloat3x3 a0, const TSimdFloat3 a1) { return tfVectorMul3x3F(a0, a1); }
static inline TSimdFloat2 operator*(const TSimdFloat2x2 a0, const TSimdFloat2 a1) { return tfVectorMul2x2F(a0, a1); }
#endif


static inline TSimdFloat4x4 tfMatMul4x4F_4x4F(TSimdFloat4x4 a0, TSimdFloat4x4 a1) {
    TSimdFloat4x4 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    res.mCol2 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
    res.mCol3 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol3 }).mRow;
    return res;
}

static inline TSimdFloat3x4 tfMatMul4x4F_3x4F(TSimdFloat4x4 a0, TSimdFloat3x4 a1) {
    TSimdFloat3x4 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    res.mCol2 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol2 }).mRow;
    return res;
}
static inline TSimdFloat2x4 tfMatMul4x4F_2x4F(TSimdFloat4x4 a0, TSimdFloat2x4 a1) {
    TSimdFloat2x4 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    res.mCol1 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol1 }).mRow;
    return res;
}
static inline TSimdFloat1x4 tfMatMul4x4F_1x4F(TSimdFloat4x4 a0, TSimdFloat1x4 a1) {
    TSimdFloat1x4 res;
    res.mCol0 = tfVectorMul4x4F(a0, TSimdFloat4{ a1.mCol0 }).mRow;
    return res;
}
static inline TSimdFloat4 tfVectorEleDiv4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimd4fDiv(a0.mRow, a1.mRow) }; }
static inline TSimdFloat3 tfVectorEleDiv3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fDiv(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleDiv2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fDiv(a0.mRow, a1.mRow) }; }

static inline TSimdFloat4 tfVectorEleSub4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimd4fSub(a0.mRow, a1.mRow) }; }
static inline TSimdFloat3 tfVectorEleSub3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fSub(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleSub2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fSub(a0.mRow, a1.mRow) }; }

static inline TSimdFloat4 tfVectorEleAdd4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimd4fAdd(a0.mRow, a1.mRow) }; }
static inline TSimdFloat3 tfVectorEleAdd3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fAdd(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleAdd2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fAdd(a0.mRow, a1.mRow) }; }

static inline TSimdFloat4 tfVectorEleMul4F(TSimdFloat4 a0, TSimdFloat4 a1) { return { tfSimd4fMul(a0.mRow, a1.mRow) }; }
static inline TSimdFloat3 tfVectorEleMul3F(TSimdFloat3 a0, TSimdFloat3 a1) { return { tfSimd3fMul(a0.mRow, a1.mRow) }; }
static inline TSimdFloat2 tfVectorEleMul2F(TSimdFloat2 a0, TSimdFloat2 a1) { return { tfSimd2fMul(a0.mRow, a1.mRow) }; }

/**
 * Multiplication of a 4x4 matrix and a 4 element vector
 **/
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

static inline TSimdFloat4 tfVectorMul3x4F(const TSimdFloat3x4 a0, const TSimdFloat3 a1) {
    TSimdFloat32x4 xxxx = tfSimdFloat3To4Splat0(a1.mRow);
    TSimdFloat32x4 yyyy = tfSimdFloat3To4Splat1(a1.mRow);
    TSimdFloat32x4 zzzz = tfSimdFloat3To4Splat2(a1.mRow);
    TSimdFloat32x4 res = tfSimd4fMul(a0.mCol0, xxxx);
    res = tfSimd4fMadd(a0.mCol1, yyyy, res);
    res = tfSimd4fMadd(a0.mCol2, zzzz, res);
    return { res };
}

static inline TSimdFloat4 tfVectorMul2x4F(const TSimdFloat2x4 a0, const TSimdFloat2 a1) {
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

/**
 * Multiplication of a 2x2 matrix and a 4 element vector
 **/
static inline TSimdFloat2 tfVectorMul2x2F(const TSimdFloat2x2 a0, const TSimdFloat2 a1) {
    TSimdFloat32x2 xx = tfSimd2fSplatIndex0(a1.mRow);
    TSimdFloat32x2 yy = tfSimd2fSplatIndex1(a1.mRow);
    TSimdFloat32x2 res = tfSimd2fMul(a0.mCol0, xx);
    res = tfSimd2fMadd(a0.mCol1, yy, res);
    return { res };
}

