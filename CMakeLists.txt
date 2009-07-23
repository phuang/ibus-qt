cmake_minimum_required(VERSION 2.4)

project(ibus-qt)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)


include(CPack)

add_subdirectory(src)
add_subdirectory(qtim)
