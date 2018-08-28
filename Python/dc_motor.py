from time import sleep
import RPi.GPIO as GPIO

OUT1  = 14
OUT2  = 15


def init():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(OUT1,  GPIO.OUT)
    GPIO.setup(OUT2,  GPIO.OUT)
    #p = GPIO.PWM(OUT1, 2000)   
    #p = GPIO.PWM(OUT2, 2000)
    #GPIO.output(OUT1, GPIO.LOW)
    #GPIO.output(OUT2, GPIO.LOW)
        

def cw(tf):
    GPIO.output(OUT1, GPIO.LOW)
    GPIO.output(OUT2, GPIO.HIGH)
    sleep(tf)
    #GPIO.cleanup()

def ccw(tf):
    GPIO.output(OUT1, GPIO.HIGH)
    GPIO.output(OUT2, GPIO.LOW)
    sleep(tf)
    #GPIO.cleanup()

#def stop(tf) 
    
#init()
#print "CW"
#cw(0.5)

#print "CCW"
#ccw(0.5)

#GPIO.cleanup()
