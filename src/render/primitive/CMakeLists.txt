file(GLOB SRC "*.cpp")
add_library(primitive STATIC ${SRC})
target_include_directories(primitive PUBLIC ${CMAKE_SOURCE_DIR}/src/render)
target_link_libraries(primitive PUBLIC math material ${LIBRARIES})
