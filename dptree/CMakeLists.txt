set(DPTREE_SRC
    dptree.h
    assoc.cpp assoc.h
)

ADD_LIBRARY(dptree STATIC ${DPTREE_SRC})

TARGET_LINK_LIBRARIES(dptree elements)
