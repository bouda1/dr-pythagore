
set (POOL_SRC
    pool.cpp pool.h
    action.cpp action.h
    task.cpp task.h
    )

ADD_EXECUTABLE(pool
    ${POOL_SRC})

TARGET_LINK_LIBRARIES(pool -lpthread)
