INCLUDE_DIRECTORIES(../tasks)

set(BOOL_SRC
    boolExpr.h boolExpr.cpp
    simpleExpr.cpp simpleExpr.h
    treeBoolExpr.cpp treeBoolExpr.h
    notBoolExpr.cpp notBoolExpr.h
    andBoolExpr.cpp andBoolExpr.h
    orBoolExpr.cpp orBoolExpr.h
    boolTable.cpp boolTable.h
    )

ADD_LIBRARY(bool STATIC ${BOOL_SRC})

#TARGET_LINK_LIBRARIES(bool)
