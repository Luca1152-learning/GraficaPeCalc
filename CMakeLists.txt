cmake_minimum_required(VERSION 3.23)
project(GraficaPeCalc)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp src/utils/ShadersUtils.cpp src/utils/ShadersUtils.h src/drawable/House.cpp src/drawable/House.h src/utils/Color.cpp src/utils/Color.h src/utils/Constants.h src/utils/Constants.cpp src/drawable/Drawable.cpp src/drawable/Drawable.h src/utils/Colors.cpp src/utils/Colors.h src/utils/Vector.cpp src/utils/Vector.h src/utils/Matrix.cpp src/utils/Matrix.h)

find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw glm::glm GLEW::GLEW)