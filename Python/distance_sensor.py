import time
import RPi.GPIO as GPIO
from time import sleep

ECHO = 16
TRIG = 12
def init():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(ECHO, GPIO.IN)
    GPIO.setup(TRIG, GPIO.OUT)

def trigger_sensor():
    GPIO.output(TRIG, GPIO.LOW)
    GPIO.output(TRIG, GPIO.HIGH)
    sleep(0.000001)
    GPIO.output(TRIG, GPIO.LOW)

def pulse_in():
    trigger_sensor() 
    while GPIO.input(ECHO) == 0:
        continue
    timer = time.time()
    while GPIO.input(ECHO) == 1:
        continue
    distance = 340 * (time.time() - timer) / 2
    return distance


def get_distance(n = 5):
    length = pulse_in()
    length2 = 0
    j  = 1
    i = 1
    while i < n:
        current = pulse_in()
#        print "This is the current: " +str(current)
#        print "This is the avg length: " +str(length/x)
#        sleep(1)
#        print "This is the current: " + str(current)
#        print "This is the avg length: " + str(length/x)
        
        factor = current / (length / i)
         
        if (1.1 > factor) and (factor > 0.9): 
            i += 1 #= x+1
            length += current
        else:  
            j += 1   
            length2 += current
     
        if j == n:
            length = length2
            break       
        
    return length/n

#init()

#while True:
#    print "This is the distance: " + str(get_distance())
