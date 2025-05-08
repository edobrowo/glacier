file(GLOB SRC "*.cpp")
add_library(scene STATIC ${SRC})
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/src/scene)
target_link_libraries(scene PUBLIC geometry ${LIBRARIES})
