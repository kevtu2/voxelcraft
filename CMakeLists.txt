cmake_minimum_required(VERSION 3.31)

project(voxelcraft)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("lib/glfw")
add_subdirectory("lib/glm")

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE HDR_FILES CONFIGURE_DEPENDS src/*.hpp)

file(GLOB IMGUI_SRC 
	lib/imgui/*.cpp
	lib/imgui/*.h
)

set(IMGUI_BACKENDS
	lib/imgui/backends/imgui_impl_opengl3.cpp
	lib/imgui/backends/imgui_impl_glfw.cpp
)

set(GLOB IMGUI_STRING
	lib/imgui/misc/cpp/imgui_stdlib.*
)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HDR_FILES} lib/glad/src/glad.c)

if (MSVC)
	target_sources(${PROJECT_NAME} PRIVATE lib/imgui/misc/debuggers/imgui.natvis)
endif()

add_library(imgui STATIC
	${IMGUI_SRC}
	${IMGUI_BACKENDS}
	${IMGUI_STRING}
)

target_include_directories(imgui PUBLIC
	lib/imgui
	lib/imgui/backends
	lib/glfw/include
)

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
	imgui
)

target_link_libraries(${PROJECT_NAME} PUBLIC atomic)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
