project(ibus-qt)

include(${QT_USE_FILE})

set(
    ibus_qt_SRCS
    qibusobject.cpp
    qibusserializable.cpp
    qibusattribute.cpp
    qibusattrlist.cpp
    qibusproperty.cpp
    qibusproplist.cpp
    qibustext.cpp
    qibuslookuptable.cpp
    qibusenginedesc.cpp
    qibuscomponent.cpp
    qibusibusproxy.cpp
    qibusdbusproxy.cpp
    qibusinputcontextproxy.cpp
    qibusbus.cpp
    qibusinputcontext.cpp
)

set(
    ibus_qt_MOC_HDRS
    qibusobject.h
    qibusserializable.h
    qibusattribute.h
    qibusattrlist.h
    qibusproperty.h
    qibusproplist.h
    qibustext.h
    qibuslookuptable.h
    qibusenginedesc.h
    qibuscomponent.h
    qibusibusproxy.h
    qibusdbusproxy.h
    qibusinputcontextproxy.h
    qibusbus.h
    qibusinputcontext.h
)

qt4_automoc(${ibus_qt_SRCS})
qt4_wrap_cpp(
    ibus_qt_MOC_SRCS
    ${ibus_qt_MOC_HDRS}
)

add_library(
    ibus-qt
    SHARED
    ${ibus_qt_SRCS}
    ${ibus_qt_MOC_SRCS}
)

add_executable(
    ibus-test
    ibus.cpp
)

include_directories(
    ${QT_INCLUDE_DIR}
    ${QT_QTDBUS_INCLUDE_DIR}
    ${DBUS_INCLUDE_DIRS}
)

target_link_libraries(
    ibus-qt
    ${QT_LIBRARIES}
    ${QT_QTDBUS_LIBRARIES}
    ${DBUS_LIBRARIES}
)


target_link_libraries(
    ibus-test
    ibus-qt
)

install(TARGETS ibus-test DESTINATION bin)
install(TARGETS ibus-qt DESTINATION lib)
