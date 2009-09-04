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
    test_engine_SRCS
    main.cpp
)

set(
    test_engine_MOC_HDRS
)

QT4_AUTOMOC(${test_engine_SRCS})
QT4_WRAP_CPP(
    _MOC_SRCS
    ${test_engine_MOC_HDRS}
)

add_executable(
    test-engine
    ${test_engine_SRCS}
    ${test_engine_MOC_SRCS}
)

target_link_libraries(
    test-engine
    debug ${QT_QTGUI_LIBRARY_DEBUG}
    optimized ${QT_QTGUI_LIBRARY_RELEASE}
    ${ICU_LIBRARIES}
    ibus-qt
)
