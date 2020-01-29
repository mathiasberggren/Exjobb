import sys
from subprocess import check_output, call
import re
from collections import defaultdict
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def simulate_all_pendulums():
    base = ['TRAINING_MODE=0']
    pendulum_start_angle = ['7.6', '5.4', '4.3', '17.12', '3.2', '5.6', '3.4', '2.3', '7.12', '1.2']
    pendulum_m1 = [1.0, 1.5, 2.0]
    pendulum_m2 = [0.3, 0.5, 1.0]
    pendulum_length = [0.5, 1.0, 2.0] 

    # for loop this shit
    for start_value in pendulum_start_angle:
        for p_m1 in pendulum_m1:
            for p_l in pendulum_length:
                for p_m2 in pendulum_m2:
                    directory = './test_script/M'+str(p_m1)+'L'+str(p_l)+'m'+str(p_m2)
                    program_specific = base + ['START_ANGLE='+start_value, 'DIRECTORY='+directory]
                    # Create directory if does not exist
                    call(['mkdir', directory])
                    # Run program with all different pendulums
                    run_simulations(str(sys.argv[1])+'-'+str(start_value), directory, program_specific)

def train_all_models():
    base = ['TRAINING_MODE=1']
    controllers = [1, 2]
    print("About to start training, the following models will be trained:")
    print(controllers)
    print("Press enter to continue")
    sys.stdin.read(1)
    for controller in controllers: 
        # call(['make', 'clean'])
        print("Now training " + str(controller) + " controller")
        call(['make', 'clean'])
        call(['make', '-s', 'CONTROLLER_MODE=' + str(controller)]+base)
        call(['./train_model-' +str(controller)])
        


def run_simulations(path_to_exec, directory, program_specific = None):
    """ Takes in the path to the executable, directory where result is saved and program specific constants """
    program = path_to_exec
    controllers = [0, 1, 2, 3]
    for controller in controllers:
        call(['make', 'clean'])
        # '-s' make output is silent
        call(['make', '-s', 'CONTROLLER_MODE=' + str(controller), 'FILENAME=' + path_to_exec + '-' + str(controller)]+program_specific)
        call(['./'+str(path_to_exec)+'-'+str(controller)+'-0'])


if (len(sys.argv)-1) < 1:
    print("To run simulations run the script with: PATH_TO_EXECUTABLE")
    train_all_models()
else:
    simulate_all_pendulums()
