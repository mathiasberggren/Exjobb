model InvertedPendulumSim
  InvertedPendulum_me_FMU invertedPendulum_me_FMU1 annotation(
    Placement(visible = true, transformation(origin = {69, -9}, extent = {{-23, -23}, {23, 23}}, rotation = 0)));
  Modelica.Blocks.Sources.Clock clock1 annotation(
    Placement(visible = true, transformation(origin = {-86, -32}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Logical.And and1 annotation(
    Placement(visible = true, transformation(origin = {-38, -34}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.Constant const(k = 10)  annotation(
    Placement(visible = true, transformation(origin = {-84, 10}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Math.MultiProduct multiProduct1(nu = 2)  annotation(
    Placement(visible = true, transformation(origin = {4, 2}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
  Modelica.Blocks.Sources.IntegerConstant integerConstant1(k = 20)  annotation(
    Placement(visible = true, transformation(origin = {-74, 48}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation
  connect(invertedPendulum_me_FMU1.F, multiProduct1.y) annotation(
    Line(points = {{44, 8}, {28, 8}, {28, 2}, {16, 2}, {16, 2}}, color = {0, 0, 127}));
  connect(integerConstant1.y, multiProduct1.u[2]) annotation(
    Line(points = {{-62, 48}, {-28, 48}, {-28, 2}, {-6, 2}}, color = {255, 127, 0}));
  connect(and1.y, multiProduct1.u[1]) annotation(
    Line(points = {{-26, -34}, {-18, -34}, {-18, 2}, {-6, 2}}, color = {255, 0, 255}));
  connect(const.y, and1.u1) annotation(
    Line(points = {{-72, 10}, {-50, 10}, {-50, -34}}, color = {0, 0, 127}));
  connect(clock1.y, and1.u2) annotation(
    Line(points = {{-74, -32}, {-57, -32}, {-57, -42}, {-50, -42}}, color = {0, 0, 127}));
  annotation(
    uses(Modelica(version = "3.2.2")));end InvertedPendulumSim;