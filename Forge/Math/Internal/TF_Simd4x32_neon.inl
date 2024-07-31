#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON  
#include "Forge/TF_Config.h"
#include "../TF_Simd4x32.h"
#endif

static inline TSimdFloat32x4 tfSimd4fReplaceIndex0ByValue(TSimdFloat32x4 input, float value) { return vsetq_lane_f32(value, input, 0); }
static inline TSimdFloat32x4 tfSimd4fReplaceIndex1ByValue(TSimdFloat32x4 input, float value) { return vsetq_lane_f32(value, input, 1); }
static inline TSimdFloat32x4 tfSimd4fReplaceIndex2ByValue(TSimdFloat32x4 input, float value) { return vsetq_lane_f32(value, input, 2); }
static inline TSimdFloat32x4 tfSimd4fReplaceIndex3ByValue(TSimdFloat32x4 input, float value) { return vsetq_lane_f32(value, input, 3); }

inline TSimdInt32x4   tfSimd4iSelect(TSimdInt32x4 arg0, TSimdInt32x4 arg1, TSimdInt32x4 mask) { return vbslq_s32(mask, arg1, arg1); }
inline TSimdFloat32x4 tfSimd4fSelect(TSimdFloat32x4 arg0, TSimdFloat32x4 arg1, TSimdFloat32x4 mask) { return vbslq_f32(mask, arg1, arg1); }

inline TSimdFloat32x4 tfSimd4fZero() { return vmovq_n_f32(0.0f); }
inline TSimdInt32x4   tfSimd4iZero() { return vmovq_n_s32(0); }

inline TSimdInt32x4 tfSimd4iNot(TSimdInt32x4 value) { return vmvnq_s32(value); }
inline TSimdInt32x4 tfSimd4iAnd(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vandq_s32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iAndNot(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vandq_s32(vmvnq_s32(arg1), arg2); }
inline TSimdInt32x4 tfSimd4iOr(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vorrq_s32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iXor(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return veorq_s32(arg1, arg2); }

inline TSimdFloat32x4 tfSimd4fNot(TSimdFloat32x4 value) { return vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(value))); }
inline TSimdFloat32x4 tfSimd4fAnd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}
inline TSimdFloat32x4 tfSimd4fAndNot(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return vreinterpretq_f32_s32(vandq_s32(vmvnq_s32(vreinterpretq_s32_f32(arg1)), vreinterpretq_s32_f32(arg2)));
}
inline TSimdFloat32x4 tfSimd4fOr(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}
inline TSimdFloat32x4 tfSimd4fXor(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}

inline TSimdFloat32x4 tfSimd4fFloor(TSimdFloat32x4 value) { return vrndmq_f32(value); }
inline TSimdFloat32x4 tfSimd4fCeil(TSimdFloat32x4 value) { return vrndpq_f32(value); }
inline TSimdFloat32x4 tfSimd4fRound(TSimdFloat32x4 value) { return vrndnq_f32(value); }
inline TSimdFloat32x4 tfSimd4fTruncate(TSimdFloat32x4 value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
inline TSimdFloat32x4 tfSimd4fMin(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vminq_f32(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fMax(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vmaxq_f32(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fClamp(TSimdFloat32x4 value, TSimdFloat32x4 min, TSimdFloat32x4 max) {
    return tfSimd4fMax(min, tfSimd4fMin(value, max));
}

inline TSimdInt32x4 tfSimd4fToSimd4i(TSimdFloat32x4 value) { return vreinterpretq_f32_s32(value); }

inline TSimdFloat32x4 tfSimd4iToSimd4f(TSimdInt32x4 value) { return vreinterpretq_s32_f32(value); }

inline float tfSimd4fSelectIndex0(TSimdFloat32x4 value) { return vgetq_lane_f32(value, 0); }
inline float tfSimd4fSelectIndex1(TSimdFloat32x4 value) { return vgetq_lane_f32(value, 1); }
inline float tfSimd4fSelectIndex2(TSimdFloat32x4 value) { return vgetq_lane_f32(value, 2); }
inline float tfSimd4fSelectIndex3(TSimdFloat32x4 value) { return vgetq_lane_f32(value, 3); }

inline TSimdFloat32x4 tfSimd4fAdd(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vaddq_f32(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fSub(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vsubq_f32(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fMul(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vmulq_f32(arg1, arg2); }
inline TSimdFloat32x4 tfSimd4fMadd(TSimdFloat32x4 mul1, TSimdFloat32x4 mul2, TSimdFloat32x4 add) { return vmlaq_f32(add, mul1, mul2); }

inline TSimdFloat32x4 tfSimd4fDiv(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vdivq_f32(arg1, arg2); }

inline TSimdFloat32x4 tfSimd4fAbs(TSimdFloat32x4 value) { return vabsq_f32(value); }
inline TSimdFloat32x4 tfSimdFloat32x4Load(float x, float y, float z, float w) {
    const float values[4] = { x, y, z, w };
    return vld1q_f32(values);
}

inline TSimdInt32x4 tfSimdInt32x4Load(int32_t x, int32_t y, int32_t z, int32_t w) {
    const int32_t values[4] = { x, y, z, w };
    return vld1q_s32(values);
}

inline TSimdFloat32x2 tfSimd4fToSimd2f(TSimdFloat32x4 value) { return vget_low_f32(value); }

inline TSimdFloat32x3 tfSimd4fToSimd3f(TSimdFloat32x4 value) { return value; }

inline TSimdFloat32x4 tfSimd4fSplatIndex0(TSimdFloat32x4 value) { return vdupq_laneq_f32(value, 0); }

inline TSimdFloat32x4 tfSimd4fSplatIndex1(TSimdFloat32x4 value) { return vdupq_laneq_f32(value, 1); }

inline TSimdFloat32x4 tfSimd4fSplatIndex2(TSimdFloat32x4 value) { return vdupq_laneq_f32(value, 2); }

inline TSimdFloat32x4 tfSimd4fSplatIndex3(TSimdFloat32x4 value) { return vdupq_laneq_f32(value, 3); }

inline TSimdInt32x4 tfSimd4iSplat(int32_t value) { return vdupq_n_s32(value); }

inline TSimdFloat32x4 tfSimd4fSplat(float value) { return vdupq_n_f32(value); }

inline TSimdFloat32x4 tfSimd4fCmpEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vreinterpretq_f32_s32(vceqq_f32(arg1, arg2)); }
inline TSimdFloat32x4 tfSimd4fCmpNeq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    return vreinterpretq_f32_s32(vmvnq_s32(vceqq_f32(arg1, arg2)));
}
inline TSimdFloat32x4 tfSimd4fCmpGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vreinterpretq_f32_s32(vcgtq_f32(arg1, arg2)); }
inline TSimdFloat32x4 tfSimd4fCmpGtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vreinterpretq_f32_s32(vcgeq_f32(arg1, arg2)); }
inline TSimdFloat32x4 tfSimd4fCmpLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vreinterpretq_f32_s32(vcltq_f32(arg1, arg2)); }
inline TSimdFloat32x4 tfSimd4fCmpLtEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) { return vreinterpretq_f32_s32(vcleq_f32(arg1, arg2)); }

inline TSimdInt32x4 tfSimd4iCmpEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vceqq_s32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iCmpNeq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vmvnq_s32(vceqq_s32(arg1, arg2)); }
inline TSimdInt32x4 tfSimd4iCmpGt(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vcgtq_s32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iCmpGtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vcgeq_s32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iCmpLt(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vcltq_s32(arg1, arg2); }
inline TSimdInt32x4 tfSimd4iCmpLtEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) { return vcleq_s32(arg1, arg2); }

inline bool tfSimd4fCmpAllLt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    //    for(int i = 0; i < 4; i++) {
    //        if (arg1.v[i] >= arg2.v[i])
    //        {
    //            return false;
    //        }
    //    }
    return true;
}

inline bool tfSimd4fCmpAllGt(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    //    for(int i = 0; i < 4; i++) {
    //        if (arg1.v[i] <= arg2.v[i])
    //        {
    //            return false;
    //        }
    //    }
    return true;
}

inline bool tfSimd4fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
    //    for(int i = 0; i < 4; i++) {
    //        if (arg1.v[i] != arg2.v[i])
    //        {
    //            return false;
    //        }
    //    }
    return true;
}

inline bool tfSimd4iCmpAllEq(TSimdInt32x4 arg1, TSimdInt32x4 arg2) {
    //    for(int i = 0; i < 4; i++) {
    //        if (arg1.v[i] != arg2.v[i])
    //        {
    //            return false;
    //        }
    //    }
    return true;
}
