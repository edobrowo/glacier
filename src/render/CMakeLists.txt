add_subdirectory(material)
add_subdirectory(primitive)

file(GLOB SRC "*.cpp")
add_library(render STATIC ${SRC})
target_include_directories(render PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(render PUBLIC primitive scene ${LIBRARIES})
