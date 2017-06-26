
set (POOL_SRC
    stack.cpp stack.h
    action.cpp action.h
    task.cpp task.h
    plane_binding.cpp plane_binding.h
    )

ADD_LIBRARY(stack STATIC
    ${POOL_SRC})

TARGET_LINK_LIBRARIES(stack -lpthread)
