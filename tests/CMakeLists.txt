INCLUDE_DIRECTORIES(${CPPUNIT_INCLUDE_DIR})
SET(src_test
        test-dr-pythagore.cpp
        )
ADD_EXECUTABLE(test-dr-pythagore
        test_lexer.cpp test_lexer.h
        test_task_checkequaldistinct.cpp test_task_checkequaldistinct.h
        ${src_test})

TARGET_LINK_LIBRARIES(test-dr-pythagore elements parser stack ${CPPUNIT_LIBRARY})

IF (COVERAGE)
    SETUP_TARGET_FOR_COVERAGE(test-coverage
        test-dr-pythagore
        coverage)
ENDIF()
