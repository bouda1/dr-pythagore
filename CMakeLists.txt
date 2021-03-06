CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)
PROJECT(DR-PYTHAGORE)

OPTION(SANITIZE "Set this variable to ON to check memory allocations" OFF)
OPTION(TSANITIZE "Set this variable to ON to check threads" OFF)
OPTION(COVERAGE "Set this variable to ON to check coverage of tests" OFF)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeScripts)

FIND_PACKAGE(Readline REQUIRED)
FIND_PACKAGE(Lua REQUIRED)
FIND_PACKAGE(RE2C REQUIRED)

IF (LUA_VERSION_MAJOR STREQUAL "5" AND LUA_VERSION_MINOR STREQUAL "1")
    MESSAGE("LUA 51")
    ADD_DEFINITIONS(-DLUA51)
ENDIF()

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR} elements parser stack bool
    ${Readline_INCLUDE_DIR} ${LUA_INCLUDE_DIR} tasks)

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
ADD_SUBDIRECTORY(bool)
ADD_SUBDIRECTORY(lemon)
ADD_SUBDIRECTORY(parser)
ADD_SUBDIRECTORY(elements)
ADD_SUBDIRECTORY(stack)
ADD_SUBDIRECTORY(tasks)
#ADD_SUBDIRECTORY(rules)

SET(DP_SRC
    drpythagore.cpp
    )

ADD_EXECUTABLE(drpythagore
    ${DP_SRC})

SET_PROPERTY(TARGET drpythagore PROPERTY CXX_STANDARD_REQUIRED ON)

#TARGET_LINK_LIBRARIES(drpythagore bool elements parser stack rules
TARGET_LINK_LIBRARIES(drpythagore bool elements parser stack
    ${Readline_LIBRARY} ${LUA_LIBRARIES})

ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)

ADD_SUBDIRECTORY(tests)

ADD_TEST(tests tests/test-dr-pythagore)
