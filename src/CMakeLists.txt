add_subdirectory(common)
add_subdirectory(scene)
add_subdirectory(render)

# Python3 packages
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

file(GLOB SRC "*.cpp")
add_executable(Glacier ${SRC})
target_link_libraries(Glacier PRIVATE scene render material geometry ${LIBRARIES} ${Python3_LIBRARIES})
target_include_directories(Glacier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Python3_INCLUDE_DIRS})
