pybind11_add_module(glacier glacier.cpp)

target_include_directories(glacier PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Set output library directory.
set_target_properties(glacier PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

target_link_libraries(glacier PUBLIC render scene primitive material ${LIBRARIES})
