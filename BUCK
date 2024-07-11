
load("//:rules.bzl", "fsl_build")
load("@prelude//paths.bzl", "paths")
load("@prelude//third-party:pkgconfig.bzl", "external_pkgconfig_library")

export_file(
    name = "fsl",
    mode = "reference",
    src = "Common_3/Tools/ForgeShadingLanguage/fsl.py",
    visibility = ["PUBLIC"],
)

export_file(
    name = "UI_ShaderList",
    mode = "reference",
    src = "Resources/UI/Shaders/FSL/UI_ShaderList.fsl",
    visibility = ['PUBLIC']
)

export_file(
    name = "Font_ShaderList",
    mode = "reference",
    src = "Resources/Fonts/Shaders/FSL/Fonts_ShaderList.fsl",
    visibility = ['PUBLIC']
)
#fsl_build(
#    name = "font_fsl",
#    input = "Resources/UI/Shaders/FSL/Fonts_ShaderList.fsl",
#    visibility = ['PUBLIC']
#)

external_pkgconfig_library(name = "gtk+-3.0")
external_pkgconfig_library(name = "libudev")
external_pkgconfig_library(name = "x11")
external_pkgconfig_library(name = "xrandr")

cxx_library(
    name = "TF",
    srcs = glob([
      "Common_3/Graphics/*.cpp",
      "Common_3/Application/*.cpp",
      "Common_3/Application/Profiler/*.cpp",
      "Common_3/Application/Fonts/FontSystem.cpp",
      "Common_3/Application/UI/UI.cpp",
      "Common_3/Application/Profiler/*.cpp",
      "Common_3/Application/InputSystem.cpp",
      "Common_3/OS/WindowSystem/*.cpp",
      "Common_3/OS/*.cpp",
      "Common_3/Resources/ResourceLoader/*.cpp",

      "Common_3/Graphics/ThirdParty/OpenSource/SPIRV_Cross/*.cpp",

      "Common_3/Utilities/FileSystem/FileSystem.c",
      "Common_3/Utilities/FileSystem/SystemRun.c",
      "Common_3/Utilities/Log/*.c",
      "Common_3/Utilities/Math/*.c",
      "Common_3/Utilities/MemoryTracking/*.c",
      "Common_3/Utilities/Threading/*.c",
      "Common_3/Utilities/*.c",

      "Common_3/Tools/Network/*.c",
      "Common_3/Tools/ReloadServer/*.cpp",

      "Common_3/Renderer/ShaderServer/Network.c",
      "Common_3/Renderer/ShaderServer/ShaderServer.cpp",

      "Common_3/Utilities/ThirdParty/OpenSource/bstrlib/bstrlib.c",
      "Common_3/Tools/ThirdParty/OpenSource/meshoptimizer/src/*.cpp",

      "Source/Forge/Core/TF_String.cpp",
      "Source/Forge/Core/TF_Core.cpp",
      "Source/Forge/Core/Mem/TF_Allocators.cpp",

      "Source/Forge/Graphics/TF_GPUConfig.cpp",
      "Source/Forge/Graphics/TF_Graphics.cpp",
      "Source/Forge/Graphics/Vulkan/Vulkan.cpp",
      "Source/Forge/Graphics/Vulkan/VulkanRaytracing.cpp",
      "Source/Forge/Graphics/Vulkan/VulkanShaderReflection.cpp",
      # lz4 
      "Common_3/Utilities/ThirdParty/OpenSource/lz4/lz4.c",
      "Common_3/Utilities/ThirdParty/OpenSource/lz4/lz4hc.c",
       
      # ga input 
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/builtin/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/dev/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/gestures/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/keyboard/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/mouse/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/pad/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/recorder/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/touch/*.cpp",
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/hid/*.cpp",   
      "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/hid/hidparsers/*.cpp",   
      
      # cpu features
      "Common_3/OS/ThirdParty/OpenSource/cpu_features/src/impl_x86_macos.c",
      "Common_3/OS/ThirdParty/OpenSource/cpu_features/src/impl_aarch64_iOS.c",
      "Common_3/OS/ThirdParty/OpenSource/cpu_features/src/impl_x86_windows.c",
      "Common_3/OS/ThirdParty/OpenSource/cpu_features/src/impl_x86_linux_or_android.c",
      "Common_3/Graphics/*.cpp",
      
      # imgui 
      "Common_3/Application/ThirdParty/OpenSource/imgui/*.cpp",

     "Common_3/Utilities/ThirdParty/OpenSource/zstd/common/*.c",
     "Common_3/Utilities/ThirdParty/OpenSource/zstd/compress/*.c",
     "Common_3/Utilities/ThirdParty/OpenSource/zstd/decompress/*.c"
  ]) + select({
        "config//os:macos": [

        ],
        "config//os:linux": glob([
          "Common_3/Utilities/ThirdParty/OpenSource/zstd/decompress/huf_decompress_amd64.S",
          "Common_3/OS/Linux/*.cpp",
          "Common_3/OS/Linux/*.c",
          "Common_3/Utilities/FileSystem/UnixFileSystem.c",
          "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/hidapi/linux/*.c"
        ]),
        "config//os:windows": [

        ] + glob([
          "Common_3/OS/Windows/*.cpp",
          "Common_3/OS/Windows/*.c",

          "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/hidapi/windows/*.c",
          "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/hid/*.cpp",
          "Common_3/Application/ThirdParty/OpenSource/gainput/lib/source/gainput/hid/hidparsers/*.cpp",


        ])
    }),
    preprocessor_flags = [ 
    ],
    deps = [
      "//:gtk+-3.0",
      "//:libudev",
      "//:x11",
      "//:xrandr"
    ],
    #linker_flags = select({
    #  # "config//os:linux": ["-lX11", "-lXrandr", "-ludev"]
    #}),
    exported_headers =
      { file: file for file in glob(["Common_3/**/*.h", "Common_3/**/*.hpp","Common_3/Graphics/ThirdParty/OpenSource/volk/*.c" ]) } |
      { paths.relativize(file, "Include"): file for file in glob(["Include/**/*.h", "Include/**/*.hpp"]) } |  
      { paths.relativize(file, "External"): file for file in glob(["External/tinyimageformat/*.h"]) } | 
      { paths.relativize(file, "External"): file for file in glob(["External/stb/*.h"]) } ,
    visibility = ["PUBLIC"],
)

