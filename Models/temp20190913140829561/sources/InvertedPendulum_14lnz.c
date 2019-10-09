/* Linearization */
#include "InvertedPendulum_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

const char *InvertedPendulum_linear_model_frame()
{
  return "model linear_InvertedPendulum\n  parameter Integer n = 4 \"number of states\";\n  parameter Integer p = 1 \"number of inputs\";\n  parameter Integer q = 1 \"number of outputs\";\n"
  "\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[p] = %s;\n"
  "\n"
  "  parameter Real A[n, n] = [%s];\n"
  "  parameter Real B[n, p] = [%s];\n"
  "  parameter Real C[q, n] = [%s];\n"
  "  parameter Real D[q, p] = [%s];\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[p](start=u0);\n"
  "  output Real y[q];\n"
  "\n"
  "  Real 'x_theta' = x[1];\n""  Real 'x_theta_velo' = x[2];\n""  Real 'x_x_pos' = x[3];\n""  Real 'x_x_vel' = x[4];\n"
  "  Real 'u_F' = u[1];\n"
  "  Real 'y_Y' = y[1];\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linear_InvertedPendulum;\n";
}
const char *InvertedPendulum_linear_model_datarecovery_frame()
{
  return "model linear_InvertedPendulum\n  parameter Integer n = 4 \"number of states\";\n  parameter Integer p = 1 \"number of inputs\";\n  parameter Integer q = 1 \"number of outputs\";\n  parameter Integer nz = 6 \"data recovery variables\";\n"
  "\n"
  "  parameter Real x0[4] = %s;\n"
  "  parameter Real u0[1] = %s;\n"
  "  parameter Real z0[6] = %s;\n"
  "\n"
  "  parameter Real A[n, n] = [%s];\n"
  "  parameter Real B[n, p] = [%s];\n"
  "  parameter Real C[q, n] = [%s];\n"
  "  parameter Real D[q, p] = [%s];\n"
  "  parameter Real Cz[nz, n] = [%s];\n"
  "  parameter Real Dz[nz, p] = [%s];\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[p](start=u0);\n"
  "  output Real y[q];\n"
  "  output Real z[nz];\n"
  "\n"
  "  Real 'x_theta' = x[1];\n""  Real 'x_theta_velo' = x[2];\n""  Real 'x_x_pos' = x[3];\n""  Real 'x_x_vel' = x[4];\n"
  "  Real 'u_F' = u[1];\n"
  "  Real 'y_Y' = y[1];\n"
  "  Real 'z_$cse2' = z[1];\n""  Real 'z_$cse3' = z[2];\n""  Real 'z_F' = z[3];\n""  Real 'z_Y' = z[4];\n""  Real 'z_theta_accel' = z[5];\n""  Real 'z_x_acc' = z[6];\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linear_InvertedPendulum;\n";
}
#if defined(__cplusplus)
}
#endif

