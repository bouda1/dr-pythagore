INCLUDE_DIRECTORIES(../tasks)

set(BOOL_SRC
    boolExpr.h boolExpr.cpp
    simpleExpr.cpp simpleExpr.h
    treeBoolExpr.cpp treeBoolExpr.h
    )

ADD_LIBRARY(bool STATIC ${BOOL_SRC})

#TARGET_LINK_LIBRARIES(bool)
