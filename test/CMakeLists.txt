include_directories(
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTDBUS_INCLUDE_DIR}
    ${DBUS_INCLUDE_DIRS}
    ${IBUS_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

link_directories(
    ${DBUS_LIBRARY_DIRS}
    ${ICU_LIBRARY_DIRS}
)

set(
    demo_engine_SRCS
    qibusdemoengine.cpp
    main.cpp
)

set(
    demo_engine_MOC_HDRS
    qibusdemoengine.h
)

QT4_AUTOMOC(${demo_engine_SRCS})
QT4_WRAP_CPP(
    demo_engine_MOC_SRCS
    ${demo_engine_MOC_HDRS}
)

add_executable(
    demo-engine
    ${demo_engine_SRCS}
    ${demo_engine_MOC_SRCS}
)

target_link_libraries(
    demo-engine
    debug ${QT_QTGUI_LIBRARY_DEBUG}
    optimized ${QT_QTGUI_LIBRARY_RELEASE}
    ${ICU_LIBRARIES}
    ibus-qt
)
