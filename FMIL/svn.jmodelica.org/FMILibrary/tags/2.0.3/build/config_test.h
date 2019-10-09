/*
    Copyright (C) 2012 Modelon AB

    This program is free software: you can redistribute it and/or modify
    it under the terms of the BSD style license.

     This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    FMILIB_License.txt file for more details.

    You should have received a copy of the FMILIB_License.txt file
    along with this program. If not, contact Modelon AB <http://www.modelon.com>.
*/

#ifndef CONFIG_TEST_H
#define CONFIG_TEST_H
/* PATHs to test files */
#define FMU1_DLL_ME_PATH "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/" CMAKE_INTDIR "/libfmu1_dll_me.so" 
#define FMU1_DLL_CS_PATH "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/" CMAKE_INTDIR "/libfmu1_dll_cs.so"
#define COMPRESS_DUMMY_FILE_PATH_SRC "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/try_to_compress_this_file.xml"
#define COMPRESS_DUMMY_FILE_PATH_DIST "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/Testing/successfully_compressed_this_file.zip"
#define UNCOMPRESSED_DUMMY_FILE_PATH_SRC "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/Test/try_to_uncompress_this_file.zip"
#define UNCOMPRESSED_DUMMY_FOLDER_PATH_DIST "/home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/Testing"

#define CTEST_RETURN_SUCCESS 0
#define CTEST_RETURN_FAIL 1

#define FMU_DUMMY_ME_MODEL_IDENTIFIER BouncingBall
#define FMU_DUMMY_CS_MODEL_IDENTIFIER BouncingBall

#define FMILIB_LINK_TEST_TO_SHAREDLIB
#if defined(FMILIB_LINK_TEST_TO_SHAREDLIB) && defined(FMILIB_BUILDING_LIBRARY)
#undef FMILIB_BUILDING_LIBRARY
#endif

#endif


