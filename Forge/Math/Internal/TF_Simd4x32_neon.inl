#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON  
#include "Forge/TF_Config.h"
#include "../TF_Simd32x4.h"
#endif

static inline Tsimd_f32x4_t tfSimd4fReplaceIndex0ByValue(Tsimd_f32x4_t input, float value) { return vsetq_lane_f32(value, input, 0); }
static inline Tsimd_f32x4_t tfSimd4fReplaceIndex1ByValue(Tsimd_f32x4_t input, float value) { return vsetq_lane_f32(value, input, 1); }
static inline Tsimd_f32x4_t tfSimd4fReplaceIndex2ByValue(Tsimd_f32x4_t input, float value) { return vsetq_lane_f32(value, input, 2); }
static inline Tsimd_f32x4_t tfSimd4fReplaceIndex3ByValue(Tsimd_f32x4_t input, float value) { return vsetq_lane_f32(value, input, 3); }

inline Tsimd_i32x4_t   tfSimd4iSelect(Tsimd_i32x4_t arg0, Tsimd_i32x4_t arg1, Tsimd_i32x4_t mask) { return vbslq_s32(mask, arg1, arg1); }
inline Tsimd_f32x4_t tfSimd4fSelect(Tsimd_f32x4_t arg0, Tsimd_f32x4_t arg1, Tsimd_f32x4_t mask) { return vbslq_f32(mask, arg1, arg1); }

inline Tsimd_f32x4_t tfSimd4fZero() { return vmovq_n_f32(0.0f); }
inline Tsimd_i32x4_t   tfSimd4iZero() { return vmovq_n_s32(0); }

inline Tsimd_i32x4_t tfSimd4iNot(Tsimd_i32x4_t value) { return vmvnq_s32(value); }
inline Tsimd_i32x4_t tfSimd4iAnd(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vandq_s32(arg1, arg2); }
inline Tsimd_i32x4_t tfSimd4iAndNot(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vandq_s32(vmvnq_s32(arg1), arg2); }
inline Tsimd_i32x4_t tfSimd4iOr(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vorrq_s32(arg1, arg2); }
inline Tsimd_i32x4_t tfSimd4iXor(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return veorq_s32(arg1, arg2); }

inline Tsimd_f32x4_t tfSimd4fNot(Tsimd_f32x4_t value) { return vreinterpretq_f32_s32(vmvnq_s32(vreinterpretq_s32_f32(value))); }
inline Tsimd_f32x4_t tfSimd4fAnd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}
inline Tsimd_f32x4_t tfSimd4fAndNot(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vreinterpretq_f32_s32(vandq_s32(vmvnq_s32(vreinterpretq_s32_f32(arg1)), vreinterpretq_s32_f32(arg2)));
}
inline Tsimd_f32x4_t tfSimd4fOr(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vreinterpretq_f32_s32(vorrq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}
inline Tsimd_f32x4_t tfSimd4fXor(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vreinterpretq_f32_s32(veorq_s32(vreinterpretq_s32_f32(arg1), vreinterpretq_s32_f32(arg2)));
}

inline Tsimd_f32x4_t tfSimd4fFloor(Tsimd_f32x4_t value) { return vrndmq_f32(value); }
inline Tsimd_f32x4_t tfSimd4fCeil(Tsimd_f32x4_t value) { return vrndpq_f32(value); }
inline Tsimd_f32x4_t tfSimd4fRound(Tsimd_f32x4_t value) { return vrndnq_f32(value); }
inline Tsimd_f32x4_t tfSimd4fTruncate(Tsimd_f32x4_t value) { return tfSimd4iToSimd4f(tfSimd4fToSimd4i(value)); }
inline Tsimd_f32x4_t tfSimd4fMin(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vminq_f32(arg1, arg2); }
inline Tsimd_f32x4_t tfSimd4fMax(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vmaxq_f32(arg1, arg2); }
inline Tsimd_f32x4_t tfSimd4fClamp(Tsimd_f32x4_t value, Tsimd_f32x4_t min, Tsimd_f32x4_t max) {
    return tfSimd4fMax(min, tfSimd4fMin(value, max));
}

inline Tsimd_i32x4_t tfSimd4fToSimd4i(Tsimd_f32x4_t value) { return vreinterpretq_f32_s32(value); }

inline Tsimd_f32x4_t tfSimd4iToSimd4f(Tsimd_i32x4_t value) { return vreinterpretq_s32_f32(value); }

inline float tfS32x4FSelectIndex0(Tsimd_f32x4_t value) { return vgetq_lane_f32(value, 0); }
inline float tfS32x4FSelectIndex1(Tsimd_f32x4_t value) { return vgetq_lane_f32(value, 1); }
inline float tfS32x4FSelectIndex2(Tsimd_f32x4_t value) { return vgetq_lane_f32(value, 2); }
inline float tfS32x4FSelectIndex3(Tsimd_f32x4_t value) { return vgetq_lane_f32(value, 3); }

inline Tsimd_f32x4_t tfSimd4fAdd(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vaddq_f32(arg1, arg2); }
inline Tsimd_f32x4_t tfSimd4fSub(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vsubq_f32(arg1, arg2); }
inline Tsimd_f32x4_t tfSimd4fMul(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vmulq_f32(arg1, arg2); }
inline Tsimd_f32x4_t tfSimd4fMadd(Tsimd_f32x4_t mul1, Tsimd_f32x4_t mul2, Tsimd_f32x4_t add) { return vmlaq_f32(add, mul1, mul2); }

inline Tsimd_f32x4_t tfSimd4fDiv(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vdivq_f32(arg1, arg2); }

inline Tsimd_f32x4_t tfSimd4fAbs(Tsimd_f32x4_t value) { return vabsq_f32(value); }
inline Tsimd_f32x4_t tfSimdFloat4x32Load(float x, float y, float z, float w) {
    const float values[4] = { x, y, z, w };
    return vld1q_f32(values);
}

inline Tsimd_i32x4_t tfSimdInt4x32Load(int32_t x, int32_t y, int32_t z, int32_t w) {
    const int32_t values[4] = { x, y, z, w };
    return vld1q_s32(values);
}

inline Tsimd_f32x2_t tfSimd4fToSimd2f(Tsimd_f32x4_t value) { return vget_low_f32(value); }

inline Tsimd_f32x3_t tfSimd4fToSimd3f(Tsimd_f32x4_t value) { return value; }

inline Tsimd_f32x4_t tfSimd4fSplatIndex0(Tsimd_f32x4_t value) { return vdupq_laneq_f32(value, 0); }

inline Tsimd_f32x4_t tfSimd4fSplatIndex1(Tsimd_f32x4_t value) { return vdupq_laneq_f32(value, 1); }

inline Tsimd_f32x4_t tfSimd4fSplatIndex2(Tsimd_f32x4_t value) { return vdupq_laneq_f32(value, 2); }

inline Tsimd_f32x4_t tfSimd4fSplatIndex3(Tsimd_f32x4_t value) { return vdupq_laneq_f32(value, 3); }

inline Tsimd_i32x4_t tfSimd4iSplat(int32_t value) { return vdupq_n_s32(value); }

inline Tsimd_f32x4_t tfSimd4fSplat(float value) { return vdupq_n_f32(value); }

inline Tsimd_f32x4_t tfSimd4fCmpEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vreinterpretq_f32_s32(vceqq_f32(arg1, arg2)); }
inline Tsimd_f32x4_t tfSimd4fCmpNeq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vreinterpretq_f32_s32(vmvnq_s32(vceqq_f32(arg1, arg2)));
}
inline Tsimd_f32x4_t tfSimd4fCmpGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vreinterpretq_f32_s32(vcgtq_f32(arg1, arg2)); }
inline Tsimd_f32x4_t tfSimd4fCmpGtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vreinterpretq_f32_s32(vcgeq_f32(arg1, arg2)); }
inline Tsimd_f32x4_t tfSimd4fCmpLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vreinterpretq_f32_s32(vcltq_f32(arg1, arg2)); }
inline Tsimd_f32x4_t tfSimd4fCmpLtEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) { return vreinterpretq_f32_s32(vcleq_f32(arg1, arg2)); }

inline Tsimd_i32x4_t tfSimd4iCmpEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vceqq_s32(arg1, arg2); }
inline Tsimd_i32x4_t tfSimd4iCmpNeq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vmvnq_s32(vceqq_s32(arg1, arg2)); }
inline Tsimd_i32x4_t tfSimd4iCmpGt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vcgtq_s32(arg1, arg2); }
inline Tsimd_i32x4_t tfSimd4iCmpGtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vcgeq_s32(arg1, arg2); }
inline Tsimd_i32x4_t tfSimd4iCmpLt(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vcltq_s32(arg1, arg2); }
inline Tsimd_i32x4_t tfSimd4iCmpLtEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) { return vcleq_s32(arg1, arg2); }

inline bool tfSimd4fCmpAllLt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vminv_u32(vcltq_f32(arg1, arg2)) != 0;
}

inline bool tfSimd4fCmpAllGt(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vminv_u32(vcgtq_f32(arg1, arg2)) != 0;
}

inline bool tfSimd4fCmpAllEq(Tsimd_f32x4_t arg1, Tsimd_f32x4_t arg2) {
    return vminv_u32(vceqq_f32(arg1, arg2)) != 0;
}

inline bool tfSimd4iCmpAllEq(Tsimd_i32x4_t arg1, Tsimd_i32x4_t arg2) {
    return vminv_u32(vceqq_s32(arg1, arg2)) != 0;
}
