#INCLUDE_DIRECTORIES(../tasks)

set(RULES_SRC
    rule.cpp rule.h
    )

ADD_LIBRARY(rules STATIC ${RULES_SRC})

SET(LUA_SCRIPTS
    aligned.lua
    )

FILE(COPY "${LUA_SCRIPTS}" DESTINATION "${CMAKE_BINARY_DIR}")

