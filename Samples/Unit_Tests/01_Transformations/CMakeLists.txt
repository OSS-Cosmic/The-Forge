add_executable(01_Transformations 01_Transformations.cpp)
target_link_libraries(01_Transformations TF)
tf_set_output_dir(01_Transformations "Unit_Tests/01_Transformations") 

add_custom_command ( TARGET 01_Transformations  POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/GPUCfg/gpu.cfg $<TARGET_FILE_DIR:01_Transformations>/GPUCfg/gpu.cfg
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RESOURCES_DIR}/GPUData/pc_gpu.data $<TARGET_FILE_DIR:01_Transformations>/GPUCfg/gpu.data
   COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:01_Transformations>/Textures 

   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/circlepad.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/colorPalette.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/curlNoise.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/environment_sky.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/grid.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/LA_Helipad3D.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Palette_Fire.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Palette_Muted.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Palette_Purple.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Palette_Rainbow.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Palette_Sky.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/rect.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Skybox_back6.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Skybox_bottom4.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Skybox_front5.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Skybox_left2.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Skybox_right1.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Skybox_top3.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/sprites.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Stormtrooper_D.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/test_224x116_IYUV.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/test_image.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/TheForge.tex $<TARGET_FILE_DIR:01_Transformations>/Textures
   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Textures/dds/Warehouse-with-lights.tex $<TARGET_FILE_DIR:01_Transformations>/Textures

   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${TF_SAMPLE_MEDIA}/UnitTestResources/Fonts $<TARGET_FILE_DIR:01_Transformations>/Fonts
)


IF(WIN32)

    tf_fsl_compile(01_Transformations DIRECT3D12
      --compile "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/FSL/ShaderList.fsl") 
    tf_fsl_compile(01_Transformations DIRECT3D11 
      --compile "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/FSL/ShaderList.fsl") 
elseif(UNIX)
    
    tf_fsl_compile(01_Transformations VULKAN
      --compile "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/FSL/ShaderList.fsl") 
    tf_fsl_compile(01_Transformations VULKAN
      --compile "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/FSL/ShaderList.fsl")

endif()

tf_configure(01_Transformations) 




