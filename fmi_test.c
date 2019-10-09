

#include <fmilib.h>

#include <stdio.h>
#include <stdlib.h>
// #include <stdarg.h>


int simulate(fmi2_import_t* fmu);
int main()
{


	fmi2_callback_functions_t callBackFunctions;
	const char* FMUPath = "/home/lapbottom/Programming/Exjobb/Models/InvertedPendulum/InvertedPendulum.fmu" ;
	const char* tmpPath = "/home/lapbottom/Programming/Exjobb/tmp_dir";

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
	simulate(fmu);
	// printf(status);
	/* insert stuff */ 	

	fmi2_import_destroy_dllfmu(fmu);
	fmi_import_free_context(context);

			
	return 0;
}


fmi2_status_t do_event_iteration(fmi2_import_t *fmu, fmi2_event_info_t *eventInfo)
{
	fmi2_status_t fmistatus = fmi2_status_ok;
	eventInfo->newDiscreteStatesNeeded = fmi2_true;
	eventInfo->terminateSimulation     = fmi2_false;
	while (eventInfo->newDiscreteStatesNeeded && !eventInfo->terminateSimulation) {
		fmistatus = fmi2_import_new_discrete_states(fmu, eventInfo);
	}
	return fmistatus;
}

int simulate(fmi2_import_t* fmu)
{
	fmi2_status_t fmistatus;
	jm_status_enu_t jmstatus;
	// FMUC  jm_callbacks* cb = &cdata->callbacks;

	fmi2_real_t tstart = 0.0;
	fmi2_real_t tcur, tnext;
	fmi2_real_t hcur;
	fmi2_real_t hdef = 0.1;
	fmi2_real_t tend = 2.0;

	size_t n_states;
	size_t n_event_indicators;
	// Not needed?
	// fmi2_real_t states_end_results[] = {0.362000, -3.962000};
	fmi2_real_t* states = 0;
	fmi2_real_t* states_der = 0;
	fmi2_real_t* event_indicators = 0;
	fmi2_real_t* event_indicators_prev = 0;
	fmi2_boolean_t callEventUpdate;
	fmi2_boolean_t terminateSimulation = fmi2_false;
	fmi2_boolean_t toleranceControlled = fmi2_false; // true first, changed because of FMUCompl
	fmi2_real_t relativeTolerance = 0.001;
	fmi2_event_info_t eventInfo;
	// Not needed? From FMUCompl	
	size_t k;
	// From FMUCompl
	fmi2_boolean_t intermediateResults = fmi2_false;
	//prepare_time_step_info(cdata, &tend, &hdef);


	n_states = fmi2_import_get_number_of_continuous_states(fmu);
	n_event_indicators = fmi2_import_get_number_of_event_indicators(fmu);

	// printf("Number of states: %u\n", (unsigned)n_states);
	// if (sizeof(states_end_results)/sizeof(fmi2_real_t) != n_states) {
		// printf("Number of states and results have different length n_states = %u n_results = %u\n", (unsigned)n_states, (unsigned)sizeof(states_end_results));
		// exit(1);
	// }
	states = calloc(n_states, sizeof(double));
	states_der = calloc(n_states, sizeof(double));
	event_indicators = calloc(n_event_indicators, sizeof(double));
	event_indicators_prev = calloc(n_event_indicators, sizeof(double));

	jmstatus = fmi2_import_instantiate(fmu, "Test ME model instance",fmi2_model_exchange,0,0);
	if (jmstatus == jm_status_error) {
		printf("fmi2_import_instantiate failed\n");
		exit(1);
	}

	fmistatus = fmi2_import_set_debug_logging(fmu, fmi2_false,0,0);
	printf("fmi2_import_set_debug_logging:  %s\n", fmi2_status_to_string(fmistatus));	
	fmi2_import_set_debug_logging(fmu, fmi2_true, 0, 0);

    fmistatus = fmi2_import_setup_experiment(fmu, toleranceControlled,
        relativeTolerance, tstart, fmi2_false, 0.0);

    fmistatus = fmi2_import_enter_initialization_mode(fmu);
    fmistatus = fmi2_import_exit_initialization_mode(fmu);

	tcur = tstart;
	hcur = hdef;
	callEventUpdate = fmi2_false;

	eventInfo.newDiscreteStatesNeeded           = fmi2_false;
	eventInfo.terminateSimulation               = fmi2_false;
	eventInfo.nominalsOfContinuousStatesChanged = fmi2_false;
	eventInfo.valuesOfContinuousStatesChanged   = fmi2_true;
	eventInfo.nextEventTimeDefined              = fmi2_false;
	eventInfo.nextEventTime                     = -0.0;

    /* fmiExitInitializationMode leaves FMU in event mode */
    do_event_iteration(fmu, &eventInfo);
    fmi2_import_enter_continuous_time_mode(fmu);

	fmistatus = fmi2_import_get_continuous_states(fmu, states, n_states);
	fmistatus = fmi2_import_get_event_indicators(fmu, event_indicators, n_event_indicators);

	while ((tcur < tend) && (!(eventInfo.terminateSimulation || terminateSimulation))) {
		// size_t k;
        fmi2_real_t tlast;
		int zero_crossing_event = 0;

		fmistatus = fmi2_import_set_time(fmu, tcur);

        { /* Swap event_indicators and event_indicators_prev so that we can get new indicators */
            fmi2_real_t *temp = event_indicators;
            event_indicators = event_indicators_prev;
            event_indicators_prev = temp;
        }
		fmistatus = fmi2_import_get_event_indicators(fmu, event_indicators, n_event_indicators);

		/* Check if an event indicator has triggered */
		for (unsigned k = 0; k < n_event_indicators; k++) {
			if ((event_indicators[k] > 0) != (event_indicators_prev[k] > 0)) {
				zero_crossing_event = 1;
				break;
			}
		}

		/* Handle any events */
		if (callEventUpdate || zero_crossing_event ||
		  (eventInfo.nextEventTimeDefined && tcur == eventInfo.nextEventTime)) {
            fmistatus = fmi2_import_enter_event_mode(fmu);
            do_event_iteration(fmu, &eventInfo);
            fmistatus = fmi2_import_enter_continuous_time_mode(fmu);

			fmistatus = fmi2_import_get_continuous_states(fmu, states, n_states);
			fmistatus = fmi2_import_get_event_indicators(fmu, event_indicators, n_event_indicators);
		}

		/* Calculate next time step */
        tlast = tcur;
        tcur += hdef;
		if (eventInfo.nextEventTimeDefined && (tcur >= eventInfo.nextEventTime)) {
            tcur = eventInfo.nextEventTime;
		}
        hcur = tcur - tlast;
		if(tcur > tend - hcur/1e16) {
			tcur = tend;				
			hcur = tcur - tlast;
		}

		/* Integrate a step */
		for(int i = 0; i < n_states; i++)  
			printf("This is the states der %f\n", states[i]);
		printf(states);

		fmistatus = fmi2_import_get_derivatives(fmu, states_der, n_states);
		for (unsigned k = 0; k < n_states; k++) {
			states[k] = states[k] + hcur*states_der[k];	
			if (k == 0) printf("Ball height state[%u] = %f\n", (unsigned)k, states[k]);
		}

		/* Set states */
		fmistatus = fmi2_import_set_continuous_states(fmu, states, n_states);
		/* Step is complete */
		fmistatus = fmi2_import_completed_integrator_step(fmu, fmi2_true, &callEventUpdate,
                                                          &terminateSimulation);
	}	

	// /* Validate result */
	// for (k = 0; k < n_states; k++) {
		// fmi2_real_t res = states[k] - states_end_results[k];
		// res = res > 0 ? res: -res; /* Take abs */
		// if (res > 1e-10) {
			// printf("Simulation results is wrong  states[%u] %f != %f, |res| = %f\n", (unsigned)k, states[k], states_end_results[k], res);
			// exit(1);
		// }
	// }
	

	fmistatus = fmi2_import_terminate(fmu);

	fmi2_import_free_instance(fmu);

	free(states);
	free(states_der);
	free(event_indicators);
	free(event_indicators_prev);

}

