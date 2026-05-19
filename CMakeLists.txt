cmake_minimum_required(VERSION 3.16)
project(FlapChud)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(glfw)

add_executable(FlapChud
    main.cpp                   
    vendor/glad/src/glad.c
    "bird.h" "pipe.h" "renderer.h" "renderer.cpp" "game.h" "game.cpp" )

target_include_directories(FlapChud PRIVATE
    ${CMAKE_SOURCE_DIR}        
    vendor/glad/include
)

target_link_libraries(FlapChud PRIVATE glfw)
target_link_libraries(FlapChud PRIVATE glm::glm)
target_link_libraries(FlapChud PRIVATE OpenGL::GL)