add_subdirectory(util)
add_subdirectory(math)

file(GLOB SRC "*.cpp")
add_executable(Glacier ${SRC})
target_link_libraries(Glacier PRIVATE math util ${LIBRARIES})
target_include_directories(Glacier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
