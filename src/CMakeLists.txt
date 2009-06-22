project(ibus-qt)

include(${QT_USE_FILE})
set(ibus_qt_SRCS
    ibus.cpp
)

qt4_automoc(${ibus_qt_SRCS})

add_executable(ibus-qt ${ibus_qt_SRCS})
target_link_libraries(ibus-qt ${QT_LIBRARIES})
