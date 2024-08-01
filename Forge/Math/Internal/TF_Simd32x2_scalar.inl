#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x2.h"
#endif

inline TSimdInt32x2 tfSimd2iSelect(TSimdInt32x2 arg0, TSimdInt32x2 arg1, TSimdInt32x2 mask) {
    return { (mask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1] };
}
inline TSimdFloat32x2 tfSimd2fSelect(TSimdFloat32x2 arg0, TSimdFloat32x2 arg1, TSimdFloat32x2 mask) {
    TSimdInt32x2 intMask = tfSimd2fToSimd2i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1] };
}

inline TSimdFloat32x2 tfSimd2fZero() { return { 0, 0 }; }
inline TSimdInt32x2   tfSimd2iZero() { return { 0, 0 }; }

inline TSimdInt32x2 tfSimd2iNot(TSimdInt32x2 value) { return { ~value.v[0], ~value.v[1] }; }
inline TSimdInt32x2 tfSimd2iAnd(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1] }; }
inline TSimdInt32x2 tfSimd2iAndNot(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1] }; }
inline TSimdInt32x2 tfSimd2iOr(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1] }; }
inline TSimdInt32x2 tfSimd2iXor(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1] }; }

inline TSimdFloat32x2 tfSimd2fNot(TSimdFloat32x2 value) {
    TSimdInt32x2 result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]) } };
    return tfSimd2iToSimd2f(result);
}
inline TSimdFloat32x2 tfSimd2fAnd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    TSimdInt32x2 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]) };
    return tfSimd2iToSimd2f(result);
}
inline TSimdFloat32x2 tfSimd2fAndNot(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    TSimdInt32x2 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]) } };
    return tfSimd2iToSimd2f(result);
}
inline TSimdFloat32x2 tfSimd2fOr(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    TSimdInt32x2 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]) } };
    return tfSimd2iToSimd2f(result);
}
inline TSimdFloat32x2 tfSimd2fXor(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    TSimdInt32x2 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]) } };
    return tfSimd2iToSimd2f(result);
}

inline TSimdFloat32x2 tfSimd2fFloor(TSimdFloat32x2 value) { return { { floorf(value.v[0]), floorf(value.v[1]) } }; }
inline TSimdFloat32x2 tfSimd2fCeil(TSimdFloat32x2 value) { return { { ceilf(value.v[0]), ceilf(value.v[1]) } }; }
inline TSimdFloat32x2 tfSimd2fRound(TSimdFloat32x2 value) {
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]) } };
}
inline TSimdFloat32x2 tfSimd2fTruncate(TSimdFloat32x2 value) { return tfSimd2iToSimd2f(tfSimd2fToSimd2i(value)); }
inline TSimdFloat32x2 tfSimd2fMin(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]) } };
}
inline TSimdFloat32x2 tfSimd2fMax(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]) } };
}
inline TSimdFloat32x2 tfSimd2fClamp(TSimdFloat32x2 value, TSimdFloat32x2 min, TSimdFloat32x2 max) {
    return tfSimd2fMax(min, tfSimd2fMin(value, max));
}

inline TSimdInt32x2 tfSimd2fToSimd2i(TSimdFloat32x2 value) { return { (int32_t)value.v[0], (int32_t)value.v[1] }; }

inline TSimdFloat32x2 tfSimd2iToSimd2f(TSimdInt32x2 value) { return { (float)value.v[0], (float)value.v[1] }; }

inline float tfSimd2fSelectIndex0(TSimdFloat32x2 value) { return value.v[0]; }

inline float tfSimd2fSelectIndex1(TSimdFloat32x2 value) { return value.v[1]; }

inline TSimdFloat32x2 tfSimd2fAdd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
    };
}
inline TSimdFloat32x2 tfSimd2fSub(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
    };
}
inline TSimdFloat32x2 tfSimd2fMul(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
    };
}
inline TSimdFloat32x2 tfSimd2fMadd(TSimdFloat32x2 mul1, TSimdFloat32x2 mul2, TSimdFloat32x2 add) {
    return tfSimd2fAdd(tfSimd2fMul(mul1, mul2), add);
}
inline TSimdFloat32x2 tfSimd2fDiv(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
    };
}
inline TSimdFloat32x2 tfSimd2fAbs(TSimdFloat32x2 value) {
    return {
        abs(value.v[0]),
        abs(value.v[1]),
    };
}

inline TSimdFloat32x2 tfSimdFloat2Load(float x, float y) { return { x, y }; }

inline TSimdInt32x2 tfSimd2iLoadImmediate(int32_t x, int32_t y) { return { x, y }; }

inline TSimdFloat32x2 tfSimd2fSplatIndex0(TSimdFloat32x2 value) { return { value.v[0], value.v[0] }; }
inline TSimdFloat32x2 tfSimd2fSplatIndex1(TSimdFloat32x2 value) { return { value.v[1], value.v[1] }; }

static inline TSimdFloat32x4 tfSimdFloat2To4Splat0(TSimdFloat32x2 value) { return { value.v[0], value.v[0], value.v[0], value.v[0] }; }
static inline TSimdFloat32x4 tfSimdFloat2To4Splat1(TSimdFloat32x2 value) { return { value.v[1], value.v[1], value.v[1], value.v[1] }; }

inline TSimdInt32x2 tfSimd2iSplat(int32_t value) { return { value, value }; }
inline TSimdFloat32x2 tfSimd2fSplat(float value) { return { value, value }; }

inline TSimdInt32x2 tfSimd2iCmpEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x2 tfSimd2iCmpNeq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x2 tfSimd2iCmpGt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x2 tfSimd2iCmpGtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x2 tfSimd2iCmpLt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x2 tfSimd2iCmpLtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}

inline bool tfSimd2fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    for (int i = 0; i < 2; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

inline bool tfSimd2iCmpAllEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
    for (int i = 0; i < 2; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

static inline bool tfSimdFloat32x2CmpAllLt(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    for (int i = 0; i < 2; i++) {
        if (arg1.v[i] >= arg2.v[i]) {
            return false;
        }
    }
    return true;
}
