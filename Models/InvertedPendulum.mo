model InvertedPendulum
  import SI = Modelica.SIunits;
  
  constant Real PI = 3.14159265359;
  parameter SI.Mass M = 1; // Mass of cart 
  parameter SI.Mass m = 0.3; // Mass of pendulum weight 
  parameter SI.Length l = 0.5; // Length of pendulum
  parameter SI.Acceleration g = 9.82; // Gravitation
  
  //SI.Angle theta(start=PI);    // Angle
  //SI.AngularVelocity theta_velo = der(theta);
  //SI.AngularAcceleration theta_accel = der(theta_velo);
  
  Real theta(start=2*PI/3);    // Angle 7/6 = 210, 5/4 = 225, 4/3 = 240, 5/6 = 150, 3/4 = 135 2/3 = 120
  Real theta_velo = der(theta);
  Real theta_accel = der(theta_velo);

  SI.Position x_pos(start=0);
  SI.Velocity x_vel = der(x_pos);
  SI.Acceleration x_acc = der(x_vel);
  
  input SI.Force F(start=0);
  output SI.Angle Y = theta;
equation
   (M + m) * x_acc - m * l * theta_accel * cos(theta) + m * l * theta_velo^2 *  sin(theta) = F;
    l * theta_accel - g * sin(theta) = x_acc * cos(theta);

annotation(
    Documentation); 
end InvertedPendulum;


