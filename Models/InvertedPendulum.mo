model InvertedPendulum
  import SI = Modelica.SIunits;
  
  constant Real PI = 3.14159265359;
//  constant Real M = 1; // Mass of cart 
 // constant Real m = 1.5; // Mass of pendulum weight 
  //constant Real L = 1.0; // Length of pendulum
  //constant Real g = 9.82; // Gravitation
  
  parameter SI.Mass M = 1; // Mass of cart 
  parameter SI.Mass m = 1.5; // Mass of pendulum weight 
  parameter SI.Length L = 1.0; // Length of pendulum
  parameter SI.Acceleration g = 9.82; // Gravitation
  
  //SI.Angle theta(start=PI);    // Angle
  //SI.AngularVelocity theta_velo = der(theta);
  //SI.AngularAcceleration theta_accel = der(theta_velo);
  
  Real theta(start=PI/2);    
  // Angles:
  // 7/6 = 210, 5/4 = 225, 4/3 = 240, 17/12 = 255, 3/2 = 270
  // 5/6 = 150, 3/4 = 135 2/3 = 120, 7/12 = 105,  1/2 = 90
  
  Real theta_velo = der(theta);
  Real theta_accel = der(theta_velo);

  SI.Position x_pos(start=0);
  SI.Velocity x_vel = der(x_pos);
  SI.Acceleration x_acc = der(x_vel);
  
  input SI.Force F(start=0);
  output SI.Angle Y = theta;
equation
   (M + m) * x_acc - m * L * theta_accel * cos(theta) + m * L * theta_velo^2 *  sin(theta) = F;
    L * theta_accel - g * sin(theta) = x_acc * cos(theta);

annotation(
    Documentation); 
end InvertedPendulum;


