file(GLOB SRC "*.cpp")
add_library(geometry STATIC ${SRC})
target_include_directories(geometry PUBLIC ${CMAKE_SOURCE_DIR}/src/common)
target_link_libraries(geometry PUBLIC math ${LIBRARIES})
