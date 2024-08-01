#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON
#include "Forge/TF_Config.h"
#include "../TF_Simd32x3.h"
#endif

inline TSimdInt32x3   tfSimd3iSelect(TSimdInt32x3 arg0, TSimdInt32x3 arg1, TSimdInt32x3 mask) { return vbslq_s32(mask, arg0, arg1); }
inline TSimdFloat32x3 tfSimd3fSelect(TSimdFloat32x3 arg0, TSimdFloat32x3 arg1, TSimdFloat32x3 mask) { return vbslq_f32(mask, arg1, arg1); }

inline TSimdFloat32x3 tfSimd3fZero() { return vmovq_n_f32(0.0f); }
inline TSimdInt32x3   tfSimd3iZero() { return vmovq_n_s32(0); }

inline TSimdInt32x3 tfSimd3iNot(TSimdInt32x3 value) { return vmvnq_s32(value); }
inline TSimdInt32x3 tfSimd3iAnd(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vandq_s32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iAndNot(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vandq_s32(vmvnq_s32(arg1), arg2); }
inline TSimdInt32x3 tfSimd3iOr(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vorrq_s32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iXor(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return veorq_s32(arg1, arg2); }

inline TSimdFloat32x3 tfSimd3fNot(TSimdFloat32x3 value) { return vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(value))); }
inline TSimdFloat32x3 tfSimd3fAnd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}
inline TSimdFloat32x3 tfSimd3fAndNot(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return vreinterpretq_f32_s32(vandq_s32(vmvnq_s32(vreinterpretq_s32_f32(arg1)), vreinterpretq_s32_f32(arg2)));
}
inline TSimdFloat32x3 tfSimd3fOr(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}
inline TSimdFloat32x3 tfSimd3fXor(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}

inline TSimdFloat32x3 tfSimd3fFloor(TSimdFloat32x3 value) { return vrndmq_f32(value); }
inline TSimdFloat32x3 tfSimd3fCeil(TSimdFloat32x3 value) { return vrndpq_f32(value); }
inline TSimdFloat32x3 tfSimd3fRound(TSimdFloat32x3 value) { return vrndnq_f32(value); }
inline TSimdFloat32x3 tfSimd3fTruncate(TSimdFloat32x3 value) { return tfSimd3iToSimd3f(tfSimd3fToSimd3i(value)); }
inline TSimdFloat32x3 tfSimd3fMin(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return vminq_f32(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fMax(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return vmaxq_f32(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fClamp(TSimdFloat32x3 value, TSimdFloat32x3 min, TSimdFloat32x3 max) {
    return tfSimd3fMax(min, tfSimd3fMin(value, max));
}

inline TSimdInt32x3 tfSimd3fToSimd3i(TSimdFloat32x3 value) { return vreinterpretq_f32_s32(value); }

inline TSimdFloat32x3 tfSimd3iToSimd3f(TSimdInt32x3 value) { return vreinterpretq_s32_f32(value); }

inline float tfSimd3fSelectIndex0(TSimdFloat32x3 value) { return vgetq_lane_f32(value, 0); }

inline float tfSimd3fSelectIndex1(TSimdFloat32x3 value) { return vgetq_lane_f32(value, 1); }

inline float tfSimd3fSelectIndex2(TSimdFloat32x3 value) { return vgetq_lane_f32(value, 2); }

inline TSimdFloat32x3 tfSimd3fAdd(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return vaddq_f32(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fSub(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return vsubq_f32(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fMul(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return vmulq_f32(arg1, arg2); }
inline TSimdFloat32x3 tfSimd3fMadd(TSimdFloat32x3 mul1, TSimdFloat32x3 mul2, TSimdFloat32x3 add) { return vmlaq_f32(add, mul1, mul2); }
inline TSimdFloat32x3 tfSimd3fDiv(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) { return vdivq_f32(arg1, arg2); }

inline TSimdFloat32x3 tfSimd3fAbs(TSimdFloat32x3 value) { return vabsq_f32(value); }

inline TSimdFloat32x3 tfSimdFloat3Load(float x, float y, float z) {
    const float values[4] = { x, y, z, 0.0f };
    return vld1q_f32(values);
}

inline TSimdInt32x3 tfSimdInt3Load(int32_t x, int32_t y, int32_t z) {
    const int32_t values[4] = { x, y, z, 0 };
    return vld1q_s32(values);
}

inline TSimdFloat32x2 tfSimd3fToSimd2f(TSimdFloat32x3 value) { return vget_low_f32(value); }

static inline TSimdFloat32x4 tfSimdFloat3To4Splat0(TSimdFloat32x3 value) { return vdupq_laneq_f32(value, 0); }
static inline TSimdFloat32x4 tfSimdFloat3To4Splat1(TSimdFloat32x3 value) { return vdupq_laneq_f32(value, 1); }
static inline TSimdFloat32x4 tfSimdFloat3To4Splat2(TSimdFloat32x3 value) { return vdupq_laneq_f32(value, 2); }

inline TSimdFloat32x3 tfSimd3fSplatIndex0(TSimdFloat32x3 value) { return vdupq_laneq_f32(value, 0); }

inline TSimdFloat32x3 tfSimd3fSplatIndex1(TSimdFloat32x3 value) { return vdupq_laneq_f32(value, 1); }

inline TSimdFloat32x3 tfSimd3fSplatIndex2(TSimdFloat32x3 value) { return vdupq_laneq_f32(value, 2); }

inline TSimdInt32x3 tfSimd3iSplat(int32_t value) { return vdupq_n_s32(value); }

inline TSimdFloat32x3 tfSimd3fSplat(float value) { return vdupq_n_f32(value); }

inline TSimdInt32x3 tfSimd3iCmpEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vceqq_s32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iCmpNeq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vmvnq_s32(vceqq_s32(arg1, arg2)); }
inline TSimdInt32x3 tfSimd3iCmpGt(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vcgtq_s32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iCmpGtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vcgeq_s32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iCmpLt(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vcltq_s32(arg1, arg2); }
inline TSimdInt32x3 tfSimd3iCmpLtEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) { return vcleq_s32(arg1, arg2); }
inline bool         tfSimd3fCmpAllEq(TSimdFloat32x3 arg1, TSimdFloat32x3 arg2) {
   // for (int i = 0; i < 3; i++) {
   //     if (arg1.v[i] != arg2.v[i]) {
   //         return false;
   //     }
   // }
    return true;
}

inline bool tfSimd3iCmpAllEq(TSimdInt32x3 arg1, TSimdInt32x3 arg2) {
   // for (int i = 0; i < 3; i++) {
   //     if (arg1.v[i] != arg2.v[i]) {
   //         return false;
   //     }
   // }
    return true;
}
