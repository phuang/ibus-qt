# project(ibus-qt)
# 
# check qt
find_package(Qt4 COMPONENTS QtCore QtGui QtDBus REQUIRED)
include(${QT_USE_FILE})

set(
    qtim_ibus_SRCS
    ibus-input-context.cpp
)

set(
    qtim_ibus_MOC_HDRS
    ibus-input-context.h
)

QT4_AUTOMOC(${qtim_ibus_SRCS})
QT4_WRAP_CPP(
    qtim_ibus_MOC_SRCS
    ${qtim_ibus_MOC_HDRS}
)

include_directories(
    ${QT_INCLUDE_DIR}
    ${DBUS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_library(
    qtim-ibus
    MODULE
    ibus-plugin.cpp
    ${qtim_ibus_SRCS}
    ${qtim_ibus_MOC_SRCS}
)

target_link_libraries(
    qtim-ibus
    ibus-qt
)

install(TARGETS qtim-ibus
    LIBRARY DESTINATION ${QT_PLUGINS_DIR}/inputmethods)
