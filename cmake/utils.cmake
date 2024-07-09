macro(tf_set_output_dir name dir)
    foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIGUPPERCASE)
        set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIGUPPERCASE} ${CMAKE_HOME_DIRECTORY}/build/${OUTPUTCONFIG}/${dir})
        set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIGUPPERCASE} ${CMAKE_HOME_DIRECTORY}/build/${OUTPUTCONFIG}/${dir})
        set_target_properties(${name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIGUPPERCASE} ${CMAKE_HOME_DIRECTORY}/build/${OUTPUTCONFIG}/${dir})
    endforeach()

    set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/${dir})
    set_target_properties(${name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/${dir})
    set_target_properties(${name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/${dir})
endmacro()


function(tf_fsl_compile target API)
    add_custom_command(
        TARGET ${target}
        MAIN_DEPENDENCY
        COMMAND ${CMAKE_COMMAND} -E env  "python3" "${FSL_COMPILER_PY}"
         -l ${API} 
        -d "$<TARGET_FILE_DIR:${target}>/Shaders"
        --verbose 
        -b  "$<TARGET_FILE_DIR:${target}>/CompiledShaders"
        --incremental 
        ${ARGN})
endfunction()

macro(tf_configure target) 
    if (WIN32)
      add_custom_command( TARGET 01_Transformations POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:01_Transformations> $<TARGET_FILE_DIR:01_Transformations>
  
        # Direct3d12AgilitySDK
        COMMAND ${CMAKE_COMMAND} -E copy ${THE_FORGE_ROOT}/Common_3/Graphics/ThirdParty/OpenSource/Direct3d12Agility/bin/x64/D3D12Core.dll $<TARGET_FILE_DIR:01_Transformations>
        COMMAND ${CMAKE_COMMAND} -E copy  ${THE_FORGE_ROOT}/Common_3/Graphics/ThirdParty/OpenSource/Direct3d12Agility/bin/x64/d3d12SDKLayers.dll $<TARGET_FILE_DIR:01_Transformations>
        
        COMMAND_EXPAND_LISTS
      )
      tf_fsl_compile(${target} 
          DIRECT3D11
          --compile "${RESOURCES_DIR}/UI/Shaders/FSL/UI_ShaderList.fsl" ) 
      tf_fsl_compile(${target} 
          DIRECT3D11
          --compile "${RESOURCES_DIR}/Fonts/Shaders/FSL/Fonts_ShaderList.fsl" )

      tf_fsl_compile(${target} 
          DIRECT3D12
          --compile "${RESOURCES_DIR}/UI/Shaders/FSL/UI_ShaderList.fsl" ) 
      tf_fsl_compile(${target} 
          DIRECT3D12
          --compile "${RESOURCES_DIR}/Fonts/Shaders/FSL/Fonts_ShaderList.fsl" )
    elseif(UNIX)
    
      tf_fsl_compile(${target} 
          VULKAN
          --compile "${RESOURCES_DIR}/UI/Shaders/FSL/UI_ShaderList.fsl" ) 
      tf_fsl_compile(${target} 
          VULKAN
          --compile "${RESOURCES_DIR}/Fonts/Shaders/FSL/Fonts_ShaderList.fsl" )

    endif ()

   
endmacro()


# --compile ${_SHADER_RESOURCE_PATH_}/ShaderList.fsl

