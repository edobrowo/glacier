pybind11_add_module(glacier glacier.cpp)

target_include_directories(glacier PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Set output library directory.
set_target_properties(glacier PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PYMODULE_OUTPUT_DIRECTORY}
)

target_link_libraries(glacier PUBLIC render scene primitive material ${LIBRARIES})

# Generate stubs using pybind11-stubgen.
add_custom_command(
    OUTPUT ${PYSTUBS_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${PYMODULE_OUTPUT_DIRECTORY} 
            pybind11-stubgen glacier
            --output-dir ${PYSTUBS_OUTPUT_DIRECTORY}
    DEPENDS glacier
    COMMENT "Generating Python stubs for glacier"
    VERBATIM
)

add_custom_target(glacier_stubs ALL
    DEPENDS ${PYSTUBS_OUTPUT_DIRECTORY}
)

add_dependencies(glacier_stubs glacier)
