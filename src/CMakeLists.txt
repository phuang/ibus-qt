project(ibus-qt)

include(${QT_USE_FILE})

set(
    ibus_qt_SRCS
    ibus.cpp
    qibusobject.cpp
    qibusserializable.cpp
    qibusattribute.cpp
    qibustext.cpp
    qibusconnection.cpp
    qibusibus_adaptor.cpp
    qibusdbus_adaptor.cpp
    qibusinputcontext.cpp
)

set(
    ibus_qt_MOC_HDRS
    qibusobject.h
    qibusserializable.h
    qibusattribute.h
    qibustext.h
    qibusconnection.h
    qibusibus_adaptor.h
    qibusdbus_adaptor.h
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
)

target_link_libraries(
    ibus-qt
    ${QT_LIBRARIES}
    ${QT_QTDBUS_LIBRARIES}
)
