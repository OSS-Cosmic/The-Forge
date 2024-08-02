#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4.h"
#endif

//static inline TSimd32Fx4 tfSimd4fReplaceIndex0ByValue(TSimd32Fx4 input, float value) { return vsetq_lane_f32(value, input, 0); }
//static inline TSimd32Fx4 tfSimd4fReplaceIndex1ByValue(TSimd32Fx4 input, float value) { return vsetq_lane_f32(value, input, 1); }
//static inline TSimd32Fx4 tfSimd4fReplaceIndex2ByValue(TSimd32Fx4 input, float value) { return vsetq_lane_f32(value, input, 2); }
//static inline TSimd32Fx4 tfSimd4fReplaceIndex3ByValue(TSimd32Fx4 input, float value) { return vsetq_lane_f32(value, input, 3); }
//
//inline TSimd32Ix4   tfSimd4iSelect(TSimd32Ix4 arg0, TSimd32Ix4 arg1, TSimd32Ix4 mask) { return vbslq_s32(mask, arg1, arg1); }
//inline TSimd32Fx4 tfSimd4fSelect(TSimd32Fx4 arg0, TSimd32Fx4 arg1, TSimd32Fx4 mask) { return vbslq_f32(mask, arg1, arg1); }
//
//inline TSimd32Fx4 tfSimd4fZero() { return vmovq_n_f32(0.0f); }
//inline TSimd32Ix4   tfSimd4iZero() { return vmovq_n_s32(0); }
//
//inline TSimd32Ix4 tfSimd4iNot(TSimd32Ix4 value) { return vmvnq_s32(value); }
//inline TSimd32Ix4 tfSimd4iAnd(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vandq_s32(arg1, arg2); }
//inline TSimd32Ix4 tfSimd4iAndNot(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vandq_s32(vmvnq_s32(arg1), arg2); }
//inline TSimd32Ix4 tfSimd4iOr(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vorrq_s32(arg1, arg2); }
//inline TSimd32Ix4 tfSimd4iXor(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return veorq_s32(arg1, arg2); }
//
//inline TSimd32Fx4 tfSimd4fNot(TSimd32Fx4 value) { return vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(value))); }
//inline TSimd32Fx4 tfSimd4fAnd(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
//}
//inline TSimd32Fx4 tfSimd4fAndNot(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vreinterpretq_f32_s32(vandq_s32(vmvnq_s32(vreinterpretq_s32_f32(arg1)), vreinterpretq_s32_f32(arg2)));
//}
//inline TSimd32Fx4 tfSimd4fOr(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
//}
//inline TSimd32Fx4 tfSimd4fXor(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
//}
//
//inline TSimd32Fx4 tfSimd4fFloor(TSimd32Fx4 value) { return vrndmq_f32(value); }
//inline TSimd32Fx4 tfSimd4fCeil(TSimd32Fx4 value) { return vrndpq_f32(value); }
//inline TSimd32Fx4 tfSimd4fRound(TSimd32Fx4 value) { return vrndnq_f32(value); }
//inline TSimd32Fx4 tfSimd4fTruncate(TSimd32Fx4 value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
//inline TSimd32Fx4 tfSimd4fMin(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vminq_f32(arg1, arg2); }
//inline TSimd32Fx4 tfSimd4fMax(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vmaxq_f32(arg1, arg2); }
//inline TSimd32Fx4 tfSimd4fClamp(TSimd32Fx4 value, TSimd32Fx4 min, TSimd32Fx4 max) {
//    return tfSimd4fMax(min, tfSimd4fMin(value, max));
//}
//
//inline TSimd32Ix4 tfSimd4fToSimd4i(TSimd32Fx4 value) { return vreinterpretq_f32_s32(value); }
//
//inline TSimd32Fx4 tfSimd4iToSimd4f(TSimd32Ix4 value) { return vreinterpretq_s32_f32(value); }
//
//inline float tfSimd4fSelectIndex0(TSimd32Fx4 value) { return vgetq_lane_f32(value, 0); }
//inline float tfSimd4fSelectIndex1(TSimd32Fx4 value) { return vgetq_lane_f32(value, 1); }
//inline float tfSimd4fSelectIndex2(TSimd32Fx4 value) { return vgetq_lane_f32(value, 2); }
//inline float tfSimd4fSelectIndex3(TSimd32Fx4 value) { return vgetq_lane_f32(value, 3); }
//
//inline TSimd32Fx4 tfSimd4fAdd(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vaddq_f32(arg1, arg2); }
//inline TSimd32Fx4 tfSimd4fSub(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vsubq_f32(arg1, arg2); }
//inline TSimd32Fx4 tfSimd4fMul(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vmulq_f32(arg1, arg2); }
//inline TSimd32Fx4 tfSimd4fMadd(TSimd32Fx4 mul1, TSimd32Fx4 mul2, TSimd32Fx4 add) { return vmlaq_f32(add, mul1, mul2); }
//
//inline TSimd32Fx4 tfSimd4fDiv(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vdivq_f32(arg1, arg2); }
//
//inline TSimd32Fx4 tfSimd4fAbs(TSimd32Fx4 value) { return vabsq_f32(value); }
//inline TSimd32Fx4 tfSimdFloat4x32Load(float x, float y, float z, float w) {
//    const float values[4] = { x, y, z, w };
//    return vld1q_f32(values);
//}
//
//inline TSimd32Ix4 tfSimdInt4x32Load(int32_t x, int32_t y, int32_t z, int32_t w) {
//    const int32_t values[4] = { x, y, z, w };
//    return vld1q_s32(values);
//}
//
//inline Tsimd_f32x2_t tfSimd4fToSimd2f(TSimd32Fx4 value) { return vget_low_f32(value); }
//
//inline TSimd32Fx3 tfSimd4fToSimd3f(TSimd32Fx4 value) { return value; }
//
//inline TSimd32Fx4 tfSimd4fSplatIndex0(TSimd32Fx4 value) { return vdupq_laneq_f32(value, 0); }
//
//inline TSimd32Fx4 tfSimd4fSplatIndex1(TSimd32Fx4 value) { return vdupq_laneq_f32(value, 1); }
//
//inline TSimd32Fx4 tfSimd4fSplatIndex2(TSimd32Fx4 value) { return vdupq_laneq_f32(value, 2); }
//
//inline TSimd32Fx4 tfSimd4fSplatIndex3(TSimd32Fx4 value) { return vdupq_laneq_f32(value, 3); }
//
//inline TSimd32Ix4 tfSimd4iSplat(int32_t value) { return vdupq_n_s32(value); }
//
//inline TSimd32Fx4 tfSimd4fSplat(float value) { return vdupq_n_f32(value); }
//
//inline TSimd32Fx4 tfSimd4fCmpEq(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vreinterpretq_f32_s32(vceqq_f32(arg1, arg2)); }
//inline TSimd32Fx4 tfSimd4fCmpNeq(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vreinterpretq_f32_s32(vmvnq_s32(vceqq_f32(arg1, arg2)));
//}
//inline TSimd32Fx4 tfSimd4fCmpGt(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vreinterpretq_f32_s32(vcgtq_f32(arg1, arg2)); }
//inline TSimd32Fx4 tfSimd4fCmpGtEq(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vreinterpretq_f32_s32(vcgeq_f32(arg1, arg2)); }
//inline TSimd32Fx4 tfSimd4fCmpLt(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vreinterpretq_f32_s32(vcltq_f32(arg1, arg2)); }
//inline TSimd32Fx4 tfSimd4fCmpLtEq(TSimd32Fx4 arg1, TSimd32Fx4 arg2) { return vreinterpretq_f32_s32(vcleq_f32(arg1, arg2)); }
//
//inline TSimd32Ix4 tfSimd4iCmpEq(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vceqq_s32(arg1, arg2); }
//inline TSimd32Ix4 tfSimd4iCmpNeq(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vmvnq_s32(vceqq_s32(arg1, arg2)); }
//inline TSimd32Ix4 tfSimd4iCmpGt(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vcgtq_s32(arg1, arg2); }
//inline TSimd32Ix4 tfSimd4iCmpGtEq(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vcgeq_s32(arg1, arg2); }
//inline TSimd32Ix4 tfSimd4iCmpLt(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vcltq_s32(arg1, arg2); }
//inline TSimd32Ix4 tfSimd4iCmpLtEq(TSimd32Ix4 arg1, TSimd32Ix4 arg2) { return vcleq_s32(arg1, arg2); }
//
//inline bool tfSimd4fCmpAllLt(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vminv_u32(vcltq_f32(arg1, arg2)) != 0;
//}
//
//inline bool tfSimd4fCmpAllGt(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vminv_u32(vcgtq_f32(arg1, arg2)) != 0;
//}
//
//inline bool tfSimd4fCmpAllEq(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    return vminv_u32(vceqq_f32(arg1, arg2)) != 0;
//}
//
//inline bool tfSimd4iCmpAllEq(TSimd32Ix4 arg1, TSimd32Ix4 arg2) {
//    return vminv_u32(vceqq_s32(arg1, arg2)) != 0;
//}
