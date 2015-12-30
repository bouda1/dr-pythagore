SET(tasks_SRC
    checkequaldistinct.cpp checkequaldistinct.h
    )

ADD_LIBRARY(tasks STATIC
    ${tasks_SRC}
    )

TARGET_LINK_LIBRARIES(tasks pool)
