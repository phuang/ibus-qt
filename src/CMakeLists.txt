include_directories(
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTDBUS_INCLUDE_DIR}
    ${DBUS_INCLUDE_DIRS}
)

link_directories(
    ${DBUS_LIBRARY_DIRS}
)

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

# QT4_ADD_DBUS_INTERFACE(
#     ibus_qt_SRCS
#     ${CMAKE_CURRENT_SOURCE_DIR}/interfaces/org.freedesktop.IBus.xml
#     basename
# )
# 
# QT4_AUTOMOC(${ibus_qt_SRCS})
QT4_WRAP_CPP(
    ibus_qt_MOC_SRCS
    ${ibus_qt_MOC_HDRS}
)

add_library(
    ibus-qt
    SHARED
    ${ibus_qt_SRCS}
    ${ibus_qt_MOC_SRCS}
)

target_link_libraries(
    ibus-qt
    debug ${QT_QTCORE_LIBRARY_DEBUG}
    debug ${QT_QTDBUS_LIBRARY_DEBUG}
    optimized ${QT_QTCORE_LIBRARY_RELEASE}
    optimized ${QT_QTDBUS_LIBRARY_RELEASE}
    ${DBUS_LIBRARIES}
)

install(TARGETS ibus-qt
    LIBRARY DESTINATION ${LIBDIR})

# add_executable(
#     ibus-test
#     ibus.cpp
# )

# target_link_libraries(
#     ibus-test
#     ibus-qt
# )

# install(TARGETS ibus-test
#     RUNTIME DESTINATION bin)
