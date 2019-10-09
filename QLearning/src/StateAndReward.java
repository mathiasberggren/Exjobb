public class StateAndReward {

	final static double noOfStates = 8;
	
	/* State discretization function for the angle controller */
	public static String getStateAngle(double angle, double vx, double vy) {
		
		//String state = "OneStateToRuleThemAll";
		/* TODO: IMPLEMENT THIS FUNCTION */
			String s = String.valueOf(discretize(angle, (int)noOfStates, -Math.PI, Math.PI));
			//System.out.println(s);
			return String.valueOf(discretize(angle, (int)noOfStates, -Math.PI, Math.PI));
	}

	/* Reward function for the angle controller */
	public static double getRewardAngle(double angle, double vx, double vy) {

		/* TODO: IMPLEMENT THIS FUNCTION */
		
		
		return Math.PI - Math.abs(angle);
		
		
		/*double pos = Double.parseDouble(getStateAngle(angle, vx, vy)); // Our angle
		double top = (noOfStates / 2) - 1; // Straight up angle
		
		if(noOfStates - 2 <= pos)
			pos -= 1.000000001;
		
		if(1 > pos && pos >= 0)
			pos = pos + 1;
		
		if(pos <= top && pos > 1)   //If we're on left half
			reward = pos / top;
		else{						//If we're on the right half
			pos = pos % top;      
			pos = top - pos;
			reward = pos / top;
		}
				
				
				
		return Math.pow(reward, 2);*/
		//return Math.pow(Math.PI,2) - Math.pow(angle, 2);
		
		//return  Math.pow(1 / (Math.abs(angle) + 1), 2);
		
		//return 10 - Math.abs(Math.pow(angle, 2));
		
			
	}

	/* State discretization function for the full hover controller */
	public static String getStateHover(double angle, double vx, double vy) {

		/* TODO: IMPLEMENT THIS FUNCTION */
		
		int anglestate = discretize(angle, 8, -Math.PI, Math.PI);
		int vxstate = discretize(vx, 6, -4, 4);
		int vystate = discretize(vy, 6, -4, 4);
		return anglestate+"/"+vxstate+"/"+vystate;
		
//		String state = "OneStateToRuleThemAll2";
		
		//int anglestate = discretize(angle, (int)noOfStates, -Math.PI, Math.PI);
		//	int anglestate = discretize(angle, 4, -0,3, 0,3);
		
		//int vxstate = discretize(vx, 5, -3, 3);
		
		//int vystate = discretize(vy, 9, -3, 3);
		
		/*
	int anglestate = 0;
	
	
		if(angle > 0.5)
			anglestate = 0;
		else if(angle > 0.2)
			anglestate = 2;
		else if(angle <= 0.2 && angle > 0)
			anglestate = 4;
		else if(angle < -0.5)
			anglestate = 1;
		else if(angle < -0.2)
			anglestate = 3;
		else if(angle >= -0.2)
			anglestate = 5;
		else 
			anglestate = 999;
	*/	/*
		int vxstate = 0;

		if(vx > 3)
			vxstate = 0;
		else if(vx > 1)
			vxstate = 1;
		else if(vx > 0.5)
			vxstate = 2;
		else if(vx <= 0.5 && vx > 0)
			vxstate = 3;
		else if(vx < -3)
			vxstate = 4;
		else if(vx < -1)
			vxstate = 5;
		else if(vx < -0.5)
			vxstate = 6;
		else if(vx >= -0.5)
			vxstate = 7;
		else
			vxstate = 999;
		
		int vystate = 0;
		
		if(vy > 3)
			vystate = 0;
		else if(vy > 1)
			vystate = 1;
		else if(vy > 0.5)
			vystate = 2;
		else if(vy <= 0.5 && vy > 0)
			vystate = 3;
		else if(vy < -3)
			vystate = 4;
		else if(vy < -1)
			vystate = 5;
		else if(vy < -0.5)
			vystate = 6;
		else if(vy >= -0.5)
			vystate = 7;
		else
			vystate = 999;
				
		*/
		
		
		//return String.valueOf(discretize(angle, (int)noOfStates, -Math.PI, Math.PI));
		
	
	}

	/* Reward function for the full hover controller */
	public static double getRewardHover(double angle, double vx, double vy) {
		
		/* TODO: IMPLEMENT THIS FUNCTION */
		double reward = 0;
				
		double angleReward = getRewardAngle(angle, vx, vy); 
		
		double hoverReward = 0;
		
		hoverReward += Math.PI - Math.abs(vx);
		hoverReward += Math.PI - Math.abs(vy);
		
		reward += hoverReward + angleReward; 

		return reward;
		/*double stateY = discretize(vy, 11, -3, 3);
		double stateX = discretize(vx, 5, -3, 3);
		double diffY = Math.abs(stateY - 5);
		double diffX = Math.abs(stateX - 2);
		//System.out.println("Vårat state i Y-led: " + stateY + " och vårat state i X-led: " + stateX);
		double hoverX = 5/(1 + diffX*diffX);
		double hoverY = 5/(1 + diffY*diffY*diffY);
	
		double hoverReward = hoverX + hoverY;*/
		//reward = angleReward + hoverReward;
		//hoverReward += 3 - vx*vx;
		//hoverReward += 4 - vy*vy;
		/*
		if(Math.abs(vx) <= Math.PI)
			hoverReward = Math.pow(Math.PI, 2) - Math.pow(vx, 2);
		else 
			hoverReward -= Math.abs(vx);
		
		if(Math.abs(vy) <= Math.PI)
			hoverReward += Math.pow(Math.PI, 2) - Math.pow(vy, 2);
		else
			hoverReward -= Math.abs(vy); 
		*/
		//hoverReward += Math.pow(Math.PI, 2) - Math.PI / (Math.pow(vx, 2) + 1);
		//hoverReward += Math.PI / (Math.pow(vy, 2) + 1);
		
		
		
		//hoverReward += (Math.PI*Math.PI - Math.abs(vx)) / Math.PI;
		//hoverReward += (Math.PI*Math.PI - Math.abs(vy)) / Math.PI;
		/*
		if(Math.abs(angle) < 0.05)
			angleReward += 3 ;//- Math.abs(angle)*2;

		if(Math.abs(vy) < 0.5)	
			hoverReward += 2 ; // - Math.abs(vy)*2;
		
		if(Math.abs(vx) < 0.5)
			hoverReward += 1 ; // - Math.abs(vx)*2;
		
		if(Math.abs(vx) < 0.5 && Math.abs(vy) < 0.5)
			hoverReward += 5;
		
		if(Math.abs(vx) < 0.5 && Math.abs(vy) < 0.5 && angle < 0.05)
			reward += 10; e
	*/
		
	}

	// ///////////////////////////////////////////////////////////
	// discretize() performs a uniform discretization of the
	// value parameter.
	// It returns an integer between 0 and nrValues-1.
	// The min and max parameters are used to specify the interval
	// for the discretization.
	// If the value is lower than min, 0 is returned
	// If the value is higher than min, nrValues-1 is returned
	// otherwise a value between 1 and nrValues-2 is returned.
	//
	// Use discretize2() if you want a discretization method that does
	// not handle values lower than min and higher than max.
	// ///////////////////////////////////////////////////////////
	public static int discretize(double value, int nrValues, double min,
			double max) {
		if (nrValues < 2) {
			return 0;
		}

		double diff = max - min;

		if (value < min) {
			return 0;
		}
		if (value > max) {
			return nrValues - 1;
		}

		double tempValue = value - min;
		double ratio = tempValue / diff;

		return (int) (ratio * (nrValues - 2)) + 1;
	}

	// ///////////////////////////////////////////////////////////
	// discretize2() performs a uniform discretization of the
	// value parameter.
	// It returns an integer between 0 and nrValues-1.
	// The min and max parameters are used to specify the interval
	// for the discretization.
	// If the value is lower than min, 0 is returned
	// If the value is higher than min, nrValues-1 is returned
	// otherwise a value between 0 and nrValues-1 is returned.
	// ///////////////////////////////////////////////////////////
	public static int discretize2(double value, int nrValues, double min,
			double max) {
		double diff = max - min;

		if (value < min) {
			return 0;
		}
		if (value > max) {
			return nrValues - 1;
		}

		double tempValue = value - min;
		double ratio = tempValue / diff;

		return (int) (ratio * nrValues);
	}

}
