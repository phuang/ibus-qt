cmake_minimum_required(VERSION 2.4)

project(ibus-qt)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# CPack configure
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
set(CPACK_SOURCE_IGNORE_FILES
    "/\\\\.git/"
    "\\\\.gitignore$"
    "/CMakeFiles/"
    "/_CPack_Packages/"
    "\\\\.cmake$"
    "CMakeCache.txt$"
    "install_manifest.txt$"
    "Makefile$"
    "Source\\\\.tar\\\\.gz$"
    "Linux\\\\.tar\\\\.gz$"
    "moc_.*\\\\.cxx$"
    "\\\\.so$"
    "ibus-test$"
)

include(CPack)

# sub dirs
add_subdirectory(src)
add_subdirectory(qtim)
