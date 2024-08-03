math_utils_header = ["TF_MathUtils.h"]

def cxx_math_simd_test(name: str, srcs: list[str]):
  native.cxx_test(
    name = name,
    srcs = srcs,
    link_style = "static",
    deps = [
        "@tf//:TF",
        "@tf//tests:TF_utest"
    ],
    header_namespace = "",
    headers = math_utils_header,
    visibility = ['PUBLIC']
  )
  native.cxx_test(
    name = "{}_scalar".format(name),
    srcs = srcs,
    preprocessor_flags = [
      "-DTF_FEATURE_CPU_SCALAR=1"
    ],
    link_style = "static",
    deps = [
        "@tf//:TF",
        "@tf//tests:TF_utest"
    ],
    header_namespace = "",
    headers = math_utils_header,
    visibility = ['PUBLIC']
  )
