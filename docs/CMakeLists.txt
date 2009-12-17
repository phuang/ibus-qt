add_custom_target(docs
    COMMAND ${DOXYGEN_EXECUTABLE}
    SOURCES Doxyfile
    )
