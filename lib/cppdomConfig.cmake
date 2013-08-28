# - Config file for the cppdom package
# It defines the following variables
#  cppdom_INCLUDE_DIRS - include directories for cppdom
#  cppdom_LIBRARIES    - libraries to link against


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was cppdomConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# These are IMPORTED targets created by cppdomLibraryDepends.cmake
set(cppdom_LIBRARIES "cppdom" )

# Compute paths
# get_filename_component(cppdom_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${PACKAGE_PREFIX_DIR}/CMakeCache.txt")
    # In build tree
    include("${PACKAGE_PREFIX_DIR}/lib/cppdomBuildTreeSettings.cmake")
    # Our library dependencies (contains definitions for IMPORTED targets)
    include("${PACKAGE_PREFIX_DIR}/lib/cppdomLibraryDepends.cmake")
else()
    set_and_check(cppdom_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include")
    # The cppdom targets file.
    if(EXISTS "${PACKAGE_PREFIX_DIR}/lib/cppdom-targets.cmake")
        include("${PACKAGE_PREFIX_DIR}/lib/cppdom-targets.cmake")
    endif()
endif()

# The location of the Usecppdom.cmake file.
set(cppdom_USE_FILE "${PACKAGE_PREFIX_DIR}/lib/Usecppdom.cmake")
# - Config file for the cppdom package
# It defines the following variables
#  cppdom_INCLUDE_DIRS - include directories for cppdom
#  cppdom_LIBRARIES    - libraries to link against


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was cppdomConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

# These are IMPORTED targets created by cppdomLibraryDepends.cmake
set(cppdom_LIBRARIES "cppdom" )

# Compute paths
# get_filename_component(cppdom_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
if(EXISTS "${PACKAGE_PREFIX_DIR}/CMakeCache.txt")
    # In build tree
    include("${PACKAGE_PREFIX_DIR}/lib/cppdomBuildTreeSettings.cmake")
    # Our library dependencies (contains definitions for IMPORTED targets)
    include("${PACKAGE_PREFIX_DIR}/lib/cppdomLibraryDepends.cmake")
else()
    set_and_check(cppdom_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include")
    # The cppdom targets file.
    if(EXISTS "${PACKAGE_PREFIX_DIR}/lib/cppdom-targets.cmake")
        include("${PACKAGE_PREFIX_DIR}/lib/cppdom-targets.cmake")
    endif()
endif()

# The location of the Usecppdom.cmake file.
set(cppdom_USE_FILE "${PACKAGE_PREFIX_DIR}/lib/Usecppdom.cmake")
