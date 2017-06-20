#INCLUDE_DIRECTORIES(../tasks)

set(RULES_SRC
    rule.cpp rule.h
    )

ADD_LIBRARY(rules STATIC ${RULES_SRC})

#TARGET_LINK_LIBRARIES(elements tasks)
