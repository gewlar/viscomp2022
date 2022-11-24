cmake_minimum_required(VERSION 3.14)

project(transformations)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

file(GLOB SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Helpers/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/Helpers/*.cpp
)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLUT
find_package(GLUT)
if(NOT GLUT_FOUND)
include(${CMAKE_CURRENT_LIST_DIR}/thirdparty/freeglut/CMakeLists.txt)
set(GLUT_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/thirdparty/freeglut/include)
set(GLUT_LIBRARIES freeglut_static)
endif(NOT GLUT_FOUND)
include_directories(${GLUT_INCLUDE_DIRS})

# GLee
set(GLee_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLee)
set(GLee_LIBRARIES ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLee/GLee.c)
include_directories(${GLee_INCLUDE_DIRS})

add_definitions(-DMAIN_DIR="${CMAKE_CURRENT_LIST_DIR}/")
	
add_executable(transformations ${SOURCES} ${GLee_LIBRARIES})

target_link_libraries(transformations ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
