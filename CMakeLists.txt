cmake_minimum_required(VERSION 3.31)

project(voxelcraft)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("lib/glfw")
add_subdirectory("lib/glm")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HDR_FILES CONFIGURE_DEPENDS src/*.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES} lib/glad/src/glad.c)

source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SRC_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Header Files" FILES ${HDR_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE 
	src
	lib/glad/include
	lib/glfw/include
	lib/glm
	lib/stb
	lib/FastNoiseLite
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	glfw
	glm::glm
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
