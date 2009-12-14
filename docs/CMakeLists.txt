install(DIRECTORY html
    DESTINATION share/doc/ibus-qt-docs-${CPACK_PACKAGE_VERSION}/html
    COMPONENT Docs)

install(DIRECTORY man/man3
    DESTINATION share/man
    COMPONENT Docs)

add_custom_target(docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE}
    )
