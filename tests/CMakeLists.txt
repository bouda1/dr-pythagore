INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
SET(src_test
        test_all.cpp
        test_boolExpr.cpp
        test_lexer.cpp
        )
ADD_EXECUTABLE(test-dr-pythagore
        ${src_test})

TARGET_LINK_LIBRARIES(test-dr-pythagore elements bool parser stack ${GTEST_BOTH_LIBRARIES})

IF (COVERAGE)
    SETUP_TARGET_FOR_COVERAGE(test-coverage
        test-dr-pythagore
        coverage)
ENDIF()
