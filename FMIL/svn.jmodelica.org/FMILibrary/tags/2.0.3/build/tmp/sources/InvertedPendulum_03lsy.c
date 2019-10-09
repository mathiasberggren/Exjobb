/* Linear Systems */
#include "InvertedPendulum_model.h"
#include "InvertedPendulum_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* linear systems */

/*
equation index: 21
type: SIMPLE_ASSIGN
x_acc = (F - m * l * (theta_velo ^ 2.0 * $cse2 - theta_accel * $cse3)) / (M + m)
*/
void InvertedPendulum_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  modelica_real tmp0;
  tmp0 = data->localData[0]->realVars[1] /* theta_velo STATE(1,theta_accel) */;
  data->localData[0]->realVars[13] /* x_acc variable */ = DIVISION_SIM(data->localData[0]->realVars[10] /* F variable */ - ((data->simulationInfo->realParameter[3]) * ((data->simulationInfo->realParameter[2]) * (((tmp0 * tmp0)) * (data->localData[0]->realVars[8] /* $cse2 variable */) - ((data->localData[0]->realVars[12] /* theta_accel variable */) * (data->localData[0]->realVars[9] /* $cse3 variable */))))),data->simulationInfo->realParameter[0] + data->simulationInfo->realParameter[3],"M + m",equationIndexes);
  TRACE_POP
}

void residualFunc25(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,25};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  data->localData[0]->realVars[12] /* theta_accel variable */ = xloc[0];
  /* local constraints */
  InvertedPendulum_eqFunction_21(data, threadData);
  res[0] = (data->simulationInfo->realParameter[2]) * (data->localData[0]->realVars[12] /* theta_accel variable */) + ((-data->simulationInfo->realParameter[1])) * (data->localData[0]->realVars[8] /* $cse2 variable */) - ((data->localData[0]->realVars[13] /* x_acc variable */) * (data->localData[0]->realVars[9] /* $cse3 variable */));
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData25(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for theta_accel */
  linearSystemData->nominal[i] = data->modelData->realVarsData[12].attribute /* theta_accel */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[12].attribute /* theta_accel */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[12].attribute /* theta_accel */.max;
}


/*
equation index: 5
type: SIMPLE_ASSIGN
x_acc = (F - m * l * (theta_velo ^ 2.0 * sin(theta) - theta_accel * cos(theta))) / (M + m)
*/
void InvertedPendulum_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  modelica_real tmp0;
  tmp0 = data->localData[0]->realVars[1] /* theta_velo STATE(1,theta_accel) */;
  data->localData[0]->realVars[13] /* x_acc variable */ = DIVISION_SIM(data->localData[0]->realVars[10] /* F variable */ - ((data->simulationInfo->realParameter[3]) * ((data->simulationInfo->realParameter[2]) * (((tmp0 * tmp0)) * (sin(data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */)) - ((data->localData[0]->realVars[12] /* theta_accel variable */) * (cos(data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */)))))),data->simulationInfo->realParameter[0] + data->simulationInfo->realParameter[3],"M + m",equationIndexes);
  TRACE_POP
}

void residualFunc10(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,10};
  ANALYTIC_JACOBIAN* jacobian = NULL;
  data->localData[0]->realVars[12] /* theta_accel variable */ = xloc[0];
  /* local constraints */
  InvertedPendulum_eqFunction_5(data, threadData);
  res[0] = (data->simulationInfo->realParameter[2]) * (data->localData[0]->realVars[12] /* theta_accel variable */) + ((-data->simulationInfo->realParameter[1])) * (sin(data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */)) - ((data->localData[0]->realVars[13] /* x_acc variable */) * (cos(data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */)));
  TRACE_POP
}
OMC_DISABLE_OPT
void initializeStaticLSData10(void *inData, threadData_t *threadData, void *systemData)
{
  DATA* data = (DATA*) inData;
  LINEAR_SYSTEM_DATA* linearSystemData = (LINEAR_SYSTEM_DATA*) systemData;
  int i=0;
  /* static ls data for theta_accel */
  linearSystemData->nominal[i] = data->modelData->realVarsData[12].attribute /* theta_accel */.nominal;
  linearSystemData->min[i]     = data->modelData->realVarsData[12].attribute /* theta_accel */.min;
  linearSystemData->max[i++]   = data->modelData->realVarsData[12].attribute /* theta_accel */.max;
}

/* Prototypes for the strict sets (Dynamic Tearing) */

/* Global constraints for the casual sets */
/* function initialize linear systems */
void InvertedPendulum_initialLinearSystem(int nLinearSystems, LINEAR_SYSTEM_DATA* linearSystemData)
{
  /* linear systems */
  assertStreamPrint(NULL, nLinearSystems > 1, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[1].equationIndex = 25;
  linearSystemData[1].size = 1;
  linearSystemData[1].nnz = 0;
  linearSystemData[1].method = 1;
  linearSystemData[1].residualFunc = residualFunc25;
  linearSystemData[1].strictTearingFunctionCall = NULL;
  linearSystemData[1].analyticalJacobianColumn = InvertedPendulum_functionJacLSJac1_column;
  linearSystemData[1].initialAnalyticalJacobian = InvertedPendulum_initialAnalyticJacobianLSJac1;
  linearSystemData[1].jacobianIndex = 1 /*jacInx*/;
  linearSystemData[1].setA = NULL;//setLinearMatrixA25;
  linearSystemData[1].setb = NULL; //setLinearVectorb25;
  linearSystemData[1].initializeStaticLSData = initializeStaticLSData25;
  linearSystemData[1].parentJacobian = NULL;
  
  assertStreamPrint(NULL, nLinearSystems > 0, "Internal Error: indexlinearSystem mismatch!");
  linearSystemData[0].equationIndex = 10;
  linearSystemData[0].size = 1;
  linearSystemData[0].nnz = 0;
  linearSystemData[0].method = 1;
  linearSystemData[0].residualFunc = residualFunc10;
  linearSystemData[0].strictTearingFunctionCall = NULL;
  linearSystemData[0].analyticalJacobianColumn = InvertedPendulum_functionJacLSJac0_column;
  linearSystemData[0].initialAnalyticalJacobian = InvertedPendulum_initialAnalyticJacobianLSJac0;
  linearSystemData[0].jacobianIndex = 0 /*jacInx*/;
  linearSystemData[0].setA = NULL;//setLinearMatrixA10;
  linearSystemData[0].setb = NULL; //setLinearVectorb10;
  linearSystemData[0].initializeStaticLSData = initializeStaticLSData10;
  linearSystemData[0].parentJacobian = NULL;
}

#if defined(__cplusplus)
}
#endif

