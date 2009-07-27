cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


# ======
# Project information
project(ibus-qt)
set(AUTHORS "Peng Huang")
set(MAINTAINER "Peng Huang <shawn.p.huang at gmail dot com>")
set(VERSION_MAJOR "1")
set(VERSION_MINOR "2")
set(VERSION_PATCH "0")
set(VERSION_SNAPDATE "20090727")

# ======
# Requires
# check qt
find_package(Qt4 COMPONENTS QtCore QtGui QtDBus REQUIRED)
include(${QT_USE_FILE})
# check dbus
find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)

# ======
# CPack configure
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
if(NOT DEFINED VERSION_SNAPDATE)
  set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
else(NOT DEFINED VERSION_SNAPDATE)
  set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH}.${VERSION_SNAPDATE})
endif(NOT DEFINED  VERSION_SNAPDATE)
set(CPACK_SET_DESTDIR "ON")
set(CPACK_INSTALL_PREFIX "/usr")
set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")
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

# ======
# sub dirs
add_subdirectory(src)
add_subdirectory(qtim)
