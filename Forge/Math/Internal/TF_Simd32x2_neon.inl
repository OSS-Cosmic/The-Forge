#if defined(__CLANGD__)
#define TF_FEATURE_CPU_NEON
#include "Forge/TF_Config.h"
#include "../TF_Simd32x2.h"
#endif

inline Tsimd_i32x2_t   tfS32x2ISelect(Tsimd_i32x2_t arg0, Tsimd_i32x2_t arg1, Tsimd_i32x2_t mask) { return vbsl_s32(mask, arg1, arg1); }
inline Tsimd_f32x2_t tfS32x2FSelect(Tsimd_f32x2_t arg0, Tsimd_f32x2_t arg1, Tsimd_f32x2_t mask) { return vbsl_f32(mask, arg1, arg2); }

inline Tsimd_f32x2_t tfS32x2FZero() { return vmov_n_f32(0); }
inline Tsimd_i32x2_t   tfS32x2IZero() { return vmov_n_s32(0); }

inline Tsimd_i32x2_t tfS32x2INot(Tsimd_i32x2_t value) { return vmvn_s32(value); }
inline Tsimd_i32x2_t tfS32x2IAnd(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vand_s32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2IAndNot(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vand_s32(vmvn_s32(arg1), arg2); }
inline Tsimd_i32x2_t tfS32x2IOr(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vorr_s32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2IXor(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return veor_s32(arg1, arg2); }

inline Tsimd_f32x2_t tfS32x2FNot(Tsimd_f32x2_t value) { return vreinterpret_f32_s32(vmvn_s32(vreinterpret_s32_f32(value))); }
inline Tsimd_f32x2_t tfS32x2FAnd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return vreinterpret_f32_s32(vand_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
}
inline Tsimd_f32x2_t tfS32x2FAndNot(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return vreinterpret_f32_s32(vand_s32(vmvn_s32(vreinterpret_s32_f32(arg1)), vreinterpret_s32_f32(arg2)));
}
inline Tsimd_f32x2_t tfS32x2FOr(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return vreinterpret_f32_s32(vorr_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
}
inline Tsimd_f32x2_t tfS32x2FXor(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) {
    return vreinterpret_f32_s32(veor_s32(vreinterpret_s32_f32(arg1), vreinterpret_s32_f32(arg2)));
}

inline Tsimd_f32x2_t tfS32x2FFloor(Tsimd_f32x2_t value) { return vrndm_f32(value); }
inline Tsimd_f32x2_t tfS32x2FCeil(Tsimd_f32x2_t value) { return vrndp_f32(value); }
inline Tsimd_f32x2_t tfS32x2FRound(Tsimd_f32x2_t value) { return vrndn_f32(value); }
inline Tsimd_f32x2_t tfS32x2FTruncate(Tsimd_f32x2_t value) { return tfS32x2IToSimd2f(tfS32x2FToSimd2i(value)); }
inline Tsimd_f32x2_t tfS32x2FMin(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return vmin_f32(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FMax(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return vmax_f32(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FClamp(Tsimd_f32x2_t value, Tsimd_f32x2_t min, Tsimd_f32x2_t max) {
    return tfS32x2FMax(min, tfS32x2FMin(value, max));
}

inline Tsimd_i32x2_t tfS32x2FToSimd2i(Tsimd_f32x2_t value) { return vreinterpret_s32_f32(value); }

inline Tsimd_f32x2_t tfS32x2IToSimd2f(Tsimd_i32x2_t value) { return vreinterpret_f32_s32(value); }

inline float tfS32x2FSelectIndex0(Tsimd_f32x2_t value) { return vget_lane_f32(value, 0); }

inline float tfS32x2FSelectIndex1(Tsimd_f32x2_t value) { return vget_lane_f32(value, 1); }

inline Tsimd_f32x2_t tfS32x2FAdd(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return vadd_f32(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FSub(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return vsub_f32(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FMul(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return vmul_f32(arg1, arg2); }
inline Tsimd_f32x2_t tfS32x2FMadd(Tsimd_f32x2_t mul1, Tsimd_f32x2_t mul2, Tsimd_f32x2_t add) { return vmla_f32(add, mul1, mul2); }
inline Tsimd_f32x2_t tfS32x2FDiv(Tsimd_f32x2_t arg1, Tsimd_f32x2_t arg2) { return vdiv_f32(arg1, arg2); }

inline Tsimd_f32x2_t tfS32x2FAbs(Tsimd_f32x2_t value) { return vabs_f32(value); }

inline Tsimd_f32x2_t tfSimdFloat2Load(float x, float y) {
    const float values[2] = { x, y };
    return vld1_f32(values);
}

inline Tsimd_i32x2_t tfS32x2ILoadImmediate(int32_t x, int32_t y) {
    const int32_t values[2] = { x, y };
    return vld1_s32(values);
}

inline Tsimd_f32x2_t tfS32x2FSplatIndex0(Tsimd_f32x2_t value) { return vdup_lane_f32(value, 0); }

inline Tsimd_f32x2_t tfS32x2FSplatIndex1(Tsimd_f32x2_t value) { return vdup_lane_f32(value, 1); }

inline Tsimd_i32x2_t tfS32x2ISplat(int32_t value) { return vdup_n_s32(value); }

inline Tsimd_f32x2_t tfS32x2FSplat(float value) { return vdup_n_f32(value); }

inline Tsimd_i32x2_t tfS32x2ICmpEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vceq_s32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2ICmpNeq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vmvn_s32(vceq_s32(arg1, arg2)); }
inline Tsimd_i32x2_t tfS32x2ICmpGt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vcgt_s32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2ICmpGtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vcgt_s32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2ICmpLt(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vclt_s32(arg1, arg2); }
inline Tsimd_i32x2_t tfS32x2ICmpLtEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) { return vcle_s32(arg1, arg2); }

inline bool tfS32x2FCmpAllEq(TSimd32Fx4 arg1, TSimd32Fx4 arg2) {
//    for (int i = 0; i < 2; i++) {
//        if (arg1.v[i] != arg2.v[i]) {
//            return false;
//        }
//    }
    return true;
}

inline bool tfS32x2ICmpAllEq(Tsimd_i32x2_t arg1, Tsimd_i32x2_t arg2) {
//    for (int i = 0; i < 2; i++) {
//        if (arg1.v[i] != arg2.v[i]) {
//            return false;
//        }
//    }
    return true;
}
