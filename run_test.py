import sys
import re
from subprocess import check_output, call
import re
from collections import defaultdict
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math


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

def plot_all_models():
    pendulum_start_angle = ['7.6', '5.4', '4.3', '17.12', '3.2', '5.6', '3.4', '2.3', '7.12'] #'1.2']
    pendulum_m1 = [1.0, 1.5, 2.0]
    pendulum_m2 = [0.3, 0.5, 1.0]
    pendulum_length = [0.5, 1.0, 2.0] 

    for p_m1 in pendulum_m1:
        for p_l in pendulum_length:
            for p_m2 in pendulum_m2:
                directory = './test_script/M'+str(p_m1)+'L'+str(p_l)+'m'+str(p_m2)
                palette = plt.get_cmap('Set2')
                # fig, subplot = plt.subplot(3, 3, 1)
                fig = plt.figure(figsize=[10, 8])
                fig.subplots_adjust(left=0.10, right=0.95, top=0.82, bottom = 0.10)
                for index, start_value in enumerate(pendulum_start_angle):
                    # Run plot with all different pendulums
                    controllers = [0, 1, 2, 3]
                    filename = directory+"/simulate_pendulum-"+start_value
                    data = read_data(controllers, filename)
                    ylimmax = []
                    ylimmin = []
                    df = pd.DataFrame({'x': data[4], 'PID': data[0], 'NN': data[1], 'LM' : data[2], 'Tree' : data[3]})
                    plt.subplot(3, 3, index+1)
                    
                    plt.plot('x','PID', data=df, marker='', color=palette(0), linewidth=1)
                    plt.plot('x','NN', data=df, marker='', color=palette(1), linewidth=1)
                    plt.plot('x','LM', data=df, marker='', color=palette(2), linewidth=1)
                    plt.plot('x','Tree', data=df, marker='', color=palette(3), linewidth=1)
                    # If max / min to be changed for each graph
                    # for num in controllers:
                        # ylimmin.append(min(data[num]))
                        # ylimmax.append(max(data[num]))
                    # plt.ylim(-2, 2)
                    plt.ylim(-90, 90)
                    plt.xlim(0,10)

                    if (index+1) in range(7) :
                        plt.tick_params(labelbottom=False)
                    if (index+1) not in [1,4,7] :
                        plt.tick_params(labelleft=False)
                        # plt.tick_params(
                    starting_angle = re.findall('(\d+)', start_value)
                    start_angle_degrees = int(round((float(starting_angle[0])\
                        /float(starting_angle[1])*math.pi) * (180.0 / math.pi)))
                    plt.title("Starting angle = " + str(start_angle_degrees)+u'\xb0', loc='left', fontsize=10, fontweight=2, color=palette(1) )

                plt.suptitle('            Cart Mass: '+str(p_m1)+'\n   Pendulum Mass: '+str(p_m2)+'\nPendulum Length: '+str(p_l), fontsize=15)
                fig.text(0.5, 0.04, 'Time (s)', ha='center', va='center', fontsize=15)
                # plt.xlabel("Time")
                fig.text(0.04, 0.5, 'Angle displacement ('+u'\xb0'+')', ha='center', va='center', fontsize=15, rotation='vertical')
                #plt.ylabel("Angle") 
                fig.legend(['PID', 'Neural Network', 'Linear Model', 'Tree'],
                    loc="upper right",   # Position of legend
                    borderaxespad=0.5,    # Small spacing around legend box
                    title="Controllers",  # Title for the legend
                )
                # plt.legend() 
                fig.savefig(directory+".png")
                print("Created and saved plot @ "+directory+".png")
                plt.close(fig)

def read_data(controllers, filename):
    data = [[] for _ in range(len(controllers) + 1)]
    for controller in controllers:
        file_obj = open(filename+ '-' + str(controller) + '.txt', "r")
        for line in file_obj:
            words = line.split()
            if controller == 0:
                data[4].append(float(words[0]))
            # data[controller].append((float(words[1]) * 180) / math.pi)
            data[controller].append(-float(words[3])* 180 / math.pi)

    return data;


                        
                                
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


print("Welcome!\nThese modes are avaiable for the script:\n\n\t$ python run_test.py <PATH_TO_EXECUTABLE> - run simulations\n\t$ python run_test.py plot - Gather plots\n\t$ python run_test.py - Start training\n\n")
if (len(sys.argv)-1) < 1:
    train_all_models()
elif str(sys.argv[1]) == "plot" :
    plot_all_models()
else:
    simulate_all_pendulums()
