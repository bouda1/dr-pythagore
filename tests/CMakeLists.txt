SET(src_test
        test-dr-pythagore.cpp
        )
ADD_EXECUTABLE(test-dr-pythagore
    ${src_test})

TARGET_LINK_LIBRARIES(test-dr-pythagore dpelements dpparser)

IF (COVERAGE)
    SETUP_TARGET_FOR_COVERAGE(test-coverage
        test-dr-pythagore
        coverage)
ENDIF()
