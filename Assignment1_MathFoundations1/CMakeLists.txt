cmake_minimum_required(VERSION 3.8.0)

PROJECT(Assignment1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Core Gui OpenGL)

include_directories(
  ${QtWidget_INCLUDES}
  ${QtCore_INCLUDES}
  ${QtGui_INCLUDES}
  ${QtOpenGL_INCLUDES}
)

include_directories(
  include/
)

set(srcs
  src/main.cpp
)

add_executable(Assignment1
  ${srcs}
)
target_link_libraries(Core Qt5)
target_link_libraries(Assignment1)
