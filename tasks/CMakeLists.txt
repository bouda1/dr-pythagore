SET(tasks_SRC
    checkequaldistinct.cpp checkequaldistinct.h
    checklinesequality.cpp checklinesequality.h
#    taskrule.cpp taskrule.h
    )

ADD_LIBRARY(tasks STATIC
    ${tasks_SRC}
    )

TARGET_LINK_LIBRARIES(tasks stack ${LUA_LIBRARIES})

#SET(LUA_SCRIPTS
#    check_aligned.lua
#    )
#
#FILE(COPY "${LUA_SCRIPTS}" DESTINATION "${CMAKE_BINARY_DIR}")

