# - Find a cppdom installation or build tree.
# The following variables are set if cppdom is found.  If cppdom is not
# found, cppdom_FOUND is set to false.
#  cppdom_FOUND         - Set to true when cppdom is found.
#  cppdom_USE_FILE      - CMake file to use cppdom.
#  cppdom_MAJOR_VERSION - The cppdom major version number.
#  cppdom_MINOR_VERSION - The cppdom minor version number 
#                       (odd non-release).
#  cppdom_BUILD_VERSION - The cppdom patch level 
#                       (meaningless for odd minor).
#  cppdom_INCLUDE_DIRS  - Include directories for cppdom
#  cppdom_LIBRARY_DIRS  - Link directories for cppdom libraries

# The following cache entries must be set by the user to locate cppdom:
#  cppdom_DIR  - The directory containing cppdomConfig.cmake.  
#             This is either the root of the build tree,
#             or the lib directory.  This is the 
#             only cache entry.


# Assume not found.
SET(cppdom_FOUND 0)

# Construct consitent error messages for use below.
SET(cppdom_DIR_DESCRIPTION "directory containing cppdomConfig.cmake.  This is either the root of the build tree, or PREFIX/lib for an installation.")
SET(cppdom_DIR_MESSAGE "cppdom not found.  Set the cppdom_DIR cmake cache entry to the ${cppdom_DIR_DESCRIPTION}")

# Use the Config mode of the find_package() command to find cppdomConfig.
# If this succeeds (possibly because cppdom_DIR is already set), the
# command will have already loaded cppdomConfig.cmake and set cppdom_FOUND.
IF(NOT cppdom_FOUND)
  FIND_PACKAGE(cppdom QUIET NO_MODULE)
ENDIF(NOT cppdom_FOUND)

#-----------------------------------------------------------------------------
IF(NOT cppdom_FOUND)
  # cppdom not found, explain to the user how to specify its location.
  IF(cppdom_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR ${cppdom_DIR_MESSAGE})
  ELSE(cppdom_FIND_REQUIRED)
    IF(NOT cppdom_FIND_QUIETLY)
      MESSAGE(STATUS ${cppdom_DIR_MESSAGE})
    ENDIF(NOT cppdom_FIND_QUIETLY)
  ENDIF(cppdom_FIND_REQUIRED)
ENDIF(NOT cppdom_FOUND)
