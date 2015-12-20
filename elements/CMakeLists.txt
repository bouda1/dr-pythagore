set(OBJ_SRC
    dpplan.cpp dpplan.h
    dpelement.cpp dpelement.h
    dppoint.cpp dppoint.h
    dpset.cpp dpset.h
    dpline.cpp dpline.h
    dpsegment.cpp dpsegment.h
    )

ADD_LIBRARY(dpelements STATIC ${OBJ_SRC})

TARGET_LINK_LIBRARIES(dpelements)
