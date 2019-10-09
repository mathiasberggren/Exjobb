# Extract object files from the library
message(STATUS "Extracting object files from /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/libfmicapi.a")
EXECUTE_PROCESS(COMMAND /usr/bin/ar -x /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/libfmicapi.a                
                WORKING_DIRECTORY /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/libfmicapi.a.objdir)
# save the list of object files
EXECUTE_PROCESS(COMMAND ls . 
				OUTPUT_FILE /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/libfmicapi.a.objlist
                WORKING_DIRECTORY /home/lapbottom/Programming/Exjobb/FMIL/svn.jmodelica.org/FMILibrary/tags/2.0.3/build/libfmicapi.a.objdir)