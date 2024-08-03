#if defined(__CLANGD__)
#define TF_FEATURE_CPU_SCALAR 1  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4.h"
#endif

static inline Tsimd_f32x4_t tfSimdReplace_f32_f32x4(Tsimd_f32x4_t a, int index, float b) {
    a.v[index] = b;
    return a;
}
static inline Tsimd_f32x4_t tfSimdReplace_f32x4_f32x4( Tsimd_f32x4_t a,int index, Tsimd_f32x4_t b) {
    ASSERT(index < 4);
    a.v[index] = b.v[index];
    return a;
}

static inline Tsimd_f32x4_t tfSimdRcp_f32x4(Tsimd_f32x4_t a) { return  {
    1.0f/a.v[0],
    1.0f/a.v[1],
    1.0f/a.v[2],
    1.0f/a.v[3]
}; }

static inline float tfSimdMaxElem_f32x4_f32(Tsimd_f32x4_t a) { return fmaxf(fmaxf(a.v[0], a.v[1]), fmaxf(a.v[2], a.v[3])); }
static inline float tfSimdMinElem_f32x4_f32(Tsimd_f32x4_t a) { return fminf(fminf(a.v[0], a.v[1]), fminf(a.v[2], a.v[3])); }

static inline Tsimd_f32x4_t tfSimdMaxElem_f32x4(Tsimd_f32x4_t a) {
    const float result = tfSimdMaxElem_f32x4_f32(a);
    return { result, result, result, result };
}
static inline Tsimd_f32x4_t tfSimdMaxPerElem_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) {
    return { fmaxf(a.v[0], b.v[0]), fmaxf(a.v[1], b.v[1]), fmaxf(a.v[2], b.v[2]), fmaxf(a.v[3], b.v[3]) };
}
static inline Tsimd_f32x4_t tfSimdMinElem_f32x4(Tsimd_f32x4_t a) {
    const float result = tfSimdMinElem_f32x4_f32(a);
    return { result, result, result, result };
}
static inline Tsimd_f32x4_t tfSimdMinPerElem_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) {
    return { fminf(a.v[0], b.v[0]), fminf(a.v[1], b.v[1]), fminf(a.v[2], b.v[2]), fminf(a.v[3], b.v[3]) };
}

static inline Tsimd_f32x4_t tfSimdSqrt_f32x4(Tsimd_f32x4_t a) { return { sqrtf(a.v[0]), sqrtf(a.v[1]), sqrtf(a.v[2]), sqrtf(a.v[3]) }; }

// Tsimd_f32x4_t
static inline Tsimd_f32x4_t tfSimdZero_f32x4() { return {0,0,0,0}; }
static inline Tsimd_f32x4_t tfSimdLoad_f32x4(float x, float y, float z, float w) { return { x, y, z, w }; }

static inline Tsimd_f32x4_t tfSimdSplat_f32_f32x4(float value) { return { value, value, value, value }; }
static inline Tsimd_f32x4_t tfSimdSplat_f32x4_f32x4(Tsimd_f32x4_t value, int index) { ASSERT(index< 4); return { value.v[index], value.v[index], value.v[index], value.v[index] }; }

static inline Tsimd_f32x4_t tfSimdDot_f32x4(Tsimd_f32x4_t a,Tsimd_f32x4_t b) {
    const float result = tfSimdDot_f32x4_f32(a, b);
    return { result, result, result, result };
}
static inline Tsimd_f32x4_t tfSimdLength_f32x4(Tsimd_f32x4_t a) {
    const float result = tfSimdLength_f32x4_f32(a);
    return { result, result, result, result };
}

static inline float tfSimdDot_f32x4_f32(Tsimd_f32x4_t a, Tsimd_f32x4_t b) {
    return (a.v[0] * b.v[0]) + (a.v[1] * b.v[1]) + (a.v[2] * b.v[2]) + (a.v[3] * b.v[3]);
}

static inline float tfSimdLength_f32x4_f32(Tsimd_f32x4_t a) {
    return sqrtf((a.v[0] * a.v[0]) + (a.v[1] * a.v[1]) + (a.v[2] * a.v[2]) + (a.v[3] * a.v[3]));
}


static inline float tfSimdGet_f32x4(Tsimd_f32x4_t value, int index) {ASSERT(index < 4); return value.v[index];}

static inline Tsimd_f32x4_t tfSimdAdd_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return {
    a.v[0] + b.v[0],
    a.v[1] + b.v[1],
    a.v[2] + b.v[2],
    a.v[3] + b.v[3]
}; }

static inline Tsimd_f32x4_t tfSimdSub_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) { return {
    a.v[0] - b.v[0],
    a.v[1] - b.v[1],
    a.v[2] - b.v[2],
    a.v[3] - b.v[3]
};}

static inline Tsimd_f32x4_t tfSimdMul_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) {
    return { a.v[0] * b.v[0], a.v[1] * b.v[1], a.v[2] * b.v[2], a.v[3] * b.v[3] };
}
static inline Tsimd_f32x4_t tfSimdDiv_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b) {
    return { a.v[0] / b.v[0], a.v[1] / b.v[1], a.v[2] / b.v[2], a.v[3] / b.v[3] };
}
static inline Tsimd_f32x4_t tfSimdAbs_f32x4(Tsimd_f32x4_t a) { return { fabsf(a.v[0]), fabsf(a.v[1]), fabsf(a.v[2]), fabsf(a.v[3]) }; }
static inline Tsimd_f32x4_t tfSimdMadd_f32x4(Tsimd_f32x4_t a, Tsimd_f32x4_t b, Tsimd_f32x4_t c) {
    return { (a.v[0] * b.v[0]) + c.v[0], (a.v[1] * b.v[1]) + c.v[1], (a.v[2] * b.v[2]) + c.v[2], (a.v[3] * b.v[3]) + +c.v[3] };
}

static inline Tsimd_f32x4_t tfSimdNot_f32x4(Tsimd_f32x4_t value) {
    return { 
        (float)(~((int32_t)value.v[0])), 
        (float)(~((int32_t)value.v[1])), 
        (float)(~((int32_t)value.v[2])), 
        (float)(~((int32_t)value.v[3])) };
}
static inline Tsimd_f32x4_t tfSimdAnd_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return { 
        (float)(((int32_t)arg1.v[0]) & ((int32_t)arg1.v[0])), 
        (float)(((int32_t)arg1.v[1]) & ((int32_t)arg1.v[1])), 
        (float)(((int32_t)arg1.v[2]) & ((int32_t)arg1.v[2])), 
        (float)(((int32_t)arg1.v[3]) & ((int32_t)arg1.v[3])) };
}
static inline Tsimd_f32x4_t tfSimdAndNot_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return { 
        (float)(~((int32_t)arg1.v[0]) & ((int32_t)arg1.v[0])), 
        (float)(~((int32_t)arg1.v[1]) & ((int32_t)arg1.v[1])), 
        (float)(~((int32_t)arg1.v[2]) & ((int32_t)arg1.v[2])), 
        (float)(~((int32_t)arg1.v[3]) & ((int32_t)arg1.v[3])) };

}
static inline Tsimd_f32x4_t tfSimdOr_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return { 
        (float)(((int32_t)arg1.v[0]) | ((int32_t)arg1.v[0])), 
        (float)(((int32_t)arg1.v[1]) | ((int32_t)arg1.v[1])), 
        (float)(((int32_t)arg1.v[2]) | ((int32_t)arg1.v[2])), 
        (float)(((int32_t)arg1.v[3]) | ((int32_t)arg1.v[3])) };
}
static inline Tsimd_f32x4_t tfSimdXor_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return { 
        (float)(((int32_t)arg1.v[0]) ^ ((int32_t)arg1.v[0])), 
        (float)(((int32_t)arg1.v[1]) ^ ((int32_t)arg1.v[1])), 
        (float)(((int32_t)arg1.v[2]) ^ ((int32_t)arg1.v[2])), 
        (float)(((int32_t)arg1.v[3]) ^ ((int32_t)arg1.v[3])) };
}

static inline Tsimd_f32x4_t tfSimdCmpEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return tfSimd_i32x4_To_f32x4({ (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[3] == arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 });
}
static inline Tsimd_f32x4_t tfSimdCmpNeq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return tfSimd_i32x4_To_f32x4({ (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[3] != arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 });
}
static inline Tsimd_f32x4_t tfSimdCmpGt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return tfSimd_i32x4_To_f32x4({ 
             (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[3] > arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 });
}
static inline Tsimd_f32x4_t tfSimdCmpGtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return tfSimd_i32x4_To_f32x4({ (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
             (arg1.v[3] >= arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 });
}
static inline Tsimd_f32x4_t tfSimdCmpLt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return tfSimd_i32x4_To_f32x4({ 
        (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
        (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
        (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
        (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 });
}
static inline Tsimd_f32x4_t tfSimdCmpLtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return tfSimd_i32x4_To_f32x4({ 
        (arg1.v[0] <= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
        (arg1.v[1] <= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
        (arg1.v[2] <= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, 
        (arg1.v[3] <= arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 });
}

static inline bool tfSimdCmpAllEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2){
    return arg1.v[0] == arg2.v[0] && arg1.v[1] == arg2.v[1] && arg1.v[2] == arg2.v[2] && arg1.v[3] == arg2.v[3];
}
static inline bool tfSimdCmpAllNeq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2){
    return arg1.v[0] != arg2.v[0] && arg1.v[1] != arg2.v[1] && arg1.v[2] != arg2.v[2] && arg1.v[3] != arg2.v[3];
}
static inline bool tfSimdCmpAllGt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return arg1.v[0] > arg2.v[0] && arg1.v[1] > arg2.v[1] && arg1.v[2] > arg2.v[2] && arg1.v[3] > arg2.v[3];
}
static inline bool tfSimdCmpAllGtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2){
    return arg1.v[0] >= arg2.v[0] && arg1.v[1] >= arg2.v[1] && arg1.v[2] >= arg2.v[2] && arg1.v[3] >= arg2.v[3];
}
static inline bool tfSimdCmpAllLt_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return arg1.v[0] < arg2.v[0] && arg1.v[1] < arg2.v[1] && arg1.v[2] < arg2.v[2] && arg1.v[3] < arg2.v[3];
}
static inline bool tfSimdCmpAllLtEq_f32x4(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2){
    return arg1.v[0] <= arg2.v[0] && arg1.v[1] <= arg2.v[1] && arg1.v[2] <= arg2.v[2] && arg1.v[3] <= arg2.v[3];
}

// Tsimd_i32x4_t
static inline Tsimd_i32x4_t tfSimdLoad_i32x4(int32_t x, int32_t y, int32_t z, int32_t w) { return { x, y, z, w }; }

static inline Tsimd_i32x4_t tfSimdSplat_i32_i32x4(int32_t value) { return { value, value, value, value }; }
static inline Tsimd_i32x4_t tfSimdSplat_i32x4_i32x4(Tsimd_i32x4_t value, int index){ ASSERT(index< 4); return { value.v[index], value.v[index], value.v[index], value.v[index] }; } 

static inline int32_t tfSimdGet_i32x4(Tsimd_i32x4_t value, int index) {
    ASSERT(index < 4);
    return value.v[index];
}

static inline Tsimd_i32x4_t tfSimdAdd_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b) {
    return { a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2], a.v[3] + b.v[3] };
}
static inline Tsimd_i32x4_t tfSimdMul_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b) {
    return { a.v[0] * b.v[0], a.v[1] * b.v[1], a.v[2] * b.v[2], a.v[3] * b.v[3] };
}
static inline Tsimd_i32x4_t tfSimdAbs_i32x4(Tsimd_i32x4_t a) {
    return {
        abs(a.v[0]),
        abs(a.v[1]),
        abs(a.v[2]),
        abs(a.v[3]),
    };
}
static inline Tsimd_i32x4_t tfSimdMadd_i32x4(Tsimd_i32x4_t a, Tsimd_i32x4_t b, Tsimd_i32x4_t c) {
    return { (a.v[0] * b.v[0]) + c.v[0], (a.v[1] * b.v[1]) + c.v[1], (a.v[2] * b.v[2]) + c.v[2], (a.v[3] * b.v[3]) + +c.v[3] };
}
static inline Tsimd_i32x4_t tfSimdNot_i32x4(Tsimd_i32x4_t value) {
    return { ~(int32_t)value.v[0], ~(int32_t)value.v[1], ~(int32_t)value.v[2], ~(int32_t)value.v[3] };
}
static inline Tsimd_i32x4_t tfSimdAnd_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2], arg1.v[3] & arg2.v[3] };
}
static inline Tsimd_i32x4_t tfSimdAndNot_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2], ~arg1.v[3] & arg2.v[3] };
}
static inline Tsimd_i32x4_t tfSimdOr_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2], arg1.v[3] | arg2.v[3] };
}
static inline Tsimd_i32x4_t tfSimdXor_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2], arg1.v[3] ^ arg2.v[3] };
}

static inline Tsimd_i32x4_t tfSimdCmpEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] == arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 };
}
static inline Tsimd_i32x4_t tfSimdCmpNeq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] != arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 };
}
static inline Tsimd_i32x4_t tfSimdCmpGt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] > arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 };
}
static inline Tsimd_i32x4_t tfSimdCmpGtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] >= arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 };
}
static inline Tsimd_i32x4_t tfSimdCmpLt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 };
}
static inline Tsimd_i32x4_t tfSimdCmpLtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return { (arg1.v[0] <= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] <= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
             (arg1.v[2] <= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] <= arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 };
}

static inline bool tfSimdCmpAllEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return arg1.v[0] == arg2.v[0] && arg1.v[1] == arg2.v[1] && arg1.v[2] == arg2.v[2] && arg1.v[3] == arg2.v[3];
}
static inline bool tfSimdCmpAllNeq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return arg1.v[0] != arg2.v[0] && arg1.v[1] != arg2.v[1] && arg1.v[2] != arg2.v[2] && arg1.v[3] != arg2.v[3];
}
static inline bool tfSimdCmpAllGt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return arg1.v[0] > arg2.v[0] && arg1.v[1] > arg2.v[1] && arg1.v[2] > arg2.v[2] && arg1.v[3] > arg2.v[3];
}
static inline bool tfSimdCmpAllGtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return arg1.v[0] >= arg2.v[0] && arg1.v[1] >= arg2.v[1] && arg1.v[2] >= arg2.v[2] && arg1.v[3] >= arg2.v[3];
}
static inline bool tfSimdCmpAllLt_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return arg1.v[0] < arg2.v[0] && arg1.v[1] < arg2.v[1] && arg1.v[2] < arg2.v[2] && arg1.v[3] < arg2.v[3];
}
static inline bool tfSimdCmpAllLtEq_i32x4(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return arg1.v[0] <= arg2.v[0] && arg1.v[1] <= arg2.v[1] && arg1.v[2] <= arg2.v[2] && arg1.v[3] <= arg2.v[3];
}

static inline Tsimd_i32x4_t tfSimd_f32x4_To_i32x4(Tsimd_f32x4_t a) {
    union int_float {
        Tsimd_f32x4_t a; 
        Tsimd_i32x4_t b; 
    } conversion;
    conversion.a = a;
    COMPILE_ASSERT(sizeof(Tsimd_f32x4_t) == sizeof(Tsimd_i32x4_t));
    return conversion.b;
}
static inline Tsimd_f32x4_t tfSimd_i32x4_To_f32x4(Tsimd_i32x4_t a) {
    union int_float {
        Tsimd_f32x4_t a; 
        Tsimd_i32x4_t b; 
    } conversion;
    conversion.b = a;
    COMPILE_ASSERT(sizeof(Tsimd_f32x4_t) == sizeof(Tsimd_i32x4_t));
    return conversion.a;
}


//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex0ByValue(Tsimd_f32x4_t input, float value) {
//    return { value, input.v[1], input.v[2], input.v[3] };
//}
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex1ByValue(Tsimd_f32x4_t input, float value) {
//    return { input.v[0], value, input.v[2], input.v[3] };
//}
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex2ByValue(Tsimd_f32x4_t input, float value) {
//    return { input.v[0], input.v[1], value, input.v[3] };
//}
//static inline Tsimd_f32x4_t tfS32x4FReplaceIndex3ByValue(Tsimd_f32x4_t input, float value) {
//    return { input.v[0], input.v[1], input.v[2], value };
//}
//
//inline Tsimd_i32x4_t Tsimd_i32x4_tSelect(Tsimd_i32x4_t arg0, Tsimd_i32x4_t arg1, Tsimd_i32x4_t mask) {
//    return { (mask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (mask.v[1] == 0) ? arg0.v[1] : arg1.v[1], (mask.v[2] == 0) ? arg0.v[2] : arg1.v[2],
//             (mask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
//}
//inline Tsimd_f32x4_t tfS32x4FSelect(Tsimd_f32x4_t arg0, Tsimd_f32x4_t arg1, Tsimd_f32x4_t mask) {
//    Tsimd_i32x4_t intMask = tfS32x4FToS32x4I(mask);
//    return { (intMask.v[0] == 0) ? arg0.v[0] : arg1.v[0], (intMask.v[1] == 0) ? arg0.v[1] : arg1.v[1],
//             (intMask.v[2] == 0) ? arg0.v[2] : arg1.v[2], (intMask.v[3] == 0) ? arg0.v[3] : arg1.v[3] };
//}
//
//inline Tsimd_f32x4_t tfS32x4FZero() { return { 0, 0, 0, 0 }; }
//inline Tsimd_i32x4_t   Tsimd_i32x4_tZero() { return { 0, 0, 0, 0 }; }
//
//inline Tsimd_i32x4_t Tsimd_i32x4_tNot(Tsimd_i32x4_t value) { return { ~value.v[0], ~value.v[1], ~value.v[2], ~value.v[3] }; }
//inline Tsimd_i32x4_t Tsimd_i32x4_tAnd(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { arg1.v[0] & arg2.v[0], arg1.v[1] & arg2.v[1], arg1.v[2] & arg2.v[2], arg1.v[3] & arg2.v[3] };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tAndNot(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { ~arg1.v[0] & arg2.v[0], ~arg1.v[1] & arg2.v[1], ~arg1.v[2] & arg2.v[2], ~arg1.v[3] & arg2.v[3] };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tOr(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { arg1.v[0] | arg2.v[0], arg1.v[1] | arg2.v[1], arg1.v[2] | arg2.v[2], arg1.v[3] | arg2.v[3] };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tXor(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { arg1.v[0] ^ arg2.v[0], arg1.v[1] ^ arg2.v[1], arg1.v[2] ^ arg2.v[2], arg1.v[3] ^ arg2.v[3] };
//}
//
//inline Tsimd_f32x4_t tfS32x4FNot(Tsimd_f32x4_t value) {
//    Tsimd_i32x4_t result = { { ~((int32_t)value.v[0]), ~((int32_t)value.v[1]), ~((int32_t)value.v[2]), ~((int32_t)value.v[3]) } };
//    return Tsimd_i32x4_tToSimd4f(result);
//}
//inline Tsimd_f32x4_t tfS32x4FAnd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    Tsimd_i32x4_t result = { ((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
//                            ((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) };
//    return Tsimd_i32x4_tToSimd4f(result);
//}
//inline Tsimd_f32x4_t tfS32x4FAndNot(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    Tsimd_i32x4_t result = { { ~((int32_t)arg1.v[0]) & ((int32_t)arg2.v[0]), ~((int32_t)arg1.v[1]) & ((int32_t)arg2.v[1]),
//                              ~((int32_t)arg1.v[2]) & ((int32_t)arg2.v[2]), ~((int32_t)arg1.v[3]) & ((int32_t)arg2.v[3]) } };
//    return Tsimd_i32x4_tToSimd4f(result);
//}
//inline Tsimd_f32x4_t tfS32x4FOr(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    Tsimd_i32x4_t result = { { ((int32_t)arg1.v[0]) | ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) | ((int32_t)arg2.v[1]),
//                              ((int32_t)arg1.v[2]) | ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) | ((int32_t)arg2.v[3]) } };
//    return Tsimd_i32x4_tToSimd4f(result);
//}
//inline Tsimd_f32x4_t tfS32x4FXor(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    Tsimd_i32x4_t result = { { ((int32_t)arg1.v[0]) ^ ((int32_t)arg2.v[0]), ((int32_t)arg1.v[1]) ^ ((int32_t)arg2.v[1]),
//                              ((int32_t)arg1.v[2]) ^ ((int32_t)arg2.v[2]), ((int32_t)arg1.v[3]) ^ ((int32_t)arg2.v[3]) } };
//    return Tsimd_i32x4_tToSimd4f(result);
//}
//
//inline Tsimd_f32x4_t tfS32x4FFloor(Tsimd_f32x4_t value) {
//    return { { floorf(value.v[0]), floorf(value.v[1]), floorf(value.v[2]), floorf(value.v[3]) } };
//}
//inline Tsimd_f32x4_t tfS32x4FCeil(Tsimd_f32x4_t value) {
//    return { { ceilf(value.v[0]), ceilf(value.v[1]), ceilf(value.v[2]), ceilf(value.v[3]) } };
//}
//inline Tsimd_f32x4_t tfS32x4FRound(Tsimd_f32x4_t value) {
//    // While 'roundf' may seem the obvious choice here, it rounds halfway cases
//    // away from zero regardless of the current rounding mode, but 'rintf' uses
//    // the current rounding mode which is consistent with other implementations.
//    return { { rintf(value.v[0]), rintf(value.v[1]), rintf(value.v[2]), rintf(value.v[3]) } };
//}
//inline Tsimd_f32x4_t tfS32x4FTruncate(Tsimd_f32x4_t value) { return Tsimd_i32x4_tToSimd4f(tfS32x4FToS32x4I(value)); }
//inline Tsimd_f32x4_t tfS32x4FMin(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { fminf(arg1.v[0], arg2.v[0]), fminf(arg1.v[1], arg2.v[1]), fminf(arg1.v[2], arg2.v[2]), fminf(arg1.v[3], arg2.v[3]) } };
//}
//inline Tsimd_f32x4_t tfS32x4FMax(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { fmaxf(arg1.v[0], arg2.v[0]), fmaxf(arg1.v[1], arg2.v[1]), fmaxf(arg1.v[2], arg2.v[2]), fmaxf(arg1.v[3], arg2.v[3]) } };
//}
//inline Tsimd_f32x4_t tfS32x4FClamp(Tsimd_f32x4_t value, Tsimd_f32x4_t min, Tsimd_f32x4_t max) {
//    return tfS32x4FMax(min, tfS32x4FMin(value, max));
//}
//
//inline Tsimd_i32x4_t tfS32x4FToS32x4I(Tsimd_f32x4_t value) {
//    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2], (int32_t)value.v[3] };
//}
//
//inline Tsimd_f32x4_t Tsimd_i32x4_tToSimd4f(Tsimd_i32x4_t value) {
//    return { (float)value.v[0], (float)value.v[1], (float)value.v[2], (float)value.v[3] };
//}
//
//inline float tfS32x4FSelectIndex0(Tsimd_f32x4_t value) { return value.v[0]; }
//inline float tfS32x4FSelectIndex1(Tsimd_f32x4_t value) { return value.v[1]; }
//inline float tfS32x4FSelectIndex2(Tsimd_f32x4_t value) { return value.v[2]; }
//inline float tfS32x4FSelectIndex3(Tsimd_f32x4_t value) { return value.v[3]; }
//
//inline Tsimd_f32x4_t tfS32x4FAdd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return {
//        arg1.v[0] + arg2.v[0],
//        arg1.v[1] + arg2.v[1],
//        arg1.v[2] + arg2.v[2],
//        arg1.v[3] + arg2.v[3],
//    };
//}
//inline Tsimd_f32x4_t tfS32x4FSub(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return {
//        arg1.v[0] - arg2.v[0],
//        arg1.v[1] - arg2.v[1],
//        arg1.v[2] - arg2.v[2],
//        arg1.v[3] - arg2.v[3],
//    };
//}
//inline Tsimd_f32x4_t tfS32x4FMul(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return {
//        arg1.v[0] * arg2.v[0],
//        arg1.v[1] * arg2.v[1],
//        arg1.v[2] * arg2.v[2],
//        arg1.v[3] * arg2.v[3],
//    };
//}
//inline Tsimd_f32x4_t tfS32x4FMadd(Tsimd_f32x4_t mul1, Tsimd_f32x4_t mul2, Tsimd_f32x4_t add) {
//    return tfS32x4FAdd(tfS32x4FMul(mul1, mul2), add);
//}
//
//inline Tsimd_f32x4_t tfS32x4FDiv(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return {
//        arg1.v[0] / arg2.v[0],
//        arg1.v[1] / arg2.v[1],
//        arg1.v[2] / arg2.v[2],
//        arg1.v[3] / arg2.v[3],
//    };
//}
//
//inline Tsimd_f32x4_t tfS32x4FAbs(Tsimd_f32x4_t value) {
//    return {
//        abs(value.v[0]),
//        abs(value.v[1]),
//        abs(value.v[2]),
//        abs(value.v[3]),
//    };
//}
//inline Tsimd_f32x4_t tfS32x4FLoad(float x, float y, float z, float w) { return { x, y, z, w }; }
//inline Tsimd_i32x4_t tfSimdInt4x32Load(int32_t x, int32_t y, int32_t z, int32_t w) { return { x, y, z, w }; }
//
//inline Tsimd_f32x2_t tfS32x4FToS32x2F(Tsimd_f32x4_t value) { return { value.v[0], value.v[1] }; }
//inline Tsimd_f32x3_t tfS32x4FToS32x3F(Tsimd_f32x4_t value) { return { value.v[0], value.v[1], value.v[2] }; }
//
//inline Tsimd_f32x4_t tfS32x4FSplatIndex0(Tsimd_f32x4_t value) { return { value.v[0], value.v[0], value.v[0], value.v[0] }; }
//inline Tsimd_f32x4_t tfS32x4FSplatIndex1(Tsimd_f32x4_t value) { return { value.v[1], value.v[1], value.v[1], value.v[1] }; }
//inline Tsimd_f32x4_t tfS32x4FSplatIndex2(Tsimd_f32x4_t value) { return { value.v[2], value.v[2], value.v[2], value.v[2] }; }
//inline Tsimd_f32x4_t tfS32x4FSplatIndex3(Tsimd_f32x4_t value) { return { value.v[3], value.v[3], value.v[3], value.v[3] }; }
//
//inline Tsimd_i32x4_t Tsimd_i32x4_tSplat(int32_t value) { return { value, value, value, value }; }
//inline Tsimd_f32x4_t tfS32x4FSplat(float value) { return { value, value, value, value }; }
//
//inline Tsimd_f32x4_t tfS32x4FCmpEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { (arg1.v[0] == arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] == arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] == arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_f32x4_t tfS32x4FCmpNeq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { (arg1.v[0] != arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] != arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] != arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_f32x4_t tfS32x4FCmpGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { (arg1.v[0] > arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] > arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] > arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_f32x4_t tfS32x4FCmpGtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { (arg1.v[0] >= arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] >= arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] >= arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_f32x4_t tfS32x4FCmpLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { (arg1.v[0] < arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] < arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] < arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_f32x4_t tfS32x4FCmpLtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    return { { (arg1.v[0] <= arg2.v[0]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[1] <= arg2.v[1]) ? (float)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] <= arg2.v[2]) ? (float)0xFFFFFFFF : 0x00000000, (arg1.v[3] <= arg2.v[3]) ? (float)0xFFFFFFFF : 0x00000000 } };
//}
//
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { { (arg1.v[0] == arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] == arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] == arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] == arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpNeq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { { (arg1.v[0] != arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] != arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] != arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] != arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpGt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { { (arg1.v[0] > arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] > arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] > arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] > arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpGtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { { (arg1.v[0] >= arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] >= arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] >= arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] >= arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpLt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
//}
//inline Tsimd_i32x4_t Tsimd_i32x4_tCmpLtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    return { { (arg1.v[0] < arg2.v[0]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[1] < arg2.v[1]) ? (int32_t)0xFFFFFFFF : 0x00000000,
//               (arg1.v[2] < arg2.v[2]) ? (int32_t)0xFFFFFFFF : 0x00000000, (arg1.v[3] < arg2.v[3]) ? (int32_t)0xFFFFFFFF : 0x00000000 } };
//}
//
//inline bool tfS32x4FCmpAllLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    for (int i = 0; i < 4; i++) {
//        if (arg1.v[i] >= arg2.v[i]) {
//            return false;
//        }
//    }
//    return true;
//}
//
//inline bool tfS32x4FCmpAllGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    for (int i = 0; i < 4; i++) {
//        if (arg1.v[i] <= arg2.v[i]) {
//            return false;
//        }
//    }
//    return true;
//}
//
//inline bool tfS32x4FCmpAllEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
//    for (int i = 0; i < 4; i++) {
//        if (arg1.v[i] != arg2.v[i]) {
//            return false;
//        }
//    }
//    return true;
//}
//
//inline bool Tsimd_i32x4_tCmpAllEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
//    for (int i = 0; i < 4; i++) {
//        if (arg1.v[i] != arg2.v[i]) {
//            return false;
//        }
//    }
//    return true;
//}
