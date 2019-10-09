/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "InvertedPendulum_model.h"
#include "simulation/solver/events.h"


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int InvertedPendulum_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->localData[0]->realVars[10] /* F variable */ = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int InvertedPendulum_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->inputVars[0] = data->modelData->realVarsData[10].attribute.start;
  
  TRACE_POP
  return 0;
}

int InvertedPendulum_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->modelData->realVarsData[10].attribute.start = data->simulationInfo->inputVars[0];
  
  TRACE_POP
  return 0;
}

int InvertedPendulum_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  names[0] = (char *) data->modelData->realVarsData[10].info.name;
  
  TRACE_POP
  return 0;
}

int InvertedPendulum_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->outputVars[0] = data->localData[0]->realVars[11] /* Y variable */;
  
  TRACE_POP
  return 0;
}


/*
equation index: 16
type: SIMPLE_ASSIGN
der(theta) = theta_velo
*/
void InvertedPendulum_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  data->localData[0]->realVars[4] /* der(theta) STATE_DER */ = data->localData[0]->realVars[1] /* theta_velo STATE(1,theta_accel) */;
  TRACE_POP
}
/*
equation index: 17
type: SIMPLE_ASSIGN
der(x_pos) = x_vel
*/
void InvertedPendulum_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[6] /* der(x_pos) STATE_DER */ = data->localData[0]->realVars[3] /* x_vel STATE(1,x_acc) */;
  TRACE_POP
}
/*
equation index: 18
type: SIMPLE_ASSIGN
Y = theta
*/
void InvertedPendulum_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  data->localData[0]->realVars[11] /* Y variable */ = data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */;
  TRACE_POP
}
/*
equation index: 19
type: SIMPLE_ASSIGN
$cse3 = cos(theta)
*/
void InvertedPendulum_eqFunction_19(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,19};
  data->localData[0]->realVars[9] /* $cse3 variable */ = cos(data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */);
  TRACE_POP
}
/*
equation index: 20
type: SIMPLE_ASSIGN
$cse2 = sin(theta)
*/
void InvertedPendulum_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  data->localData[0]->realVars[8] /* $cse2 variable */ = sin(data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */);
  TRACE_POP
}
/*
equation index: 25
type: LINEAR

<var>theta_accel</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void InvertedPendulum_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { data->localData[1]->realVars[12] /* theta_accel variable */ };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 25 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  retValue = solve_linear_system(data, threadData, 1, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,25};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 25 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[12] /* theta_accel variable */ = aux_x[0];
  TRACE_POP
}
/*
equation index: 26
type: SIMPLE_ASSIGN
der(x_vel) = x_acc
*/
void InvertedPendulum_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->localData[0]->realVars[7] /* der(x_vel) STATE_DER */ = data->localData[0]->realVars[13] /* x_acc variable */;
  TRACE_POP
}
/*
equation index: 27
type: SIMPLE_ASSIGN
der(theta_velo) = theta_accel
*/
void InvertedPendulum_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->localData[0]->realVars[5] /* der(theta_velo) STATE_DER */ = data->localData[0]->realVars[12] /* theta_accel variable */;
  TRACE_POP
}

OMC_DISABLE_OPT
int InvertedPendulum_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
  
  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  InvertedPendulum_functionLocalKnownVars(data, threadData);
  InvertedPendulum_eqFunction_16(data, threadData);

  InvertedPendulum_eqFunction_17(data, threadData);

  InvertedPendulum_eqFunction_18(data, threadData);

  InvertedPendulum_eqFunction_19(data, threadData);

  InvertedPendulum_eqFunction_20(data, threadData);

  InvertedPendulum_eqFunction_25(data, threadData);

  InvertedPendulum_eqFunction_26(data, threadData);

  InvertedPendulum_eqFunction_27(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int InvertedPendulum_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/* forwarded equations */
extern void InvertedPendulum_eqFunction_16(DATA* data, threadData_t *threadData);
extern void InvertedPendulum_eqFunction_17(DATA* data, threadData_t *threadData);
extern void InvertedPendulum_eqFunction_19(DATA* data, threadData_t *threadData);
extern void InvertedPendulum_eqFunction_20(DATA* data, threadData_t *threadData);
extern void InvertedPendulum_eqFunction_25(DATA* data, threadData_t *threadData);
extern void InvertedPendulum_eqFunction_26(DATA* data, threadData_t *threadData);
extern void InvertedPendulum_eqFunction_27(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
    InvertedPendulum_eqFunction_16(data, threadData);

    InvertedPendulum_eqFunction_17(data, threadData);

    InvertedPendulum_eqFunction_19(data, threadData);

    InvertedPendulum_eqFunction_20(data, threadData);

    InvertedPendulum_eqFunction_25(data, threadData);

    InvertedPendulum_eqFunction_26(data, threadData);

    InvertedPendulum_eqFunction_27(data, threadData);
}

int InvertedPendulum_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  data->simulationInfo->callStatistics.functionODE++;
  
  InvertedPendulum_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

  
  TRACE_POP
  return 0;
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "InvertedPendulum_12jac.h"
#include "InvertedPendulum_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks InvertedPendulum_callback = {
   NULL,
   NULL,
   NULL,
   InvertedPendulum_callExternalObjectDestructors,
   NULL,
   InvertedPendulum_initialLinearSystem,
   NULL,
   #if !defined(OMC_NO_STATESELECTION)
   InvertedPendulum_initializeStateSets,
   #else
   NULL,
   #endif
   InvertedPendulum_initializeDAEmodeData,
   InvertedPendulum_functionODE,
   InvertedPendulum_functionAlgebraics,
   InvertedPendulum_functionDAE,
   InvertedPendulum_functionLocalKnownVars,
   InvertedPendulum_input_function,
   InvertedPendulum_input_function_init,
   InvertedPendulum_input_function_updateStartValues,
   InvertedPendulum_output_function,
   InvertedPendulum_function_storeDelayed,
   InvertedPendulum_updateBoundVariableAttributes,
   InvertedPendulum_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   InvertedPendulum_functionInitialEquations_lambda0,
   InvertedPendulum_functionRemovedInitialEquations,
   InvertedPendulum_updateBoundParameters,
   InvertedPendulum_checkForAsserts,
   InvertedPendulum_function_ZeroCrossingsEquations,
   InvertedPendulum_function_ZeroCrossings,
   InvertedPendulum_function_updateRelations,
   InvertedPendulum_zeroCrossingDescription,
   InvertedPendulum_relationDescription,
   InvertedPendulum_function_initSample,
   InvertedPendulum_INDEX_JAC_A,
   InvertedPendulum_INDEX_JAC_B,
   InvertedPendulum_INDEX_JAC_C,
   InvertedPendulum_INDEX_JAC_D,
   InvertedPendulum_initialAnalyticJacobianA,
   InvertedPendulum_initialAnalyticJacobianB,
   InvertedPendulum_initialAnalyticJacobianC,
   InvertedPendulum_initialAnalyticJacobianD,
   InvertedPendulum_functionJacA_column,
   InvertedPendulum_functionJacB_column,
   InvertedPendulum_functionJacC_column,
   InvertedPendulum_functionJacD_column,
   InvertedPendulum_linear_model_frame,
   InvertedPendulum_linear_model_datarecovery_frame,
   InvertedPendulum_mayer,
   InvertedPendulum_lagrange,
   InvertedPendulum_pickUpBoundsForInputsInOptimization,
   InvertedPendulum_setInputData,
   InvertedPendulum_getTimeGrid,
   InvertedPendulum_symbolicInlineSystem,
   InvertedPendulum_function_initSynchronous,
   InvertedPendulum_function_updateSynchronous,
   InvertedPendulum_function_equationsSynchronous,
   InvertedPendulum_inputNames,
   InvertedPendulum_read_input_fmu,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "Complex"
#define _OMC_LIT_RESOURCE_0_dir_data "/usr/lib/omlibrary"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,7,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,18,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "InvertedPendulum"
#define _OMC_LIT_RESOURCE_1_dir_data "/home/lapbottom/Programming/Exjobb/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,16,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,41,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "Modelica"
#define _OMC_LIT_RESOURCE_2_dir_data "/usr/lib/omlibrary/Modelica 3.2.2"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,8,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,33,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "ModelicaReference"
#define _OMC_LIT_RESOURCE_3_dir_data "/usr/lib/omlibrary/ModelicaReference"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,17,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,36,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "ModelicaServices"
#define _OMC_LIT_RESOURCE_4_dir_data "/usr/lib/omlibrary/ModelicaServices 3.2.2"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,16,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,41,_OMC_LIT_RESOURCE_4_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,10,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir)}};
void InvertedPendulum_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &InvertedPendulum_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "InvertedPendulum";
  data->modelData->modelFilePrefix = "InvertedPendulum";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/home/lapbottom/Programming/Exjobb/Models";
  data->modelData->modelGUID = "{6018b5be-a7cf-48aa-b5ec-2367b190a9ce}";
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  
  data->modelData->nStates = 4;
  data->modelData->nVariablesReal = 14;
  data->modelData->nDiscreteReal = 0;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 0;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 4;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 1;
  data->modelData->nOutputVars = 1;
  
  data->modelData->nAliasReal = 0;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 0;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  GC_asprintf(&data->modelData->modelDataXml.fileName, "%s/InvertedPendulum_info.json", data->modelData->resourcesDir);
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 0;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 30;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 2;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 6;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  
  data->modelData->nDelayExpressions = 0;
  
  data->modelData->nClocks = 0;
  data->modelData->nSubClocks = 0;
  
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

