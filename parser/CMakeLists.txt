ADD_CUSTOM_COMMAND(
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lexer.re
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp
        COMMAND ${RE2C_EXECUTABLE}
        -o ${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer.re
        COMMENT "Generating parser/lexer.cpp"
        )

ADD_CUSTOM_COMMAND(
  DEPENDS lemon ${CMAKE_CURRENT_SOURCE_DIR}/grammar.y
  COMMENT "Executing Lemon to generate parser grammar.c"
  COMMAND lemon
  T=${CMAKE_SOURCE_DIR}/lemon/lempar.c
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar.y
  COMMENT "Renaming grammar.c to grammar.cpp"
  COMMAND ${CMAKE_COMMAND}
  ARGS -E rename ${CMAKE_CURRENT_SOURCE_DIR}/grammar.c ${CMAKE_CURRENT_SOURCE_DIR}/grammar.cpp
  COMMAND sed -i 's/grammar\.c/grammar.cpp/g' ${CMAKE_CURRENT_SOURCE_DIR}/grammar.cpp
  COMMENT "Updating grammar.cpp"
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/grammar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar.h
)

SET(CMAKE_C_COMPILER ${CMAKE_CXX_COMPILER})

ADD_LIBRARY(parser STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/parsertoken.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/parsertoken.h
    ${CMAKE_CURRENT_SOURCE_DIR}/grammar.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/grammar.h
    ${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lexer.h
    )

SET_TARGET_PROPERTIES(parser PROPERTIES LINKER_LANGUAGE CXX)
TARGET_LINK_LIBRARIES(parser elements bool)
