# check qt
find_package(Qt4 COMPONENTS QtCore QtDBus REQUIRED)
include(${QT_USE_FILE})

# check dbus
find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)

include_directories(
    ${QT_INCLUDE_DIRS}
    ${DBUS_INCLUDE_DIRS}
)

link_directories(
    ${QT_LIBRARY_DIRS}
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

add_executable(
    ibus-test
    ibus.cpp
)

target_link_libraries(
    ibus-qt
    ${QT_LIBRARIES}
    ${DBUS_LIBRARIES}
)

target_link_libraries(
    ibus-test
    ibus-qt
)

install(TARGETS ibus-qt
    LIBRARY DESTINATION lib)
install(TARGETS ibus-test
    RUNTIME DESTINATION bin)
