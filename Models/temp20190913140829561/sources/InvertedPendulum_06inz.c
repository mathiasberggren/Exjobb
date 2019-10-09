/* Initialization */
#include "InvertedPendulum_model.h"
#include "InvertedPendulum_11mix.h"
#include "InvertedPendulum_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void InvertedPendulum_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: SIMPLE_ASSIGN
x_pos = $START.x_pos
*/
void InvertedPendulum_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[2] /* x_pos STATE(1,x_vel) */ = data->modelData->realVarsData[2].attribute /* x_pos STATE(1,x_vel) */.start;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
theta_velo = $START.theta_velo
*/
void InvertedPendulum_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[1] /* theta_velo STATE(1,theta_accel) */ = data->modelData->realVarsData[1].attribute /* theta_velo STATE(1,theta_accel) */.start;
  TRACE_POP
}

/*
equation index: 3
type: SIMPLE_ASSIGN
theta = $START.theta
*/
void InvertedPendulum_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[0] /* theta STATE(1,theta_velo) */ = data->modelData->realVarsData[0].attribute /* theta STATE(1,theta_velo) */.start;
  TRACE_POP
}
extern void InvertedPendulum_eqFunction_16(DATA *data, threadData_t *threadData);


/*
equation index: 10
type: LINEAR

<var>theta_accel</var>
<row>

</row>
<matrix>
</matrix>
*/
OMC_DISABLE_OPT
void InvertedPendulum_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  /* Linear equation system */
  int retValue;
  double aux_x[1] = { data->localData[1]->realVars[12] /* theta_accel variable */ };
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving linear system 10 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  retValue = solve_linear_system(data, threadData, 0, &aux_x[0]);
  
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,10};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving linear system 10 failed at time=%.15g.\nFor more information please use -lv LOG_LS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[12] /* theta_accel variable */ = aux_x[0];
  TRACE_POP
}
extern void InvertedPendulum_eqFunction_26(DATA *data, threadData_t *threadData);

extern void InvertedPendulum_eqFunction_27(DATA *data, threadData_t *threadData);

extern void InvertedPendulum_eqFunction_18(DATA *data, threadData_t *threadData);


/*
equation index: 14
type: SIMPLE_ASSIGN
x_vel = $START.x_vel
*/
void InvertedPendulum_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  data->localData[0]->realVars[3] /* x_vel STATE(1,x_acc) */ = data->modelData->realVarsData[3].attribute /* x_vel STATE(1,x_acc) */.start;
  TRACE_POP
}
extern void InvertedPendulum_eqFunction_17(DATA *data, threadData_t *threadData);

OMC_DISABLE_OPT
void InvertedPendulum_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  InvertedPendulum_eqFunction_1(data, threadData);
  InvertedPendulum_eqFunction_2(data, threadData);
  InvertedPendulum_eqFunction_3(data, threadData);
  InvertedPendulum_eqFunction_16(data, threadData);
  InvertedPendulum_eqFunction_10(data, threadData);
  InvertedPendulum_eqFunction_26(data, threadData);
  InvertedPendulum_eqFunction_27(data, threadData);
  InvertedPendulum_eqFunction_18(data, threadData);
  InvertedPendulum_eqFunction_14(data, threadData);
  InvertedPendulum_eqFunction_17(data, threadData);
  TRACE_POP
}


int InvertedPendulum_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  InvertedPendulum_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}


int InvertedPendulum_functionInitialEquations_lambda0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}
int InvertedPendulum_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

