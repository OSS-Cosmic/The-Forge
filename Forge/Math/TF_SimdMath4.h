#include "Forge/Math/Internal/Types.h"

inline Simd_FloatType4 tfSimd4fSplat(float value);
inline Simd_Int32Type4 tfSimd4iSplat(int32_t value);

inline Simd_FloatType  tfSimd4fToSimd1f(Simd_FloatType4 value);
inline Simd_FloatType2 tfSimd4fToSimd2f(Simd_FloatType4 value);
inline Simd_FloatType3 tfSimd4fToSimd3f(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fToSimd4i(Simd_Int32Type4 value);
inline Simd_Int32Type4  tfSimd4iToSimd4f(Simd_FloatType4 value);

inline Simd_FloatType4 tfSimd4fSplatIndex0(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fSplatIndex1(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fSplatIndex2(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fSplatIndex3(Simd_FloatType4 value);

inline float tfSimd4fSelectIndex0(Simd_FloatType4 value);
inline float tfSimd4fSelectIndex1(Simd_FloatType4 value);
inline float tfSimd4fSelectIndex2(Simd_FloatType4 value);
inline float tfSimd4fSelectIndex3(Simd_FloatType4 value);

inline Simd_FloatType4 tfSimd4fLoadImmediate(float x, float y, float z, float w);

inline float tfSimd4fSelectIndex1(Simd_FloatType4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex1(value)); }
inline float tfSimd4fSelectIndex2(Simd_FloatType4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex2(value)); }
inline float tfSimd4fSelectIndex3(Simd_FloatType4 value) { return tfSimd4fSelectIndex0(tfSimd4fSplatIndex3(value)); }

inline Simd_FloatType4 tfSimd4fReplaceIndex0Value(Simd_FloatType4 a, float b);
inline Simd_FloatType4 tfSimd4fReplaceIndex1Value(Simd_FloatType4 a, float b);
inline Simd_FloatType4 tfSimd4fReplaceIndex2Value(Simd_FloatType4 a, float b);
inline Simd_FloatType4 tfSimd4fReplaceIndex3Value(Simd_FloatType4 a, float b);
inline Simd_FloatType4 tfSimd4fReplaceIndex0Simd4(Simd_FloatType4 a, Simd_FloatType4 b);
inline Simd_FloatType4 tfSimd4fReplaceIndex1Simd4(Simd_FloatType4 a, Simd_FloatType4 b);
inline Simd_FloatType4 tfSimd4fReplaceIndex2Simd4(Simd_FloatType4 a, Simd_FloatType4 b);
inline Simd_FloatType4 tfSimd4fReplaceIndex3Simd4(Simd_FloatType4 a, Simd_FloatType4 b);

inline Simd_FloatType4 tfSimd4fAdd(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fSub(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fMul(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fMadd(Simd_FloatType4 mul1, Simd_FloatType4 mul2, Simd_FloatType4 add);
inline Simd_FloatType4 tfSimd4fDiv(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fAbs(Simd_FloatType4 value);

inline Simd_FloatType4 tfSimd4fNot(Simd_FloatType4 value);
inline Simd_FloatType4 tfSimd4fAnd(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fAndNot(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fOr(Simd_FloatType4 arg1, Simd_FloatType4 arg2);
inline Simd_FloatType4 tfSimd4fXor(Simd_FloatType4 arg1, Simd_FloatType4  arg2);

inline Simd_Int32Type4 tfSimd4fNot(Simd_Int32Type4 value);
inline Simd_Int32Type4 tfSimd4fAnd(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4fAndNot(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4fOr(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_Int32Type4 tfSimd4fXor(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);

inline Simd_FloatType4 tfSimd4fFloor(Simd_Int32Type4 value);
inline Simd_FloatType4 tfSimd4fCeil(Simd_Int32Type4 value);
inline Simd_FloatType4 tfSimd4fRound(Simd_Int32Type4 value); // Ties to even (banker's rounding)
inline Simd_FloatType4 tfSimd4fTruncate(Simd_Int32Type4  value);
inline Simd_FloatType4 tfSimd4fMin(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_FloatType4 tfSimd4fMax(Simd_Int32Type4 arg1, Simd_Int32Type4 arg2);
inline Simd_FloatType4 tfSimd4fClamp(Simd_Int32Type4  value, Simd_Int32Type4 min, Simd_Int32Type4 max);

inline Simd_FloatType4 tfSimd4fNot(Simd_FloatType4 value) { 
    return value; 
}
inline Simd_FloatType4 tfSimd4fAnd(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { return arg1; }
inline Simd_FloatType4 tfSimd4fAndNot(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { return arg1; }
inline Simd_FloatType4 tfSimd4fOr(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { return arg1; }
inline Simd_FloatType4 tfSimd4fXor(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { return arg1; }

inline Simd_FloatType4  tfSimd4fToSimd4i(Simd_Int32Type4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castps_si128(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (float)value.v[0], (float)value.v[1], (float)value.v[2], (float)value.v[3] };
#endif
}
inline Simd_Int32Type4  tfSimd4iToSimd4f(Simd_FloatType4 value)  {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_castsi128_ps(value); 
#elif defined(TF_FEATURE_CPU_SCALAR)
    return { (int32_t)value.v[0], (int32_t)value.v[1], (int32_t)value.v[2], (int32_t)value.v[3] };
#endif
}

inline float tfSimd4fSelectIndex0(Simd_FloatType4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
  return _mm_cvtss_f32(value);
#elif defined(TF_FEATURE_CPU_SCALAR)
  return value.v[0];
#endif
}


inline Simd_FloatType4 tfSimd4fAdd(Simd_FloatType4 arg1, Simd_FloatType4 arg2) { 
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_add_ps(arg1, arg2); 
#else
    return {
        arg1.v[0] + arg2.v[0],
        arg1.v[1] + arg2.v[1],
        arg1.v[2] + arg2.v[2],
        arg1.v[3] + arg2.v[3],
    };
#endif
}
inline Simd_FloatType4 tfSimd4fSub(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_sub_ps(arg1, arg2); 
#else
    return {
        arg1.v[0] - arg2.v[0],
        arg1.v[1] - arg2.v[1],
        arg1.v[2] - arg2.v[2],
        arg1.v[3] - arg2.v[3],
    };
#endif
}
inline Simd_FloatType4 tfSimd4fMul(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_mul_ps(arg1, arg2); 
#else
    return {
        arg1.v[0] * arg2.v[0],
        arg1.v[1] * arg2.v[1],
        arg1.v[2] * arg2.v[2],
        arg1.v[3] * arg2.v[3],
    };
#endif

}
inline Simd_FloatType4 tfSimd4fMadd(Simd_FloatType4 mul1, Simd_FloatType4 mul2, Simd_FloatType4 add)
{
#if 0
    return _mm_fmadd_ps(mul1, mul2, add); // Requires FMA CPUID
#else
    return tfSimd4fAdd(tfSimd4fMul(mul1, mul2), add);
#endif
}
inline Simd_FloatType4 tfSimd4fDiv(Simd_FloatType4 arg1, Simd_FloatType4 arg2) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_div_ps(arg1, arg2);
#else
    return {
        arg1.v[0] / arg2.v[0],
        arg1.v[1] / arg2.v[1],
        arg1.v[2] / arg2.v[2],
        arg1.v[3] / arg2.v[3],
    };
#endif
}

inline Simd_FloatType4 tfSimd4fAbs(Simd_FloatType4 value) { 
#if defined(TF_FEATURE_CPU_SSE)
    return value;
    //return _mm_abs_epi32(value); 
#else
    return {
        abs(value.v[0]),
        abs(value.v[1]),
        abs(value.v[2]),
        abs(value.v[3]),
    };
#endif
}

inline Simd_FloatType4 tfSimd4fReplaceIndex0Value(Simd_FloatType4 a, float b) { 
    return tfSimd4fReplaceIndex0Simd4(a, tfSimd4fSplat(b));
}

inline Simd_FloatType4 tfSimd4fReplaceIndex1Value(Simd_FloatType4 a, float b) { 
    return tfSimd4fReplaceIndex1Simd4(a, tfSimd4fSplat(b));
}

inline Simd_FloatType4 tfSimd4fReplaceIndex2Value(Simd_FloatType4 a, float b) { 
    return tfSimd4fReplaceIndex2Simd4(a, tfSimd4fSplat(b));
}

inline Simd_FloatType4 tfSimd4fReplaceIndex3Value(Simd_FloatType4 a, float b) { 
    return tfSimd4fReplaceIndex3Simd4(a, tfSimd4fSplat(b));
}

inline Simd_FloatType4 tfSimd4fReplaceIndex0Simd4(Simd_FloatType4 a, Simd_FloatType4 b)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blend_ps(a, b, 0b0001);
#else
    return {b.v[0], a.v[1], a.v[2], a.v[3]};
#endif
}
inline Simd_FloatType4 tfSimd4fReplaceIndex1Simd4(Simd_FloatType4 a, Simd_FloatType4 b)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blend_ps(a, b, 0b0010);
#else
    return {a.v[0], b.v[1], a.v[2], a.v[3]};
#endif
}
inline Simd_FloatType4 tfSimd4fReplaceIndex2Simd4(Simd_FloatType4 a, Simd_FloatType4 b)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blend_ps(a, b, 0b0100);
#else
    return {a.v[0], a.v[1], b.v[2], a.v[3]};
#endif
}
inline Simd_FloatType4 tfSimd4fReplaceIndex3Simd4(Simd_FloatType4 a, Simd_FloatType4 b)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_blend_ps(a, b, 0b1000);
#else
    return {a.v[0], a.v[1], a.v[2], b.v[3]};
#endif
}

inline Simd_FloatType4 tfSimd4fLoadImmediate(float x, float y, float z, float w) {
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set_ps(w, z, y, x);
#else
    return { x, y, z, w };
#endif
}

inline Simd_FloatType tfSimd4fToSimd1f(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return value.v[0];
#endif
}

inline Simd_FloatType2 tfSimd4fToSimd2f(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1]};
#endif
}

inline Simd_FloatType3 tfSimd4fToSimd3f(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return value;
#else
    return {value.v[0], value.v[1], value.v[2]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex0(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0));
#else
  return {value.v[0],value.v[0],value.v[0],value.v[0]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex1(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(1, 1, 1, 1));
#else
  return {value.v[1],value.v[1],value.v[1],value.v[1]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex2(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(2, 2, 2, 2));
#else
  return {value.v[2],value.v[2],value.v[2],value.v[2]};
#endif
}

inline Simd_FloatType4 tfSimd4fSplatIndex3(Simd_FloatType4 value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_shuffle_ps(value, value, _MM_SHUFFLE(3, 3, 3, 3));
#else
  return {value.v[3],value.v[3],value.v[3],value.v[3]};
#endif
}

//float tfSimd4fSelectIndex0(Simd_FloatType4 value) { 
//  return _mm_shuffle_ps(value, value, _MM_SHUFFLE(0, 0, 0, 0)); 
//}
//float tfSimd4fSelectIndex1(Simd_FloatType4 value){}
//float tfSimd4fSelectIndex2(Simd_FloatType4 value){}
//float tfSimd4fSelectIndex3(Simd_FloatType4 value){}

inline Simd_Int32Type4 tfSimd4iSplat(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}

inline Simd_FloatType4 tfSimd4fSplat(float value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_ps(value);
#else
    return { value, value, value, value };
#endif
}

inline Simd_Int32Type4 tfSimdSplat4i(int32_t value)
{
#if defined(TF_FEATURE_CPU_SSE)
    return _mm_set1_epi32(value);
#else
    return { value, value, value, value };
#endif
}
