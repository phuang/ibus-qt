install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
    DESTINATION share/doc/ibus-qt-docs-${CPACK_PACKAGE_VERSION}
    COMPONENT Docs)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/man/man3
    DESTINATION share/man
    COMPONENT Docs)

add_custom_target(docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE}
    )
