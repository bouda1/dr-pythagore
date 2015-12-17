CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)
PROJECT(DR-PYTHAGORE)

OPTION(SANITIZE "Set this variable to ON to check memory allocations" OFF)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} elements parser)

IF (SANITIZE)
    SET(SANITIZE_CFLAGS "-g -O0 -fsanitize=address -fno-omit-frame-pointer")
    SET(CMAKE_BUILD_TYPE "Debug")
ENDIF ()

SET(CMAKE_CXX_FLAGS "${SANITIZE_CFLAGS} -std=c++11")
ADD_SUBDIRECTORY(lemon)
ADD_SUBDIRECTORY(parser)
ADD_SUBDIRECTORY(elements)

SET(DP_SRC
    drpythagore.cpp
    )

ADD_EXECUTABLE(drpythagore
    ${DP_SRC})

SET_PROPERTY(TARGET drpythagore PROPERTY CXX_STANDARD_REQUIRED ON)
#SET_PROPERTY(TARGET drpythagore PROPERTY CXX_STANDARD 11)

TARGET_LINK_LIBRARIES(drpythagore dpelements dpparser)

