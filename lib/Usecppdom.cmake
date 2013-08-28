#
# This module is provided as cppdom_USE_FILE by cppdomConfig.cmake.  It can
# be INCLUDEd in a project to load the needed compiler and linker
# settings to use cppdom.
#

IF(NOT cppdom_USE_FILE_INCLUDED)
  SET(cppdom_USE_FILE_INCLUDED 1)

  # Update CMAKE_MODULE_PATH so includes work.
  #SET (CMAKE_MODULE_PATH
  #  ${CMAKE_MODULE_PATH}
  #  ${cppdom_CMAKE_DIR})

  # Add compiler flags needed to use cppdom.
  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${cppdom_REQUIRED_C_FLAGS}")
  #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cppdom_REQUIRED_CXX_FLAGS}")
  #SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${cppdom_REQUIRED_EXE_LINKER_FLAGS}")
  #SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${cppdom_REQUIRED_SHARED_LINKER_FLAGS}")
  #SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${cppdom_REQUIRED_MODULE_LINKER_FLAGS}")

  # Add include directories needed to use cppdom.
  INCLUDE_DIRECTORIES(${cppdom_INCLUDE_DIRS})

ENDIF(NOT cppdom_USE_FILE_INCLUDED)
#
# This module is provided as cppdom_USE_FILE by cppdomConfig.cmake.  It can
# be INCLUDEd in a project to load the needed compiler and linker
# settings to use cppdom.
#

IF(NOT cppdom_USE_FILE_INCLUDED)
  SET(cppdom_USE_FILE_INCLUDED 1)

  # Update CMAKE_MODULE_PATH so includes work.
  #SET (CMAKE_MODULE_PATH
  #  ${CMAKE_MODULE_PATH}
  #  ${cppdom_CMAKE_DIR})

  # Add compiler flags needed to use cppdom.
  #SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${cppdom_REQUIRED_C_FLAGS}")
  #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cppdom_REQUIRED_CXX_FLAGS}")
  #SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${cppdom_REQUIRED_EXE_LINKER_FLAGS}")
  #SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${cppdom_REQUIRED_SHARED_LINKER_FLAGS}")
  #SET(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${cppdom_REQUIRED_MODULE_LINKER_FLAGS}")

  # Add include directories needed to use cppdom.
  INCLUDE_DIRECTORIES(${cppdom_INCLUDE_DIRS})

ENDIF(NOT cppdom_USE_FILE_INCLUDED)
