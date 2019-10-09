


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "fmilib.h"


int main(int argc, char* argv[])
{

	fmi2_callback_functions_t callBackFunctions;
	const char* FMUPath = "~/Programming/Exjobb/Models/InvertedPendulum/InvertedPendulum.fmu" ;
	const char* tmpPath = "~/Programming/Exjobb/";
	jm_callbacks callbacks;
	fmi_import_context_t* context;
	fmi_version_enu_t version;
	jm_status_enu_t status;

	fmi2_import_t* fmu;	
	
	callbacks.malloc = malloc;
    callbacks.calloc = calloc;
    callbacks.realloc = realloc;
    callbacks.free = free;
    callbacks.logger = jm_default_logger;
	callbacks.log_level = jm_log_level_debug;
    callbacks.context = 0;

	context = fmi_import_allocate_context(&callbacks);
	version = fmi_import_get_fmi_version(context, FMUPath, tmpPath);

	fmu = fmi2_import_parse_xml(context, tmpPath,0);

	callBackFunctions.logger = fmi2_log_forwarding;
	callBackFunctions.allocateMemory = calloc;
	callBackFunctions.freeMemory = free;
	callBackFunctions.componentEnvironment = fmu;

	status = fmi2_import_create_dllfmu(fmu, fmi2_fmu_kind_me, &callBackFunctions);

	fmi2_import_destroy_dllfmu(fmu);
	fmi_import_free_context(context);

	return 0;

}
