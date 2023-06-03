# Import necessary
import matplotlib.pyplot as plt
import numpy as np

# Determining x-axis
x = np.arange(0, 2*np.pi, 0.0628)

# Reading from files
with open('../output/client_1.txt', 'r') as f1:
    first_line = f1.readline()
    client1_array = [[float(x) for x in line.split()] for line in f1]

with open('../output/client_2.txt', 'r') as f2:
    first_line = f2.readline()
    client2_array = [[float(x) for x in line.split()] for line in f2]
    
with open('../output/client_3.txt', 'r') as f3:
    first_line = f3.readline()
    client3_array = [[float(x) for x in line.split()] for line in f3]

# Closing open files
f1.close()
f2.close()
f3.close()

# Plotting data from every client on one graph
plt.plot(x, client1_array, x, client2_array, x, client3_array)

# Setting labels and making axis visible
plt.xlabel('x values from 0 to 2pi')
plt.ylabel('sin(x) and cos(x)')
plt.axhline(y = 0, color = 'k')
plt.axvline(x = 0, color = 'k')

# Draw graph
plt.show()
