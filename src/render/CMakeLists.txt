file(GLOB SRC "*.cpp")
add_library(render STATIC ${SRC})
target_include_directories(render PUBLIC ${CMAKE_SOURCE_DIR}/src/render)
target_link_libraries(render PUBLIC primitive ${LIBRARIES})
