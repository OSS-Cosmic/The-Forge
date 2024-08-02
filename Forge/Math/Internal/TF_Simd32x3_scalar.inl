#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x3.h"
#endif

inline Tsimd_i32x3_t tfS32x3iSelect(Tsimd_i32x3_t arg0, Tsimd_i32x3_t arg1, Tsimd_i32x3_t mask) {
    return { (mask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1], (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2] };
}
inline Tsimd_f32x3_t tfS32x3FSelect(Tsimd_f32x3_t arg0, Tsimd_f32x3_t arg1, Tsimd_f32x3_t mask) {
    Tsimd_i32x3_t intMask = tfS32x3FToSimd3i(mask);
    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1],
             (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2] };
}

inline Tsimd_f32x3_t tfS32x3FZero() { return { 0, 0, 0 }; }
inline Tsimd_i32x3_t   tfS32x3iZero() { return { 0, 0, 0 }; }

inline Tsimd_i32x3_t tfS32x3iNot(Tsimd_i32x3_t value) { return { ~value.v[0], ~value.v[1], ~value.v[2] }; }
inline Tsimd_i32x3_t tfS32x3iAnd(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2] };
}
inline Tsimd_i32x3_t tfS32x3iAndNot(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2] };
}
inline Tsimd_i32x3_t tfS32x3iOr(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2] };
}
inline Tsimd_i32x3_t tfS32x3iXor(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2] };
}

inline Tsimd_f32x3_t tfS32x3FNot(Tsimd_f32x3_t value) {
    Tsimd_i32x3_t result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]), ~((int32_t)value.v[2]) } };
    return tfS32x3iToSimd3f(result);
}
inline Tsimd_f32x3_t tfS32x3FAnd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    Tsimd_i32x3_t result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                            ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) };
    return tfS32x3iToSimd3f(result);
}
inline Tsimd_f32x3_t tfS32x3FAndNot(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    Tsimd_i32x3_t result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
                              ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]) } };
    return tfS32x3iToSimd3f(result);
}
inline Tsimd_f32x3_t tfS32x3FOr(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    Tsimd_i32x3_t result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
                              ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]) } };
    return tfS32x3iToSimd3f(result);
}
inline Tsimd_f32x3_t tfS32x3FXor(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    Tsimd_i32x3_t result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
                              ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]) } };
    return tfS32x3iToSimd3f(result);
}

inline Tsimd_f32x3_t tfS32x3FFloor(Tsimd_f32x3_t value) { return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]) } }; }
inline Tsimd_f32x3_t tfS32x3FCeil(Tsimd_f32x3_t value) { return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]) } }; }
inline Tsimd_f32x3_t tfS32x3FRound(Tsimd_f32x3_t value) {
    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
    // away from zero regardless of the current rounding mode, but 'rintf' uses
    // the current rounding mode which is consistent with other implementations.
    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]) } };
}
inline Tsimd_f32x3_t tfS32x3FTruncate(Tsimd_f32x3_t value) { return tfS32x3iToSimd3f(tfS32x3FToSimd3i(value)); }
inline Tsimd_f32x3_t tfS32x3FMin(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]) } };
}
inline Tsimd_f32x3_t tfS32x3FMax(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]) } };
}
inline Tsimd_f32x3_t tfS32x3FClamp(Tsimd_f32x3_t value, Tsimd_f32x3_t min, Tsimd_f32x3_t max) {
    return tfS32x3FMax(min, tfS32x3FMin(value, max));
}

inline Tsimd_i32x3_t tfS32x3FToSimd3i(Tsimd_f32x3_t value) { return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2] }; }

inline Tsimd_f32x3_t tfS32x3iToSimd3f(Tsimd_i32x3_t value) { return { (float)value.v[0], (float)value.v[1], (float)value.v[2] }; }

inline float tfS32x3FSelectIndex0(Tsimd_f32x3_t value) { return value.v[0]; }

inline float tfS32x3FSelectIndex1(Tsimd_f32x3_t value) { return value.v[1]; }

inline float tfS32x3FSelectIndex2(Tsimd_f32x3_t value) { return value.v[2]; }

inline Tsimd_f32x3_t tfS32x3FAdd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
        arg1.v[2] + arg2.v[2],
    };
}
inline Tsimd_f32x3_t tfS32x3FSub(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
        arg1.v[2] - arg2.v[2],
    };
}
inline Tsimd_f32x3_t tfS32x3FMul(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
        arg1.v[2] * arg2.v[2],
    };
}
inline Tsimd_f32x3_t tfS32x3FMadd(Tsimd_f32x3_t mul1, Tsimd_f32x3_t mul2, Tsimd_f32x3_t add) {
    return tfS32x3FAdd(tfS32x3FMul(mul1, mul2), add);
}
inline Tsimd_f32x3_t tfS32x3FDiv(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    return { arg1.v[0] / arg2.v[0], arg1.v[1] / arg2.v[1], arg1.v[2] / arg2.v[2] };
}

inline Tsimd_f32x3_t tfS32x3FAbs(Tsimd_f32x3_t value) {
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
    };
}

inline Tsimd_f32x3_t tfSimd3x32FLoad(float x, float y, float z) { return { x, y, z }; }
inline Tsimd_i32x3_t tfSimd3x32ILoad(int32_t x, int32_t y, int32_t z) { return { x, y, z }; }

inline Tsimd_f32x2_t tfS32x3FToSimd2f(Tsimd_f32x3_t value) { return { value.v[0], value.v[1] }; }

static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat0(Tsimd_f32x3_t value) { return { value.v[0], value.v[0], value.v[0], value.v[0] }; }
static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat1(Tsimd_f32x3_t value) { return { value.v[1], value.v[1], value.v[1], value.v[1] }; }
static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat2(Tsimd_f32x3_t value) { return { value.v[2], value.v[2], value.v[2], value.v[2] }; }

inline Tsimd_f32x3_t tfS32x3FSplatIndex0(Tsimd_f32x3_t value) { return { value.v[0], value.v[0], value.v[0] }; }
inline Tsimd_f32x3_t tfS32x3FSplatIndex1(Tsimd_f32x3_t value) { return { value.v[1], value.v[1], value.v[1] }; }
inline Tsimd_f32x3_t tfS32x3FSplatIndex2(Tsimd_f32x3_t value) { return { value.v[2], value.v[2], value.v[2] }; }

inline Tsimd_i32x3_t tfS32x3iSplat(int32_t value) { return { value, value, value }; }
inline Tsimd_f32x3_t tfS32x3FSplat(float value) { return { value, value, value }; }

inline Tsimd_i32x3_t tfS32x3iCmpEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x3_t tfS32x3iCmpNeq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x3_t tfS32x3iCmpGt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x3_t tfS32x3iCmpGtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x3_t tfS32x3iCmpLt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline Tsimd_i32x3_t tfS32x3iCmpLtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
}
inline bool tfS32x3FCmpAllEq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
    for (int i = 0; i < 3; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

inline bool tfS32x3iCmpAllEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
    for (int i = 0; i < 3; i++) {
        if (arg1.v[i] != arg2.v[i]) {
            return false;
        }
    }
    return true;
}

static inline bool tfSimdFloat32x3CmpAllLt(Tsimd_f32x3_t a, Tsimd_f32x3_t b) {
    for (int i = 0; i < 3; i++) {
        if (a.v[i] >= b.v[i]) {
            return false;
        }
    }
    return true;
}

static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex0ByValue(Tsimd_f32x3_t input, float value) {
    return {value, input.v[1], input.v[2]};
}
static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex1ByValue(Tsimd_f32x3_t input, float value){
    return {input.v[0], value, input.v[2]};
};
static inline Tsimd_f32x3_t tfSimd3x32FReplaceIndex2ByValue(Tsimd_f32x3_t input, float value){
    return {input.v[0], input.v[1], value};
};



