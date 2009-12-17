add_custom_target(docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE}
    SOURCES Doxyfile
    )
