import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0, 2*np.pi, 0.01)
y = np.sin(x)
z = np.cos(x)


plt.plot(x, y, x, z)

plt.xlabel('x values from 0 to 2pi')
plt.ylabel('sin(x) and cos(x)')

plt.axhline(y = 0, color = 'k')
plt.axvline(x = 0, color = 'k')

plt.title('Plot of sin and cos from 0 to 2pi')

plt.legend(['sin(x)', 'cos(x)'])

plt.show()
