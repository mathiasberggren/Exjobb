import sys
from subprocess import check_output, call
import re
from collections import defaultdict
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def simulate_all_pendulums():
    program_specific = ['TRAINING_MODE=0']
    pendulum_start_angle = ['3.14']
    pendulum_m1 = [1.0]
    pendulum_m2 = [0.3] #, 0.6, 1.5]
    pendulum_length = [0.5] #, 1.0] 
    # Generate some kind of pendulum model with different parameters
    # then for loop this shit
    for p_m1 in pendulum_m1:
        for p_l in pendulum_length:
            for p_m2 in pendulum_m2:
                directory = 'M'+str(p_m1)+'L'+str(p_l)+'m'+str(p_m2)
                # Create directory if does not exist
                call(['mkdir', directory])
                for start_value in pendulum_start_angle:
                    run_subprogram(str(sys.argv[1])+'-'+str(start_value), directory, program_specific)

def run_subprogram(path_to_exec, directory, program_specific = None):
    """ Takes in the path to the executable, directory where result is saved and program specific constants """
    program = path_to_exec
    controllers = [1, 2, 3]
    for controller in controllers:
        call(['make', 'clean'])
        # '-s' suppresses warnings from matplotlib
        call(['make', '-s', 'CONTROLLER_MODE=' + str(controller), "DIRECTORY=" + directory,'FILENAME=' + path_to_exec + '-' + str(controller)]+program_specific)
        call(['./'+str(path_to_exec)+'-'+str(controller)+'-0'])


if (len(sys.argv)-1) < 1:
    print("Call the script with: PATH_TO_EXECUTABLE")
    quit()
else:
    simulate_all_pendulums()
