INCLUDE_DIRECTORIES(../tasks)

set(OBJ_SRC
    plane.cpp plane.h
    element.cpp element.h
    point.cpp point.h
    set.cpp set.h
    line.cpp line.h
    segment.cpp segment.h
    )

ADD_LIBRARY(elements STATIC ${OBJ_SRC})

TARGET_LINK_LIBRARIES(elements tasks)
