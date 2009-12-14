
install(DIRECTORY html
    DESTINATION share/ibus-qt/docs COMPONENT Docs)

add_custom_target(docs
    COMMAND ${DOXYGEN_EXECUTABLE}
    )
