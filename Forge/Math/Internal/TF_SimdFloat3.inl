#if defined(__CLANGD__)
#include "../TF_SimdFloat3.h"
#endif

#include "Forge/Math/TF_Simd32x3.h"

static inline TSimdFloat3x3 tfLoadZeroSimd3x3F() {
    TSimdFloat3x3 res;
    //res.mRow = tfS32x3FZero();
    return res;
}

static inline TSimdFloat3 tfLoadSimd3F(float x, float y, float z) {
    TSimdFloat3 res;
    res.mRow = tfSimd3x32FLoad(x, y, z);
    return res;
}
