find_program(ICU_CONFIG_EXECUTABLE NAMES icu-config DOC "icu-config executable")
mark_as_advanced(ICU_CONFIG_EXECUTABLE)

if(ICU_CONFIG_EXECUTABLE)
  set(ICU_FOUND "YES")
else(ICU_CONFIG_EXECUTABLE)
  set(ICU_FOUND "NO")
  # if(ICU_FIND_REQUIRED)
  #   message(FATAL_ERROR "Could not find icu")
  # endif(ICU_FIND_REQUIRED)
endif(ICU_CONFIG_EXECUTABLE)

if(ICU_FOUND)
  exec_program("${ICU_CONFIG_EXECUTABLE} --ldflags-libsonly"
    OUTPUT_VARIABLE ICU_LIBRARIES
    RETURN_VALUE ERROR_CODE
  )
  separate_arguments(ICU_LIBRARIES)

  exec_program("${ICU_CONFIG_EXECUTABLE} --cppflags-searchpath|sed s/^-I//"
    OUTPUT_VARIABLE ICU_INCLUDE_DIRS
    RETURN_VALUE ERROR_CODE
  )
  separate_arguments(ICU_INCLUDE_DIRS)
endif(ICU_FOUND)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ICU DEFAULT_MSG
  ICU_LIBRARIES ICU_INCLUDE_DIRS)
