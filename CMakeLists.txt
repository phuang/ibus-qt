cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# ======
# Project information
project(ibus-qt)
set(AUTHORS "Peng Huang")
set(MAINTAINER "Peng Huang <shawn.p.huang at gmail dot com>")
set(VERSION_MAJOR "1")
set(VERSION_MINOR "2")
set(VERSION_PATCH "0")
set(VERSION_SNAPDATE "20091014")
set(LIB_VERSION "1.2.0")
set(LIB_SOVERSION "1")

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
    "cmake_install.cmake"
    "CMakeCache.txt$"
    "install_manifest.txt$"
    "Makefile$"
    "Source\\\\.tar\\\\.gz$"
    "Linux\\\\.tar\\\\.gz$"
    "moc_.*\\\\.cxx$"
    "\\\\.so$"
    "\\\\.so\\\\.*"
    "ibus-test$"
    "/rpm/"
    "ibus-qt\\\\.spec$"
    "CPackSourceConfig\\\\.cmake$"
    "CPackConfig\\\\.cmake$"
)
include(CPack)
configure_file(ibus-qt.spec.in ibus-qt.spec)

# ======
# Requires
# check qt
find_package(Qt4 COMPONENTS QtCore QtGui QtDBus REQUIRED)
include(${QT_USE_FILE})
# check dbus
find_package(PkgConfig REQUIRED)
find_package(ICU REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)
pkg_check_modules(IBUS REQUIRED ibus-1.0)

# =====
# Define variables
if(NOT DEFINED LIBDIR)
    if( $ENV{MACHTYPE} MATCHES "64")
        set(LIBDIR lib64)
    else()
        set(LIBDIR lib)
    endif()
endif(NOT DEFINED LIBDIR)
if(NOT DEFINED DOCDIR)
    set(DOCDIR "share/doc/ibus-qt-${CPACK_PACKAGE_VERSION}")
endif(NOT DEFINED DOCDIR)

# =====
# install
set(MAIN_DOCS
    AUTHORS
    README
    INSTALL)
install(FILES ${MAIN_DOCS}
    DESTINATION ${DOCDIR})



# ======
# sub dirs
add_subdirectory(src)
add_subdirectory(qtim)
add_subdirectory(test)

# ======
# targets
add_custom_target(version echo ${CPACK_PACKAGE_VERSION})
add_custom_target(gitclean git clean -f -d -X)
add_custom_target(rpm
    COMMAND make package_source
    COMMAND rpmbuild -bb
    --define "_sourcedir ${CMAKE_CURRENT_SOURCE_DIR}"
    --define "_builddir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    --define "_srcrpmdir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    --define "_rpmdir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    --define "_specdir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    ibus-qt.spec
    )
add_custom_target(srpm
    COMMAND make package_source
    COMMAND rpmbuild -bs
    --define "_sourcedir ${CMAKE_CURRENT_SOURCE_DIR}"
    --define "_builddir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    --define "_srcrpmdir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    --define "_rpmdir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    --define "_specdir ${CMAKE_CURRENT_SOURCE_DIR}/rpm"
    ibus-qt.spec
    )
