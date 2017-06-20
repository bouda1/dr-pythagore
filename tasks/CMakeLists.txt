SET(tasks_SRC
    checkequaldistinct.cpp checkequaldistinct.h
    checklinesequality.cpp checklinesequality.h
    tasklua.cpp tasklua.h
    )

ADD_LIBRARY(tasks STATIC
    ${tasks_SRC}
    )

TARGET_LINK_LIBRARIES(tasks pool ${LUA_LIBRARIES})
