#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cppdom" for configuration "Debug"
set_property(TARGET cppdom APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cppdom PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/cppdom_d-1_2_0.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/cppdom_d-1_2_0.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS cppdom )
list(APPEND _IMPORT_CHECK_FILES_FOR_cppdom "${_IMPORT_PREFIX}/lib/cppdom_d-1_2_0.lib" "${_IMPORT_PREFIX}/bin/cppdom_d-1_2_0.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
