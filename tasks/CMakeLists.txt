SET(tasks_SRC
    checkequaldistinct.cpp checkequaldistinct.h
    checklinesequality.cpp checklinesequality.h
    tasklua.cpp tasklua.h
    plane_binding.cpp plane_binding.h
    )

ADD_LIBRARY(tasks STATIC
    ${tasks_SRC}
    )

TARGET_LINK_LIBRARIES(tasks pool ${LUA_LIBRARIES})

SET(LUA_SCRIPTS
    check_aligned.lua
    )

FILE(COPY "${LUA_SCRIPTS}" DESTINATION "${CMAKE_BINARY_DIR}")

