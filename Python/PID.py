
import time

class PID:

    def __init__(self, P=0.0, I=0.0, D=0.0):
     
        self.Kp = P
        self.Ki = I
        self.Kd = D
        self.sample_time  = 0.00
        self.current_time = time.time()
        self.last_time  = self.current_time
        
        self.SetPoint = 0.0
        self.last_error = 0.0
        self.output = 0.0

        self.int_error = 0.0
        self.windup_guard = 20.0
        
        self.PTerm = 0.0
        self.ITerm = 0.0
        self.DTerm = 0.0

        self.max_out = 100
        self.min_out = -100

    def update(self, feedback_value):
    
        error = self.SetPoint - feedback_value
        
        self.current_time = time.time()
        dt        = self.current_time - self.last_time
        dt_error       = error - self.last_error
        
        if dt >= self.sample_time: 
            self.PTerm  = self.Kp * error
            self.ITerm += error * dt
 
            if self.ITerm < -self.windup_guard:
                self.ITerm = -self.windup_guard
            elif self.ITerm > self.windup_guard:
                self.ITerm = self.windup_guard

           
            self.DTerm = 0.0
            if dt > 0:
                self.DTerm = dt_error / dt
            

            self.last_time  = self.current_time
            self.last_error = error
            
            self.output = self.PTerm + self.Ki * self.ITerm + self.Kd * self.DTerm
            
            if self.output > self.max_out:
                self.output = self.max_out
            elif self.output < self.min_out:
                self.output = self.min_out
            

    def setKp(self, p):
        self.Kp = p 
    def setKi(self, i):
        self.Ki = i
    def setKd(self, d):
        self.Kd = d
    
    def setSampleTime(self,time):
        self.sample_time = time

    def setMaxOut(self,m):
        self.max_out = m
    def setMinOut(self,m):
        self.min_out = m

