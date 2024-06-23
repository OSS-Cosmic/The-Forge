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


function(tf_fsl_compile target)
    IF(CMAKE_SYSTEM_NAME MATCHES "Windows")
        add_custom_command(
            TARGET ${target}
            MAIN_DEPENDENCY
            COMMAND ${CMAKE_COMMAND} -E env  "python3" "${FSL_COMPILER_PY}"
            -l DIRECT3D12 
            -d "$<TARGET_FILE_DIR:${target}>/Shaders"
            --verbose 
            -b  "$<TARGET_FILE_DIR:${target}>/CompiledShaders"
            --incremental 
           ${ARGN} 
        )
    else()
        add_custom_command(
            TARGET ${target}
            MAIN_DEPENDENCY
            COMMAND ${CMAKE_COMMAND} -E env "VULKAN_SDK=$ENV{VULKAN_SDK}" "python3" "${FSL_COMPILER_PY}"
            -l VULKAN 
            -d "$<TARGET_FILE_DIR:${target}>/Shaders"
            --verbose 
            -b  "$<TARGET_FILE_DIR:${target}>/CompiledShaders"
            --incremental 
            ${ARGN} 
        )
    endif()
endfunction()
macro(tf_prepare_resources target) 
    tf_fsl_compile(${target} 
      --compile "${RESOURCES_DIR}/UI/Shaders/FSL/UI_ShaderList.fsl" ) 
    tf_fsl_compile(${target} 
      --compile "${RESOURCES_DIR}/Fonts/Shaders/FSL/Fonts_ShaderList.fsl" ) 
endmacro()


# --compile ${_SHADER_RESOURCE_PATH_}/ShaderList.fsl

