#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON
#include "Forge/TF_Config.h"
#include "../TF_Simd32x3.h"
#endif

//inline Tsimd_i32x3_t   tfS32x3iSelect(Tsimd_i32x3_t arg0, Tsimd_i32x3_t arg1, Tsimd_i32x3_t mask) { return vbslq_s32(mask, arg0, arg1); }
//inline Tsimd_f32x3_t tfS32x3FSelect(Tsimd_f32x3_t arg0, Tsimd_f32x3_t arg1, Tsimd_f32x3_t mask) { return vbslq_f32(mask, arg1, arg1); }
//
//inline Tsimd_f32x3_t tfS32x3FZero() { return vmovq_n_f32(0.0f); }
//inline Tsimd_i32x3_t   tfS32x3iZero() { return vmovq_n_s32(0); }
//
//inline Tsimd_i32x3_t tfS32x3iNot(Tsimd_i32x3_t value) { return vmvnq_s32(value); }
//inline Tsimd_i32x3_t tfS32x3iAnd(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vandq_s32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iAndNot(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vandq_s32(vmvnq_s32(arg1), arg2); }
//inline Tsimd_i32x3_t tfS32x3iOr(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vorrq_s32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iXor(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return veorq_s32(arg1, arg2); }
//
//inline Tsimd_f32x3_t tfS32x3FNot(Tsimd_f32x3_t value) { return vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(value))); }
//inline Tsimd_f32x3_t tfS32x3FAnd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
//    return vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
//}
//inline Tsimd_f32x3_t tfS32x3FAndNot(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
//    return vreinterpretq_f32_s32(vandq_s32(vmvnq_s32(vreinterpretq_s32_f32(arg1)), vreinterpretq_s32_f32(arg2)));
//}
//inline Tsimd_f32x3_t tfS32x3FOr(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
//    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
//}
//inline Tsimd_f32x3_t tfS32x3FXor(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
//    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
//}
//
//inline Tsimd_f32x3_t tfS32x3FFloor(Tsimd_f32x3_t value) { return vrndmq_f32(value); }
//inline Tsimd_f32x3_t tfS32x3FCeil(Tsimd_f32x3_t value) { return vrndpq_f32(value); }
//inline Tsimd_f32x3_t tfS32x3FRound(Tsimd_f32x3_t value) { return vrndnq_f32(value); }
//inline Tsimd_f32x3_t tfS32x3FTruncate(Tsimd_f32x3_t value) { return tfS32x3iToSimd3f(tfS32x3FToSimd3i(value)); }
//inline Tsimd_f32x3_t tfS32x3FMin(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return vminq_f32(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FMax(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return vmaxq_f32(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FClamp(Tsimd_f32x3_t value, Tsimd_f32x3_t min, Tsimd_f32x3_t max) {
//    return tfS32x3FMax(min, tfS32x3FMin(value, max));
//}
//
//inline Tsimd_i32x3_t tfS32x3FToSimd3i(Tsimd_f32x3_t value) { return vreinterpretq_f32_s32(value); }
//
//inline Tsimd_f32x3_t tfS32x3iToSimd3f(Tsimd_i32x3_t value) { return vreinterpretq_s32_f32(value); }
//
//inline float tfS32x3FSelectIndex0(Tsimd_f32x3_t value) { return vgetq_lane_f32(value, 0); }
//
//inline float tfS32x3FSelectIndex1(Tsimd_f32x3_t value) { return vgetq_lane_f32(value, 1); }
//
//inline float tfS32x3FSelectIndex2(Tsimd_f32x3_t value) { return vgetq_lane_f32(value, 2); }
//
//inline Tsimd_f32x3_t tfS32x3FAdd(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return vaddq_f32(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FSub(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return vsubq_f32(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FMul(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return vmulq_f32(arg1, arg2); }
//inline Tsimd_f32x3_t tfS32x3FMadd(Tsimd_f32x3_t mul1, Tsimd_f32x3_t mul2, Tsimd_f32x3_t add) { return vmlaq_f32(add, mul1, mul2); }
//inline Tsimd_f32x3_t tfS32x3FDiv(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) { return vdivq_f32(arg1, arg2); }
//
//inline Tsimd_f32x3_t tfS32x3FAbs(Tsimd_f32x3_t value) { return vabsq_f32(value); }
//
//inline Tsimd_f32x3_t tfSimdFloat3Load(float x, float y, float z) {
//    const float values[4] = { x, y, z, 0.0f };
//    return vld1q_f32(values);
//}
//
//inline Tsimd_i32x3_t tfSimdInt3Load(int32_t x, int32_t y, int32_t z) {
//    const int32_t values[4] = { x, y, z, 0 };
//    return vld1q_s32(values);
//}
//
//inline Tsimd_f32x2_t tfS32x3FToSimd2f(Tsimd_f32x3_t value) { return vget_low_f32(value); }
//
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat0(Tsimd_f32x3_t value) { return vdupq_laneq_f32(value, 0); }
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat1(Tsimd_f32x3_t value) { return vdupq_laneq_f32(value, 1); }
//static inline Tsimd_f32x4_t tfS32x3FTo32x4FSplat2(Tsimd_f32x3_t value) { return vdupq_laneq_f32(value, 2); }
//
//inline Tsimd_f32x3_t tfS32x3FSplatIndex0(Tsimd_f32x3_t value) { return vdupq_laneq_f32(value, 0); }
//
//inline Tsimd_f32x3_t tfS32x3FSplatIndex1(Tsimd_f32x3_t value) { return vdupq_laneq_f32(value, 1); }
//
//inline Tsimd_f32x3_t tfS32x3FSplatIndex2(Tsimd_f32x3_t value) { return vdupq_laneq_f32(value, 2); }
//
//inline Tsimd_i32x3_t tfS32x3iSplat(int32_t value) { return vdupq_n_s32(value); }
//
//inline Tsimd_f32x3_t tfS32x3FSplat(float value) { return vdupq_n_f32(value); }
//
//inline Tsimd_i32x3_t tfS32x3iCmpEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vceqq_s32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iCmpNeq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vmvnq_s32(vceqq_s32(arg1, arg2)); }
//inline Tsimd_i32x3_t tfS32x3iCmpGt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vcgtq_s32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iCmpGtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vcgeq_s32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iCmpLt(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vcltq_s32(arg1, arg2); }
//inline Tsimd_i32x3_t tfS32x3iCmpLtEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) { return vcleq_s32(arg1, arg2); }
//inline bool         tfS32x3FCmpAllEq(Tsimd_f32x3_t arg1, Tsimd_f32x3_t arg2) {
//   // for (int i = 0; i < 3; i++) {
//   //     if (arg1.v[i] != arg2.v[i]) {
//   //         return false;
//   //     }
//   // }
//    return true;
//}
//
//inline bool tfS32x3iCmpAllEq(Tsimd_i32x3_t arg1, Tsimd_i32x3_t arg2) {
//   // for (int i = 0; i < 3; i++) {
//   //     if (arg1.v[i] != arg2.v[i]) {
//   //         return false;
//   //     }
//   // }
//    return true;
//}
