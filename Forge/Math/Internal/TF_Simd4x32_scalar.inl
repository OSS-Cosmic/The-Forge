#if defined(__CLANGD__)
#include "Forge/TF_Config.h"
#undef TF_FEATURE_CPU_NEON  
#undef TF_FEATURE_CPU_SSE  
#define TF_FEATURE_CPU_SCALAR  
#include "../TF_Simd4x32.h"
#endif

static inline TSimdFloat32x4 tfSimd4fReplaceIndex0ByValue(TSimdFloat32x4 input, float value) {
    return { value, input.v[1], input.v[2], input.v[3] };
}
static inline TSimdFloat32x4 tfSimd4fReplaceIndex1ByValue(TSimdFloat32x4 input, float value) {
    return { input.v[0], value, input.v[2], input.v[3] };
}
static inline TSimdFloat32x4 tfSimd4fReplaceIndex2ByValue(TSimdFloat32x4 input, float value) {
    return { input.v[0], input.v[1], value, input.v[3] };
}
static inline TSimdFloat32x4 tfSimd4fReplaceIndex3ByValue(TSimdFloat32x4 input, float value) {
    return { input.v[0], input.v[1], input.v[2], value };
}

inline TSimdInt32x4 tfSimd4iSelect(TSimdInt32x4 arg0, TSimdInt32x4 arg1, TSimdInt32x4 mask) {
    return { (mask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1], (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2],
             (mask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
}
inline TSimdFloat32x4 tfSimd4fSelect(TSimdFloat32x4 arg0, TSimdFloat32x4 arg1, TSimdFloat32x4 mask) {
    TSimdInt32x4 intMask = tfSimd4fToSimd4i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1],
             (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2], (intMask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
}

inline TSimdFloat32x4 tfSimd4fZero() { return { 0, 0, 0, 0 }; }
inline TSimdInt32x4   tfSimd4iZero() { return { 0, 0, 0, 0 }; }

inline TSimdInt32x4 tfSimd4iNot(TSimdInt32x4 value) { return { ~value.v[0], ~value.v[1], ~value.v[2], ~value.v[3] }; }
inline TSimdInt32x4 tfSimd4iAnd(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2], arg1.v[3] & arg2.v[3] };
}
inline TSimdInt32x4 tfSimd4iAndNot(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2], ~arg1.v[3] & arg2.v[3] };
}
inline TSimdInt32x4 tfSimd4iOr(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2], arg1.v[3] | arg2.v[3] };
}
inline TSimdInt32x4 tfSimd4iXor(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2], arg1.v[3] ^ arg2.v[3] };
}

inline TSimdFloat32x4 tfSimd4fNot(TSimdFloat32x4 value) {
    TSimdInt32x4 result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]), ~((int32_t)value.v[2]), ~((int32_t)value.v[3]) } };
    return tfSimd4iToSimd4f(result);
}
inline TSimdFloat32x4 tfSimd4fAnd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdInt32x4 result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                            ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) };
    return tfSimd4iToSimd4f(result);
}
inline TSimdFloat32x4 tfSimd4fAndNot(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdInt32x4 result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                              ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ~((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
}
inline TSimdFloat32x4 tfSimd4fOr(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdInt32x4 result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                              ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) | ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
}
inline TSimdFloat32x4 tfSimd4fXor(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    TSimdInt32x4 result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                              ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) ^ ((int32_t)arg2.v[3]) } };
    return tfSimd4iToSimd4f(result);
}

inline TSimdFloat32x4 tfSimd4fFloor(TSimdFloat32x4 value) {
    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]), floorf(value.v[3]) } };
}
inline TSimdFloat32x4 tfSimd4fCeil(TSimdFloat32x4 value) {
    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]), ceilf(value.v[3]) } };
}
inline TSimdFloat32x4 tfSimd4fRound(TSimdFloat32x4 value) {
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]), rintf(value.v[3]) } };
}
inline TSimdFloat32x4 tfSimd4fTruncate(TSimdFloat32x4 value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
inline TSimdFloat32x4 tfSimd4fMin(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]), fminf(arg1.v[3], arg2.v[3]) } };
}
inline TSimdFloat32x4 tfSimd4fMax(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]), fmaxf(arg1.v[3], arg2.v[3]) } };
}
inline TSimdFloat32x4 tfSimd4fClamp(TSimdFloat32x4 value, TSimdFloat32x4 min, TSimdFloat32x4 max) {
    return tfSimd4fMax(min, tfSimd4fMin(value, max));
}

inline TSimdInt32x4 tfSimd4fToSimd4i(TSimdFloat32x4 value) {
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2], (int32_t)value.v[3] };
}

inline TSimdFloat32x4 tfSimd4iToSimd4f(TSimdInt32x4 value) {
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2], (float)value.v[3] };
}

inline float tfSimd4fSelectIndex0(TSimdFloat32x4 value) { return value.v[0]; }
inline float tfSimd4fSelectIndex1(TSimdFloat32x4 value) { return value.v[1]; }
inline float tfSimd4fSelectIndex2(TSimdFloat32x4 value) { return value.v[2]; }
inline float tfSimd4fSelectIndex3(TSimdFloat32x4 value) { return value.v[3]; }

inline TSimdFloat32x4 tfSimd4fAdd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
        arg1.v[2] + arg2.v[2],
        arg1.v[3] + arg2.v[3],
    };
}
inline TSimdFloat32x4 tfSimd4fSub(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
        arg1.v[2] - arg2.v[2],
        arg1.v[3] - arg2.v[3],
    };
}
inline TSimdFloat32x4 tfSimd4fMul(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
        arg1.v[2] * arg2.v[2],
        arg1.v[3] * arg2.v[3],
    };
}
inline TSimdFloat32x4 tfSimd4fMadd(TSimdFloat32x4 mul1, TSimdFloat32x4 mul2, TSimdFloat32x4 add) {
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
}

inline TSimdFloat32x4 tfSimd4fDiv(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
        arg1.v[2] / arg2.v[2],
        arg1.v[3] / arg2.v[3],
    };
}

inline TSimdFloat32x4 tfSimd4fAbs(TSimdFloat32x4 value) {
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
        abs(value.v[3]),
    };
}
inline TSimdFloat32x4 tfSimdFloat32x4Load(float x, float y, float z, float w) { return { x, y, z, w }; }
inline TSimdInt32x4 tfSimdInt32x4Load(int32_t x, int32_t y, int32_t z, int32_t w) { return { x, y, z, w }; }

inline TSimdFloat32x2 tfSimd4fToSimd2f(TSimdFloat32x4 value) { return { value.v[0], value.v[1] }; }
inline TSimdFloat32x3 tfSimd4fToSimd3f(TSimdFloat32x4 value) { return { value.v[0], value.v[1], value.v[2] }; }

inline TSimdFloat32x4 tfSimd4fSplatIndex0(TSimdFloat32x4 value) { return { value.v[0], value.v[0], value.v[0], value.v[0] }; }
inline TSimdFloat32x4 tfSimd4fSplatIndex1(TSimdFloat32x4 value) { return { value.v[1], value.v[1], value.v[1], value.v[1] }; }
inline TSimdFloat32x4 tfSimd4fSplatIndex2(TSimdFloat32x4 value) { return { value.v[2], value.v[2], value.v[2], value.v[2] }; }
inline TSimdFloat32x4 tfSimd4fSplatIndex3(TSimdFloat32x4 value) { return { value.v[3], value.v[3], value.v[3], value.v[3] }; }

inline TSimdInt32x4 tfSimd4iSplat(int32_t value) { return { value, value, value, value }; }
inline TSimdFloat32x4 tfSimd4fSplat(float value) { return { value, value, value, value }; }

inline TSimdFloat32x4 tfSimd4fCmpEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { (arg1.v[0] == arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] == arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdFloat32x4 tfSimd4fCmpNeq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { (arg1.v[0] != arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] != arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdFloat32x4 tfSimd4fCmpGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { (arg1.v[0] > arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] > arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdFloat32x4 tfSimd4fCmpGtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { (arg1.v[0] >= arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] >= arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdFloat32x4 tfSimd4fCmpLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] < arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdFloat32x4 tfSimd4fCmpLtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return { { (arg1.v[0] <= arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] <= arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] <= arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] <= arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
}

inline TSimdInt32x4 tfSimd4iCmpEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] == arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x4 tfSimd4iCmpNeq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] != arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x4 tfSimd4iCmpGt(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] > arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x4 tfSimd4iCmpGtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] >= arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x4 tfSimd4iCmpLt(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline TSimdInt32x4 tfSimd4iCmpLtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}

inline bool tfSimd4fCmpAllLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    for (int i = 0; i < 4; i++) {
        if (arg1.v[i] >= arg2.v[i]) {
            return false;
        }
    }
    return true;
}

inline bool tfSimd4fCmpAllGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    for (int i = 0; i < 4; i++) {
        if (arg1.v[i] <= arg2.v[i]) {
            return false;
        }
    }
    return true;
}

inline bool tfSimd4fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    for (int i = 0; i < 4; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

inline bool tfSimd4iCmpAllEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    for (int i = 0; i < 4; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}
