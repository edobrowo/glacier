add_subdirectory(nodes)
add_subdirectory(bindings)

file(GLOB SRC "*.cpp")
add_library(scene STATIC ${SRC})
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/src/scene)
target_link_libraries(scene PUBLIC scene_nodes ${LIBRARIES})
