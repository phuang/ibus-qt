project(ibus-qt)
cmake_minimum_required(VERSION 2.4.0)
include(CPack)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Qt
find_package(Qt4 REQUIRED)

#
find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUS REQUIRED dbus-1)
add_subdirectory(src)
