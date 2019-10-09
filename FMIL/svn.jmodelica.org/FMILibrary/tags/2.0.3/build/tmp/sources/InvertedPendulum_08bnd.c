/* update bound parameters and variable attributes (start, nominal, min, max) */
#include "InvertedPendulum_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

OMC_DISABLE_OPT
int InvertedPendulum_updateBoundVariableAttributes(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  /* min ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating min-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* max ******************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating max-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* nominal **************************************************** */
  
  infoStreamPrint(LOG_INIT, 1, "updating nominal-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  /* start ****************************************************** */
  infoStreamPrint(LOG_INIT, 1, "updating primary start-values");
  if (ACTIVE_STREAM(LOG_INIT)) messageClose(LOG_INIT);
  
  TRACE_POP
  return 0;
}

void InvertedPendulum_updateBoundParameters_0(DATA *data, threadData_t *threadData);

/*
equation index: 28
type: ALGORITHM

  assert(m >= 0.0, "Variable violating min constraint: 0.0 <= m, has value: " + String(m, "g"));
*/
OMC_DISABLE_OPT
static void InvertedPendulum_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  modelica_boolean tmp0;
  static const MMC_DEFSTRINGLIT(tmp1,56,"Variable violating min constraint: 0.0 <= m, has value: ");
  modelica_string tmp2;
  static int tmp3 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp3)
  {
    tmp0 = GreaterEq(data->simulationInfo->realParameter[3],0.0);
    if(!tmp0)
    {
      tmp2 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[3], (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp1),tmp2);
      {
        FILE_INFO info = {"/home/lapbottom/Programming/Exjobb/Models/InvertedPendulum.mo",6,3,6,28,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nm >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp3 = 1;
    }
  }
  TRACE_POP
}

/*
equation index: 29
type: ALGORITHM

  assert(M >= 0.0, "Variable violating min constraint: 0.0 <= M, has value: " + String(M, "g"));
*/
OMC_DISABLE_OPT
static void InvertedPendulum_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  modelica_boolean tmp4;
  static const MMC_DEFSTRINGLIT(tmp5,56,"Variable violating min constraint: 0.0 <= M, has value: ");
  modelica_string tmp6;
  static int tmp7 = 0;
  modelica_metatype tmpMeta[1] __attribute__((unused)) = {0};
  if(!tmp7)
  {
    tmp4 = GreaterEq(data->simulationInfo->realParameter[0],0.0);
    if(!tmp4)
    {
      tmp6 = modelica_real_to_modelica_string_format(data->simulationInfo->realParameter[0], (modelica_string) mmc_strings_len1[103]);
      tmpMeta[0] = stringAppend(MMC_REFSTRINGLIT(tmp5),tmp6);
      {
        FILE_INFO info = {"/home/lapbottom/Programming/Exjobb/Models/InvertedPendulum.mo",5,3,5,26,0};
        omc_assert_warning(info, "The following assertion has been violated %sat time %f\nM >= 0.0", initial() ? "during initialization " : "", data->localData[0]->timeValue);
        omc_assert_warning_withEquationIndexes(info, equationIndexes, MMC_STRINGDATA(tmpMeta[0]));
      }
      tmp7 = 1;
    }
  }
  TRACE_POP
}
OMC_DISABLE_OPT
void InvertedPendulum_updateBoundParameters_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  InvertedPendulum_eqFunction_28(data, threadData);
  InvertedPendulum_eqFunction_29(data, threadData);
  TRACE_POP
}
OMC_DISABLE_OPT
int InvertedPendulum_updateBoundParameters(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  InvertedPendulum_updateBoundParameters_0(data, threadData);
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

