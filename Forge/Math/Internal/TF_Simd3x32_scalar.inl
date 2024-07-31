#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR  
#include "Forge/TF_Config.h"
#include "../TF_Simd3x32.h"
#endif

inline TSimdInt32x3 tfSimd3iSelect(TSimdInt32x3 arg0, TSimdInt32x3 arg1, TSimdInt32x3 mask) {
    return { (mask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1], (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2] };
}
inline TSimdFloat32x3 tfSimd3fSelect(TSimdFloat32x3 arg0, TSimdFloat32x3 arg1, TSimdFloat32x3 mask) {
    TSimdInt32x3 intMask = tfSimd3fToSimd3i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1],
             (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2] };
}

inline TSimdFloat32x3 tfSimd3fZero() { return { 0, 0, 0 }; }
inline TSimdInt32x3   tfSimd3iZero() { return { 0, 0, 0 }; }

inline TSimdInt32x3 tfSimd3iNot(TSimdInt32x3 value) { return { ~value.v[0], ~value.v[1], ~value.v[2] }; }
inline TSimdInt32x3 tfSimd3iAnd(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2] };
}
inline TSimdInt32x3 tfSimd3iAndNot(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2] };
}
inline TSimdInt32x3 tfSimd3iOr(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2] };
}
inline TSimdInt32x3 tfSimd3iXor(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2] };
}

inline TSimdFloat32x3 tfSimd3fNot(TSimdFloat32x3 value) {
    TSimdInt32x3 result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]), ~((int32_t)value.v[2]) } };
    return tfSimd3iToSimd3f(result);
}
inline TSimdFloat32x3 tfSimd3fAnd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    TSimdInt32x3 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                            ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) };
    return tfSimd3iToSimd3f(result);
}
inline TSimdFloat32x3 tfSimd3fAndNot(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    TSimdInt32x3 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                              ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
}
inline TSimdFloat32x3 tfSimd3fOr(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    TSimdInt32x3 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                              ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
}
inline TSimdFloat32x3 tfSimd3fXor(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    TSimdInt32x3 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                              ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]) } };
    return tfSimd3iToSimd3f(result);
}

inline TSimdFloat32x3 tfSimd3fFloor(TSimdFloat32x3 value) { return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]) } }; }
inline TSimdFloat32x3 tfSimd3fCeil(TSimdFloat32x3 value) { return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]) } }; }
inline TSimdFloat32x3 tfSimd3fRound(TSimdFloat32x3 value) {
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]) } };
}
inline TSimdFloat32x3 tfSimd3fTruncate(TSimdFloat32x3 value) { return tfSimd3iToSimd3f(tfSimd3fToSimd3i(value)); }
inline TSimdFloat32x3 tfSimd3fMin(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]) } };
}
inline TSimdFloat32x3 tfSimd3fMax(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]) } };
}
inline TSimdFloat32x3 tfSimd3fClamp(TSimdFloat32x3 value, TSimdFloat32x3 min, TSimdFloat32x3 max) {
    return tfSimd3fMax(min, tfSimd3fMin(value, max));
}

inline TSimdInt32x3 tfSimd3fToSimd3i(TSimdFloat32x3 value) { return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2] }; }

inline TSimdFloat32x3 tfSimd3iToSimd3f(TSimdInt32x3 value) { return { (float)value.v[0], (float)value.v[1], (float)value.v[2] }; }

inline float tfSimd3fSelectIndex0(TSimdFloat32x3 value) { return value.v[0]; }

inline float tfSimd3fSelectIndex1(TSimdFloat32x3 value) { return value.v[1]; }

inline float tfSimd3fSelectIndex2(TSimdFloat32x3 value) { return value.v[2]; }

inline TSimdFloat32x3 tfSimd3fAdd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
        arg1.v[2] + arg2.v[2],
    };
}
inline TSimdFloat32x3 tfSimd3fSub(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
        arg1.v[2] - arg2.v[2],
    };
}
inline TSimdFloat32x3 tfSimd3fMul(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
        arg1.v[2] * arg2.v[2],
    };
}
inline TSimdFloat32x3 tfSimd3fMadd(TSimdFloat32x3 mul1, TSimdFloat32x3 mul2, TSimdFloat32x3 add) {
    return tfSimd3fAdd(tfSimd3fMul(mul1, mul2), add);
}
inline TSimdFloat32x3 tfSimd3fDiv(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return { arg1.v[0] / arg2.v[0], arg1.v[1] / arg2.v[1], arg1.v[2] / arg2.v[2] };
}

inline TSimdFloat32x3 tfSimd3fAbs(TSimdFloat32x3 value) {
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
    };
}

inline TSimdFloat32x3 tfSimdFloat3Load(float x, float y, float z) { return { x, y, z }; }
inline TSimdInt32x3 tfSimdInt3Load(int32_t x, int32_t y, int32_t z) { return { x, y, z }; }

inline TSimdFloat32x2 tfSimd3fToSimd2f(TSimdFloat32x3 value) { return { value.v[0], value.v[1] }; }

static inline TSimdFloat32x4 tfSimdFloat3To4Splat0(TSimdFloat32x3 value) { return { value.v[0], value.v[0], value.v[0], value.v[0] }; }
static inline TSimdFloat32x4 tfSimdFloat3To4Splat1(TSimdFloat32x3 value) { return { value.v[1], value.v[1], value.v[1], value.v[1] }; }
static inline TSimdFloat32x4 tfSimdFloat3To4Splat2(TSimdFloat32x3 value) { return { value.v[2], value.v[2], value.v[2], value.v[2] }; }

inline TSimdFloat32x3 tfSimd3fSplatIndex0(TSimdFloat32x3 value) { return { value.v[0], value.v[0], value.v[0] }; }
inline TSimdFloat32x3 tfSimd3fSplatIndex1(TSimdFloat32x3 value) { return { value.v[1], value.v[1], value.v[1] }; }
inline TSimdFloat32x3 tfSimd3fSplatIndex2(TSimdFloat32x3 value) { return { value.v[2], value.v[2], value.v[2] }; }

inline TSimdInt32x3 tfSimd3iSplat(int32_t value) { return { value, value, value }; }
inline TSimdFloat32x3 tfSimd3fSplat(float value) { return { value, value, value }; }

inline TSimdInt32x3 tfSimd3iCmpEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x3 tfSimd3iCmpNeq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x3 tfSimd3iCmpGt(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x3 tfSimd3iCmpGtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x3 tfSimd3iCmpLt(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x3 tfSimd3iCmpLtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline bool tfSimd3fCmpAllEq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    for (int i = 0; i < 3; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

inline bool tfSimd3iCmpAllEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
    for (int i = 0; i < 3; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}
