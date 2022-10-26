# Projects Settings
cmake_minimum_required(VERSION 3.1)
project(GC)

# The main executable
add_executable(${PROJECT_NAME}
        src/Application.cpp
        src/Application.cpp
        src/MyApplication.cpp
        src/MyApplication.cpp
        src/glError.hpp
        src/glError.cpp
        src/main.cpp
        src/Shader.hpp
        src/Shader.cpp
        src/loadShaders.h
        src/loadShaders.cpp
        )

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

INCLUDE_DIRECTORIES(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/freeglut/include")
LINK_DIRECTORIES(${PROJECT_NAME} "${CMAKE_CURRENT_SOURCE_DIR}/lib/freeglut/lib")

target_link_libraries(${PROJECT_NAME}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/freeglut/lib/freeglut.lib"
        PRIVATE glfw
        PRIVATE libglew_static
        PRIVATE glm
        )

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/asset.hpp.in
        ${CMAKE_CURRENT_BINARY_DIR}/src/asset.hpp
)
target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
        )

add_custom_target(copy-files ALL
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/freeglut/bin/freeglut.dll
        ${CMAKE_CURRENT_BINARY_DIR}/Debug
        )
