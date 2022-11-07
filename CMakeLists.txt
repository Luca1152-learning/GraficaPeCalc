cmake_minimum_required(VERSION 3.23)
project(GraficaPeCalc)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp src/utils/render/ShadersUtils.cpp src/utils/render/ShadersUtils.h src/drawable/House.cpp src/drawable/House.h src/utils/color/Color.cpp src/utils/color/Color.h src/utils/Constants.h src/utils/Constants.cpp src/drawable/Drawable.cpp src/drawable/Drawable.h src/utils/color/Colors.cpp src/utils/color/Colors.h src/utils/math/Vector.cpp src/utils/math/Vector.h src/utils/math/Matrix.cpp src/utils/math/Matrix.h src/drawable/Circle.cpp src/drawable/Circle.h src/drawable/sun/Sun.cpp src/drawable/sun/Sun.h src/drawable/sun/SunRays.cpp src/drawable/sun/SunRays.h src/drawable/sun/SunRay.cpp src/drawable/sun/SunRay.h src/drawable/Tree.cpp src/drawable/Tree.h src/drawable/Hills.cpp src/drawable/Hills.h)

find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_link_libraries(${PROJECT_NAME} glfw glm::glm GLEW::GLEW)