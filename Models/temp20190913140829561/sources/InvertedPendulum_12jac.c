/* Jacobians 6 */
#include "InvertedPendulum_model.h"
#include "InvertedPendulum_12jac.h"
OMC_DISABLE_OPT
int InvertedPendulum_initialAnalyticJacobianLSJac28(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  const int colPtrIndex[1+1] = {0,1};
  const int rowIndex[1] = {0};
  int i = 0;
  
  jacobian->sizeCols = 1;
  jacobian->sizeRows = 1;
  jacobian->sizeTmpVars = 3;
  jacobian->seedVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  jacobian->resultVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  jacobian->tmpVars = (modelica_real*) calloc(3,sizeof(modelica_real));
  jacobian->sparsePattern.leadindex = (unsigned int*) malloc((1+1)*sizeof(int));
  jacobian->sparsePattern.index = (unsigned int*) malloc(1*sizeof(int));
  jacobian->sparsePattern.numberOfNoneZeros = 1;
  jacobian->sparsePattern.colorCols = (unsigned int*) malloc(1*sizeof(int));
  jacobian->sparsePattern.maxColors = 1;
  
  /* write lead index of compressed sparse column */
  memcpy(jacobian->sparsePattern.leadindex, colPtrIndex, (1+1)*sizeof(int));
  
  for(i=2;i<1+1;++i)
    jacobian->sparsePattern.leadindex[i] += jacobian->sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(jacobian->sparsePattern.index, rowIndex, 1*sizeof(int));
  
  /* write color array */
  jacobian->sparsePattern.colorCols[0] = 1;
  TRACE_POP
  return 0;
}
OMC_DISABLE_OPT
int InvertedPendulum_initialAnalyticJacobianLSJac29(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  const int colPtrIndex[1+1] = {0,1};
  const int rowIndex[1] = {0};
  int i = 0;
  
  jacobian->sizeCols = 1;
  jacobian->sizeRows = 1;
  jacobian->sizeTmpVars = 2;
  jacobian->seedVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  jacobian->resultVars = (modelica_real*) calloc(1,sizeof(modelica_real));
  jacobian->tmpVars = (modelica_real*) calloc(2,sizeof(modelica_real));
  jacobian->sparsePattern.leadindex = (unsigned int*) malloc((1+1)*sizeof(int));
  jacobian->sparsePattern.index = (unsigned int*) malloc(1*sizeof(int));
  jacobian->sparsePattern.numberOfNoneZeros = 1;
  jacobian->sparsePattern.colorCols = (unsigned int*) malloc(1*sizeof(int));
  jacobian->sparsePattern.maxColors = 1;
  
  /* write lead index of compressed sparse column */
  memcpy(jacobian->sparsePattern.leadindex, colPtrIndex, (1+1)*sizeof(int));
  
  for(i=2;i<1+1;++i)
    jacobian->sparsePattern.leadindex[i] += jacobian->sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(jacobian->sparsePattern.index, rowIndex, 1*sizeof(int));
  
  /* write color array */
  jacobian->sparsePattern.colorCols[0] = 1;
  TRACE_POP
  return 0;
}
int InvertedPendulum_initialAnalyticJacobianD(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 1;
}
int InvertedPendulum_initialAnalyticJacobianC(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 1;
}
int InvertedPendulum_initialAnalyticJacobianB(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 1;
}
OMC_DISABLE_OPT
int InvertedPendulum_initialAnalyticJacobianA(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian)
{
  TRACE_PUSH
  DATA* data = ((DATA*)inData);
  const int colPtrIndex[1+4] = {0,2,3,0,1};
  const int rowIndex[6] = {1,3,0,1,3,2};
  int i = 0;
  
  jacobian->sizeCols = 4;
  jacobian->sizeRows = 4;
  jacobian->sizeTmpVars = 0;
  jacobian->seedVars = (modelica_real*) calloc(4,sizeof(modelica_real));
  jacobian->resultVars = (modelica_real*) calloc(4,sizeof(modelica_real));
  jacobian->tmpVars = (modelica_real*) calloc(0,sizeof(modelica_real));
  jacobian->sparsePattern.leadindex = (unsigned int*) malloc((4+1)*sizeof(int));
  jacobian->sparsePattern.index = (unsigned int*) malloc(6*sizeof(int));
  jacobian->sparsePattern.numberOfNoneZeros = 6;
  jacobian->sparsePattern.colorCols = (unsigned int*) malloc(4*sizeof(int));
  jacobian->sparsePattern.maxColors = 2;
  
  /* write lead index of compressed sparse column */
  memcpy(jacobian->sparsePattern.leadindex, colPtrIndex, (4+1)*sizeof(int));
  
  for(i=2;i<4+1;++i)
    jacobian->sparsePattern.leadindex[i] += jacobian->sparsePattern.leadindex[i-1];
  
  /* call sparse index */
  memcpy(jacobian->sparsePattern.index, rowIndex, 6*sizeof(int));
  
  /* write color array */
  jacobian->sparsePattern.colorCols[1] = 1;
  jacobian->sparsePattern.colorCols[0] = 2;
  jacobian->sparsePattern.colorCols[2] = 2;
  jacobian->sparsePattern.colorCols[3] = 2;
  TRACE_POP
  return 0;
}


/*
equation index: 7
type: SIMPLE_ASSIGN
$cse1 = cos(theta)
*/
void InvertedPendulum_eqFunction_7(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int clockIndex = 0;
  const int equationIndexes[2] = {1,7};
  jacobian->tmpVars[0] /* $cse1 JACOBIAN_DIFF_VAR */ = cos(data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */);
  TRACE_POP
}

/*
equation index: 8
type: SIMPLE_ASSIGN
x_acc._$pDERLSJac28._dummyVarLSJac28 = m * l * theta_accel.SeedLSJac28 * $cse1 / (M + m)
*/
void InvertedPendulum_eqFunction_8(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int clockIndex = 0;
  const int equationIndexes[2] = {1,8};
  jacobian->tmpVars[1] /* x_acc.$pDERLSJac28.dummyVarLSJac28 JACOBIAN_DIFF_VAR */ = DIVISION((data->simulationInfo->realParameter[3]) * ((data->simulationInfo->realParameter[2]) * ((jacobian->seedVars[0] /* theta_accel.SeedLSJac28 SEED_VAR */) * (jacobian->tmpVars[0] /* $cse1 JACOBIAN_DIFF_VAR */))),data->simulationInfo->realParameter[0] + data->simulationInfo->realParameter[3],"M + m");
  TRACE_POP
}

/*
equation index: 9
type: SIMPLE_ASSIGN
$res1._$pDERLSJac28._dummyVarLSJac28 = l * theta_accel.SeedLSJac28 - x_acc.$pDERLSJac28.dummyVarLSJac28 * $cse1
*/
void InvertedPendulum_eqFunction_9(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int clockIndex = 0;
  const int equationIndexes[2] = {1,9};
  jacobian->resultVars[0] /* $res1.$pDERLSJac28.dummyVarLSJac28 JACOBIAN_VAR */ = (data->simulationInfo->realParameter[2]) * (jacobian->seedVars[0] /* theta_accel.SeedLSJac28 SEED_VAR */) - ((jacobian->tmpVars[1] /* x_acc.$pDERLSJac28.dummyVarLSJac28 JACOBIAN_DIFF_VAR */) * (jacobian->tmpVars[0] /* $cse1 JACOBIAN_DIFF_VAR */));
  TRACE_POP
}
int InvertedPendulum_functionJacLSJac28_column(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = InvertedPendulum_INDEX_JAC_LSJac28;
  InvertedPendulum_eqFunction_7(data, threadData, jacobian, parentJacobian);

  InvertedPendulum_eqFunction_8(data, threadData, jacobian, parentJacobian);

  InvertedPendulum_eqFunction_9(data, threadData, jacobian, parentJacobian);
  
  TRACE_POP
  return 0;
}

/*
equation index: 23
type: SIMPLE_ASSIGN
x_acc._$pDERLSJac29._dummyVarLSJac29 = m * l * theta_accel.SeedLSJac29 * $cse3 / (M + m)
*/
void InvertedPendulum_eqFunction_23(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int clockIndex = 0;
  const int equationIndexes[2] = {1,23};
  jacobian->tmpVars[0] /* x_acc.$pDERLSJac29.dummyVarLSJac29 JACOBIAN_DIFF_VAR */ = DIVISION((data->simulationInfo->realParameter[3]) * ((data->simulationInfo->realParameter[2]) * ((jacobian->seedVars[0] /* theta_accel.SeedLSJac29 SEED_VAR */) * (data->localData[0]->realVars[9] /* $cse3 variable */))),data->simulationInfo->realParameter[0] + data->simulationInfo->realParameter[3],"M + m");
  TRACE_POP
}

/*
equation index: 24
type: SIMPLE_ASSIGN
$res1._$pDERLSJac29._dummyVarLSJac29 = l * theta_accel.SeedLSJac29 - x_acc.$pDERLSJac29.dummyVarLSJac29 * $cse3
*/
void InvertedPendulum_eqFunction_24(DATA *data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  const int clockIndex = 0;
  const int equationIndexes[2] = {1,24};
  jacobian->resultVars[0] /* $res1.$pDERLSJac29.dummyVarLSJac29 JACOBIAN_VAR */ = (data->simulationInfo->realParameter[2]) * (jacobian->seedVars[0] /* theta_accel.SeedLSJac29 SEED_VAR */) - ((jacobian->tmpVars[0] /* x_acc.$pDERLSJac29.dummyVarLSJac29 JACOBIAN_DIFF_VAR */) * (data->localData[0]->realVars[9] /* $cse3 variable */));
  TRACE_POP
}
int InvertedPendulum_functionJacLSJac29_column(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = InvertedPendulum_INDEX_JAC_LSJac29;
  InvertedPendulum_eqFunction_23(data, threadData, jacobian, parentJacobian);

  InvertedPendulum_eqFunction_24(data, threadData, jacobian, parentJacobian);
  
  TRACE_POP
  return 0;
}
int InvertedPendulum_functionJacD_column(void* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int InvertedPendulum_functionJacC_column(void* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int InvertedPendulum_functionJacB_column(void* data, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH
  TRACE_POP
  return 0;
}
int InvertedPendulum_functionJacA_column(void* inData, threadData_t *threadData, ANALYTIC_JACOBIAN *jacobian, ANALYTIC_JACOBIAN *parentJacobian)
{
  TRACE_PUSH

  DATA* data = ((DATA*)inData);
  int index = InvertedPendulum_INDEX_JAC_A;
  
  TRACE_POP
  return 0;
}


