/* Algebraic */
#include "InvertedPendulum_model.h"

#ifdef __cplusplus
extern "C" {
#endif


/* forwarded equations */
extern void InvertedPendulum_eqFunction_18(DATA* data, threadData_t *threadData);

static void functionAlg_system0(DATA *data, threadData_t *threadData)
{
    InvertedPendulum_eqFunction_18(data, threadData);
}
/* for continuous time variables */
int InvertedPendulum_functionAlgebraics(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  
  data->simulationInfo->callStatistics.functionAlgebraics++;
  
  functionAlg_system0(data, threadData);

  InvertedPendulum_function_savePreSynchronous(data, threadData);
  
  TRACE_POP
  return 0;
}

#ifdef __cplusplus
}
#endif
