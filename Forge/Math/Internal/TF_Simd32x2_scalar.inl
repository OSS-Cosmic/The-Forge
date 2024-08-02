#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x2.h"
#endif

inline Tsimd_i32x2_t tfS32x2ISelect(Tsimd_i32x2_t arg0, Tsimd_i32x2_t arg1, Tsimd_i32x2_t mask) {
    return { (mask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1] };
}
inline Tsimd_f32x2_t tfS32x2FSelect(Tsimd_f32x2_t arg0, Tsimd_f32x2_t arg1, Tsimd_f32x2_t mask) {
    Tsimd_i32x2_t intMask = tfS32x2FToSimd2i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1] };
}

inline Tsimd_f32x2_t tfS32x2FZero() { return { 0, 0 }; }
inline Tsimd_i32x2_t   tfS32x2IZero() { return { 0, 0 }; }

inline Tsimd_i32x2_t tfS32x2INot(Tsimd_i32x2_t value) { return { ~value.v[0], ~value.v[1] }; }
inline Tsimd_i32x2_t tfS32x2IAnd(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1] }; }
inline Tsimd_i32x2_t tfS32x2IAndNot(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1] }; }
inline Tsimd_i32x2_t tfS32x2IOr(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1] }; }
inline Tsimd_i32x2_t tfS32x2IXor(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1] }; }

inline Tsimd_f32x2_t tfS32x2FNot(Tsimd_f32x2_t value) {
    Tsimd_i32x2_t result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]) } };
    return tfS32x2IToSimd2f(result);
}
inline Tsimd_f32x2_t tfS32x2FAnd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    Tsimd_i32x2_t result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]) };
    return tfS32x2IToSimd2f(result);
}
inline Tsimd_f32x2_t tfS32x2FAndNot(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    Tsimd_i32x2_t result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]) } };
    return tfS32x2IToSimd2f(result);
}
inline Tsimd_f32x2_t tfS32x2FOr(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    Tsimd_i32x2_t result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]) } };
    return tfS32x2IToSimd2f(result);
}
inline Tsimd_f32x2_t tfS32x2FXor(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    Tsimd_i32x2_t result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]) } };
    return tfS32x2IToSimd2f(result);
}

inline Tsimd_f32x2_t tfS32x2FFloor(Tsimd_f32x2_t value) { return { { floorf(value.v[0]), floorf(value.v[1]) } }; }
inline Tsimd_f32x2_t tfS32x2FCeil(Tsimd_f32x2_t value) { return { { ceilf(value.v[0]), ceilf(value.v[1]) } }; }
inline Tsimd_f32x2_t tfS32x2FRound(Tsimd_f32x2_t value) {
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]) } };
}
inline Tsimd_f32x2_t tfS32x2FTruncate(Tsimd_f32x2_t value) { return tfS32x2IToSimd2f(tfS32x2FToSimd2i(value)); }
inline Tsimd_f32x2_t tfS32x2FMin(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]) } };
}
inline Tsimd_f32x2_t tfS32x2FMax(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]) } };
}
inline Tsimd_f32x2_t tfS32x2FClamp(Tsimd_f32x2_t value, Tsimd_f32x2_t min, Tsimd_f32x2_t max) {
    return tfS32x2FMax(min, tfS32x2FMin(value, max));
}

inline Tsimd_i32x2_t tfS32x2FToSimd2i(Tsimd_f32x2_t value) { return { (int32_t)value.v[0], (int32_t)value.v[1] }; }

inline Tsimd_f32x2_t tfS32x2IToSimd2f(Tsimd_i32x2_t value) { return { (float)value.v[0], (float)value.v[1] }; }

inline float tfS32x2FSelectIndex0(Tsimd_f32x2_t value) { return value.v[0]; }

inline float tfS32x2FSelectIndex1(Tsimd_f32x2_t value) { return value.v[1]; }

inline Tsimd_f32x2_t tfS32x2FAdd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
    };
}
inline Tsimd_f32x2_t tfS32x2FSub(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
    };
}
inline Tsimd_f32x2_t tfS32x2FMul(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
    };
}
inline Tsimd_f32x2_t tfS32x2FMadd(Tsimd_f32x2_t mul1, Tsimd_f32x2_t mul2, Tsimd_f32x2_t add) {
    return tfS32x2FAdd(tfS32x2FMul(mul1, mul2), add);
}
inline Tsimd_f32x2_t tfS32x2FDiv(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
    };
}
inline Tsimd_f32x2_t tfS32x2FAbs(Tsimd_f32x2_t value) {
    return {
        abs(value.v[0]),
        abs(value.v[1]),
    };
}

inline Tsimd_f32x2_t tfSimdFloat2Load(float x, float y) { return { x, y }; }

inline Tsimd_i32x2_t tfS32x2ILoadImmediate(int32_t x, int32_t y) { return { x, y }; }

inline Tsimd_f32x2_t tfS32x2FSplatIndex0(Tsimd_f32x2_t value) { return { value.v[0], value.v[0] }; }
inline Tsimd_f32x2_t tfS32x2FSplatIndex1(Tsimd_f32x2_t value) { return { value.v[1], value.v[1] }; }

static inline Tsimd_f32x4_t tfSimdFloat2To4Splat0(Tsimd_f32x2_t value) { return { value.v[0], value.v[0], value.v[0], value.v[0] }; }
static inline Tsimd_f32x4_t tfSimdFloat2To4Splat1(Tsimd_f32x2_t value) { return { value.v[1], value.v[1], value.v[1], value.v[1] }; }

inline Tsimd_i32x2_t tfS32x2ISplat(int32_t value) { return { value, value }; }
inline Tsimd_f32x2_t tfS32x2FSplat(float value) { return { value, value }; }

inline Tsimd_i32x2_t tfS32x2ICmpEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x2_t tfS32x2ICmpNeq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x2_t tfS32x2ICmpGt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x2_t tfS32x2ICmpGtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x2_t tfS32x2ICmpLt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x2_t tfS32x2ICmpLtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}

inline bool tfS32x2FCmpAllEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    for (int i = 0; i < 2; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

inline bool tfS32x2ICmpAllEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
    for (int i = 0; i < 2; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

static inline bool tfS32x2FCmpAllLt(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    for (int i = 0; i < 2; i++) {
        if (arg1.v[i] >= arg2.v[i]) {
            return false;
        }
    }
    return true;
}
