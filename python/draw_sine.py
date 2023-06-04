# -------------------------------------------------------------------------------
# Import necessary
import matplotlib.pyplot as plt
import numpy as np
import os
# -------------------------------------------------------------------------------
# Calculating number of files in directory
dir_path = r'/home/ubuntu/Desktop/IoT/iot-client-server/output'
num_of_files = 0
# Iterate directory
for path in os.listdir(dir_path):
	if os.path.isfile(os.path.join(dir_path, path)):
		num_of_files += 1
# -------------------------------------------------------------------------------
# Calculate x-axis values
x = np.arange(0, 2*np.pi, 0.0628)
# -------------------------------------------------------------------------------
# Reading from every file in directory & plotting graph
for i in range(num_of_files):
	file_name = '../output/client_' + str(i+1) + '.txt'
	with open(file_name, 'r') as f:
		first_line = f.readline()
		client_array = [[float(x) for x in line.split()] for line in f]
	f.close()
	plt.plot(x, client_array)
# -------------------------------------------------------------------------------
# Setting labels and making axis visible
plt.xlabel('x values from 0 to 2pi')
plt.ylabel('sin() values from all clients')
plt.axhline(y = 0, color = 'k')
plt.axvline(x = 0, color = 'k')
# -------------------------------------------------------------------------------
# Draw graph
plt.show()
# -------------------------------------------------------------------------------
