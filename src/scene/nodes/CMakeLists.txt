file(GLOB SRC "*.cpp")
add_library(scene_nodes STATIC ${SRC})
target_include_directories(scene_nodes PUBLIC ${CMAKE_SOURCE_DIR}/src/scene/nodes)
target_link_libraries(scene_nodes PUBLIC geometry ${LIBRARIES})
