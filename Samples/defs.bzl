load("@prelude//paths.bzl", "paths")

def common_unit_test_resources() -> dict[str, str]:
      return {paths.join("Textures",paths.basename(file)): file for file in glob(["TFSamples-Media/UnitTestResources/Textures/dds/*.tex"])} | \
             {paths.relativize(file,"TFSamples-Media/UnitTestResources"): file for file in glob(["TFSamples-Media/UnitTestResources/Fonts/**/*"])} 
