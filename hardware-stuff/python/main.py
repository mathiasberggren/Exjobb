import serial
import RPi.GPIO as GPIO
import PID
import numpy as np
from scipy.interpolate import spline
#import dc_motor as motor
import distance_sensor as dist
import time
#import angle_sensor as angle
MOTOR_OUT1 = 14
MOTOR_OUT2 = 15

ser = serial.Serial('/dev/ttyACM0', 115200)
dist.init()
def main():
    GPIO.setmode(GPIO.BCM)

    #angle.init() 
    #INIT MOTOR#
    GPIO.setup(MOTOR_OUT1, GPIO.OUT)
    GPIO.setup(MOTOR_OUT2, GPIO.OUT)
    pwm1 = GPIO.PWM(MOTOR_OUT1, 2000)
    pwm2 = GPIO.PWM(MOTOR_OUT2, 2000)
    pwm1.start(0)
    pwm2.start(0)
    #INIT MOTOR#

    #INIT PID CONTROLLERS#
    PID_rot = PID.PID(4, 0.0, 0.0)
    PID_rot.SetPoint = 505
    PID_rot.setSampleTime(0.01)
    
#    PID_lin = PID.PID(1, 0.01, 0.1)
#    PID_lin.SetPoint = 0.55
#    PID_lin.setSampleTime(0.01)
    
    theta = 0
 #   dist = 0
    #INIT PID CONTROLLERS#

    simulation_time = 10
    
#    feedback_list_rot = []
#    feedback_list_lin = []
#    time_list         = []
#    setpoint_list_rot = [] 
#    setpoint_list_lin = [] 
 #   feedback_lin = 0
 #   feedback_rot = 0
 #   previous_timestamp = time.time()
 #   end_time = previous_timestamp + simulation_time
   
        
    while True:#(time.time() <= end_time):
        #current_timestamp = time.time()
        #time_delta = current_timestamp - previous_timestamp
        dist, theta = update_values()
        if (dist < 0.20 or dist > 0.9): # or (theta < 700  and theta > 350)):
            print 'This is dist: ' + str(dist) + '\nThis is theta: ' + str(theta)
            return
     #   PID_lin.update(dist)
     #   output = PID_lin.output
     #   PID_rot.SetPoint = output
        PID_rot.update(theta)
        
        output = PID_rot.output
        if output >= 0:
            pwm1.ChangeDutyCycle(output)
            pwm2.ChangeDutyCycle(0)
        else:
            pwm1.ChangeDutyCycle(0)
            pwm2.ChangeDutyCycle(-output) 
    
def update_values():
    distance = float(dist.pulse_in())
    angle = 0
    while True:
        try: 
            angle = int(ser.readline())
            break
        except ValueError:
            continue 
#    try:
#        return float(dist.pulse_in()), int(ser.readline())
#    except ValueError:
#        update_values()
#   print 'upidating value! dist: ' + str(distance) + ' angle: ' + str(angle)
    return distance, angle
    
    """ 
        feedback_list.append(output)

        PID_rot.update(output) 
        output = PID_rot.output
        
             
        
        setpoint_list_rot.append(
        time.list.append(current_timestamp)
    """      

def plot(feedback_list, setpoint_list, time_list):
    time_sm = np.array(time_list)
    time_smooth = np.linspace(time_sm.min(), time_sm.max(), 300)
    feedback_smooth = spline(time_list, feedback_list, time_smooth)
 

    plt.plot(time_smooth, feedback_smooth)
    plt.plot(time_list, setpoint_list)
    plt.xlim((0, L))
    plt.ylim((min(feedback_list)-0.5, max(feedback_list)+0.5))
    plt.xlabel('time (s)')
    plt.ylabel('PID (PV)')
    plt.title('TEST PID')
 
    plt.ylim((1-0.5, 1+0.5)) 
  
    plt.grid(True)
    plt.show()
        
main()
GPIO.cleanup()
#motor.accel_test()
#motor.step(200)
#motor.cw_direction()
#motor.accel_test()
#motor.step(100)
#motor.ccw_step()
#motor.cw_step(600)
#motor.ccw_step(600)
#motor.cw_step(200)
#GPIO.cleanup()

