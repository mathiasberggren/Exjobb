model Exjobb
  InvertedPendulum invertedPendulum1(theta(start = 0))  annotation(
    Placement(visible = true, transformation(origin = {19, 33}, extent = {{-31, -31}, {31, 31}}, rotation = 0)));
  Modelica.Blocks.Continuous.PID PID annotation(
    Placement(visible = true, transformation(origin = {-66, 28}, extent = {{-10, -10}, {10, 10}}, rotation = 0)));
equation


annotation(
    Diagram,
    uses(Modelica(version = "3.2.2")));end Exjobb;