# Install script for directory: /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/../install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/libfmilib.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfmilib_shared.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfmilib_shared.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfmilib_shared.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/libfmilib_shared.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfmilib_shared.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfmilib_shared.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libfmilib_shared.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc" TYPE FILE FILES
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/FMILIB_Readme.txt"
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/FMILIB_License.txt"
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/FMILIB_Acknowledgements.txt"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/fmilib_config.h"
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/fmilib.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/src/Import/include"
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/src/Util//include"
    FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/ThirdParty/FMI/default/FMI1"
    "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/ThirdParty/FMI/default/FMI2"
    FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/ThirdParty/c99_snprintf/cmake_install.cmake")
  include("/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/Config.cmake/Minizip/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
