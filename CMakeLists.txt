cmake_minimum_required(VERSION 3.23)
project(GraficaPeCalc)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw glm::glm GLEW::GLEW)