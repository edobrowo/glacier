file(GLOB SRC "*.cpp")
add_library(material STATIC ${SRC})
target_include_directories(material PUBLIC ${CMAKE_SOURCE_DIR}/src/render)
target_link_libraries(material PUBLIC math ${LIBRARIES})
