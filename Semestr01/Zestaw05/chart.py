import random
import scipy as sp
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from subprocess import Popen, PIPE, STDOUT

def mesure(n):
    in_arr = [random.randint(0, n*10) for _ in range(0, n)]
    in_data = bytearray('\n'.join(map(str, in_arr)), 'ascii')

    p = Popen(['./SelectionSortComplexity.x'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
    out, err = p.communicate(input=in_data)

    return int(out.decode('ascii').strip())

def fit_function(x, a):
    return a * x**2

mesure_space = np.linspace(10, 10**5/2, num=20, dtype=int)
mesured = list(map(mesure, mesure_space))

[a], _ = curve_fit(fit_function, mesure_space, mesured)

fit_space = np.linspace(10, 10**5/2, num=500)
fit = list(map(lambda x: fit_function(x, a), fit_space))

plt.scatter(mesure_space, mesured)
plt.plot(fit_space, fit)
plt.legend(['zmierzona liość operacji dominujących', 'funkcja dopasowana: ' + str(round(a, 5)) + ' * x^2'])
plt.title('Pomiar ilośći operacji dominujących \n w zależności od liczby elementów dla selection sort')
plt.ylabel('operacje dominujące')
plt.xlabel('ilość elementów')
plt.grid()
plt.tight_layout()
plt.savefig('./chart.svg')