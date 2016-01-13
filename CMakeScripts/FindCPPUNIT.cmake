#
# Find the CppUnit headers and libraries.
#
# This module defines
# CPPUNIT_INCLUDE_DIRS - the cppunit include directory
# CPPUNIT_LIBRARIES    - the libraries needed to use cppunit
# CPPUNIT_FOUND        - system has the cppunit library
#
# Copyright (c) 2016 David Boucher <boudav at gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.

FIND_PATH(CPPUNIT_INCLUDE_DIR NAMES cppunit/TestCase.h)
FIND_LIBRARY(CPPUNIT_LIBRARY NAMES cppunit)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPPUNIT DEFAULT_MSG
 CPPUNIT_LIBRARY
 CPPUNIT_INCLUDE_DIR
)

IF (CPPUNIT_FOUND)
  SET(CPPUNIT_LIBRARIES ${CPPUNIT_LIBRARY})
  # hack to get old and new layout working:
  SET(CPPUNIT_INCLUDE_DIRS ${CPPUNIT_INCLUDE_DIR})
ENDIF()

MARK_AS_ADVANCED(
  CPPUNIT_LIBRARY
  CPPUNIT_INCLUDE_DIR
)
