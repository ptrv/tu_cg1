cmake_minimum_required(VERSION 2.8)
project(cg1_ex)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaulting to \"Release\"")
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -DDEBUG -D_DEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

find_package(GLUT)
find_package(OpenGL)

include_directories(${GLUT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

set(cg1_ex1_SOURCE
  cg1_ex1.cpp
  context.cpp
  node.cpp
  robot.cpp
  scenegraph.cpp
  )

set(cg1_ex1_HEADERS
  context.h
  node.h
  robot.h
  scenegraph.h
  )

add_executable(cg1_ex1 ${cg1_ex1_SOURCE} ${cg1_ex1_HEADERS})
target_link_libraries(cg1_ex1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
