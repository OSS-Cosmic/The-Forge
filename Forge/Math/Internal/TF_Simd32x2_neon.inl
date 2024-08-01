#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON
#include "Forge/TF_Config.h"
#include "../TF_Simd32x2.h"
#endif

inline TSimdInt32x2   tfSimd2iSelect(TSimdInt32x2 arg0, TSimdInt32x2 arg1, TSimdInt32x2 mask) { return vbsl_s32(mask, arg1, arg1); }
inline TSimdFloat32x2 tfSimd2fSelect(TSimdFloat32x2 arg0, TSimdFloat32x2 arg1, TSimdFloat32x2 mask) { return vbsl_f32(mask, arg1, arg2); }

inline TSimdFloat32x2 tfSimd2fZero() { return vmov_n_f32(0); }
inline TSimdInt32x2   tfSimd2iZero() { return vmov_n_s32(0); }

inline TSimdInt32x2 tfSimd2iNot(TSimdInt32x2 value) { return vmvn_s32(value); }
inline TSimdInt32x2 tfSimd2iAnd(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vand_s32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iAndNot(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vand_s32(vmvn_s32(arg1), arg2); }
inline TSimdInt32x2 tfSimd2iOr(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vorr_s32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iXor(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return veor_s32(arg1, arg2); }

inline TSimdFloat32x2 tfSimd2fNot(TSimdFloat32x2 value) { return vreinterpret_f32_s32(vmvn_s32(vreinterpret_s32_f32(value))); }
inline TSimdFloat32x2 tfSimd2fAnd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return vreinterpret_f32_s32(vand_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
}
inline TSimdFloat32x2 tfSimd2fAndNot(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return vreinterpret_f32_s32(vand_s32(vmvn_s32(vreinterpret_s32_f32(arg1)), vreinterpret_s32_f32(arg2)));
}
inline TSimdFloat32x2 tfSimd2fOr(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return vreinterpret_f32_s32(vorr_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
}
inline TSimdFloat32x2 tfSimd2fXor(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) {
    return vreinterpret_f32_s32(veor_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
}

inline TSimdFloat32x2 tfSimd2fFloor(TSimdFloat32x2 value) { return vrndm_f32(value); }
inline TSimdFloat32x2 tfSimd2fCeil(TSimdFloat32x2 value) { return vrndp_f32(value); }
inline TSimdFloat32x2 tfSimd2fRound(TSimdFloat32x2 value) { return vrndn_f32(value); }
inline TSimdFloat32x2 tfSimd2fTruncate(TSimdFloat32x2 value) { return tfSimd2iToSimd2f(tfSimd2fToSimd2i(value)); }
inline TSimdFloat32x2 tfSimd2fMin(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return vmin_f32(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fMax(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return vmax_f32(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fClamp(TSimdFloat32x2 value, TSimdFloat32x2 min, TSimdFloat32x2 max) {
    return tfSimd2fMax(min, tfSimd2fMin(value, max));
}

inline TSimdInt32x2 tfSimd2fToSimd2i(TSimdFloat32x2 value) { return vreinterpret_s32_f32(value); }

inline TSimdFloat32x2 tfSimd2iToSimd2f(TSimdInt32x2 value) { return vreinterpret_f32_s32(value); }

inline float tfSimd2fSelectIndex0(TSimdFloat32x2 value) { return vget_lane_f32(value, 0); }

inline float tfSimd2fSelectIndex1(TSimdFloat32x2 value) { return vget_lane_f32(value, 1); }

inline TSimdFloat32x2 tfSimd2fAdd(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return vadd_f32(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fSub(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return vsub_f32(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fMul(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return vmul_f32(arg1, arg2); }
inline TSimdFloat32x2 tfSimd2fMadd(TSimdFloat32x2 mul1, TSimdFloat32x2 mul2, TSimdFloat32x2 add) { return vmla_f32(add, mul1, mul2); }
inline TSimdFloat32x2 tfSimd2fDiv(TSimdFloat32x2 arg1, TSimdFloat32x2 arg2) { return vdiv_f32(arg1, arg2); }

inline TSimdFloat32x2 tfSimd2fAbs(TSimdFloat32x2 value) { return vabs_f32(value); }

inline TSimdFloat32x2 tfSimdFloat2Load(float x, float y) {
    const float values[2] = { x, y };
    return vld1_f32(values);
}

inline TSimdInt32x2 tfSimd2iLoadImmediate(int32_t x, int32_t y) {
    const int32_t values[2] = { x, y };
    return vld1_s32(values);
}

inline TSimdFloat32x2 tfSimd2fSplatIndex0(TSimdFloat32x2 value) { return vdup_lane_f32(value, 0); }

inline TSimdFloat32x2 tfSimd2fSplatIndex1(TSimdFloat32x2 value) { return vdup_lane_f32(value, 1); }

inline TSimdInt32x2 tfSimd2iSplat(int32_t value) { return vdup_n_s32(value); }

inline TSimdFloat32x2 tfSimd2fSplat(float value) { return vdup_n_f32(value); }

inline TSimdInt32x2 tfSimd2iCmpEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vceq_s32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iCmpNeq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vmvn_s32(vceq_s32(arg1, arg2)); }
inline TSimdInt32x2 tfSimd2iCmpGt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vcgt_s32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iCmpGtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vcgt_s32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iCmpLt(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vclt_s32(arg1, arg2); }
inline TSimdInt32x2 tfSimd2iCmpLtEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) { return vcle_s32(arg1, arg2); }

inline bool tfSimd2fCmpAllEq(TSimdFloat32x4 arg1, TSimdFloat32x4 arg2) {
//    for (int i = 0; i < 2; i++) {
//        if (arg1.v[i] != arg2.v[i]) {
//            return false;
//        }
//    }
    return true;
}

inline bool tfSimd2iCmpAllEq(TSimdInt32x2 arg1, TSimdInt32x2 arg2) {
//    for (int i = 0; i < 2; i++) {
//        if (arg1.v[i] != arg2.v[i]) {
//            return false;
//        }
//    }
    return true;
}
