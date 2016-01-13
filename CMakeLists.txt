CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)
PROJECT(DR-PYTHAGORE)

OPTION(SANITIZE "Set this variable to ON to check memory allocations" OFF)
OPTION(TSANITIZE "Set this variable to ON to check threads" OFF)
OPTION(COVERAGE "Set this variable to ON to check coverage of tests" OFF)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

FIND_PACKAGE(Readline REQUIRED)
FIND_PACKAGE(CPPUNIT REQUIRED)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} elements parser pool ${Readline_INCLUDE_DIR})

IF(COVERAGE)
    SET(COVERAGE_CXXFLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_BUILD_TYPE "Debug")
    INCLUDE(CodeCoverage)
ENDIF()

IF (TSANITIZE)
    SET(TSANITIZE_CXXFLAGS "-g -O0 -fsanitize=thread -fno-omit-frame-pointer")
    SET(CMAKE_BUILD_TYPE "Debug")
ENDIF ()

IF (SANITIZE)
    SET(SANITIZE_CXXFLAGS "-g -O0 -fsanitize=address -fno-omit-frame-pointer")
    SET(CMAKE_BUILD_TYPE "Debug")
ENDIF ()

SET(CMAKE_CXX_FLAGS "${COVERAGE_CXXFLAGS} ${TSANITIZE_CXXFLAGS} ${SANITIZE_CXXFLAGS} -std=c++11")
ADD_SUBDIRECTORY(lemon)
ADD_SUBDIRECTORY(parser)
ADD_SUBDIRECTORY(elements)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(pool)
ADD_SUBDIRECTORY(tasks)

SET(DP_SRC
    drpythagore.cpp
    )

ADD_EXECUTABLE(drpythagore
    ${DP_SRC})

SET_PROPERTY(TARGET drpythagore PROPERTY CXX_STANDARD_REQUIRED ON)

TARGET_LINK_LIBRARIES(drpythagore elements parser pool ${Readline_LIBRARY})

ENABLE_TESTING()

ADD_TEST(basic tests/test-dr-pythagore)
