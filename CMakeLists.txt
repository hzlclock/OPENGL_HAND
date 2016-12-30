cmake_minimum_required(VERSION 3.6)
project(OpenGL_Gesture)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        application.cpp
        application.h
        gl_arcball.cpp
        gl_arcball.h
        gl_viewer.cpp
        gl_viewer.h
        main.cpp
        mat.h
        timer.cpp
        timer.h
        vec.h)

add_executable(OpenGL_Gesture ${SOURCE_FILES})

IF (APPLE)
    INCLUDE_DIRECTORIES(/System/Library/Frameworks)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(GLUT_LIBRARY GLUT)
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
    MARK_AS_ADVANCED(COCOA_LIBRARY
            GLUT_LIBRARY
            OpenGL_LIBRARY)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY} -lpng)
ENDIF (APPLE)

target_link_libraries(OpenGL_Gesture ${EXTRA_LIBS})