#INCLUDE_DIRECTORIES(../tasks)

set(RULES_SRC
    rule.cpp rule.h
    )

ADD_LIBRARY(rules STATIC ${RULES_SRC})

SET(LUA_SCRIPTS
    aligned.lua
    distinct.lua
    equals.lua
    notaligned.lua
    )

FOREACH (F ${LUA_SCRIPTS})
    FILE(COPY "${F}" DESTINATION "${CMAKE_BINARY_DIR}")
ENDFOREACH ()
