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
    qibusenginedesc.cpp
    qibuscomponent.cpp
    qibusconnection.cpp
    qibusibusadaptor.cpp
    qibusdbusadaptor.cpp
    qibusbus.cpp
    qibusinputcontext.cpp
    ibus.cpp
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
    qibusenginedesc.h
    qibuscomponent.h
    qibusconnection.h
    qibusibusadaptor.h
    qibusdbusadaptor.h
    qibusbus.h
    qibusinputcontext.h
)

qt4_automoc(${ibus_qt_SRCS})
qt4_wrap_cpp(
    ibus_qt_MOC_SRCS
    ${ibus_qt_MOC_HDRS}
)

add_executable(
    ibus-qt
    ${ibus_qt_SRCS}
    ${ibus_qt_MOC_SRCS}
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
