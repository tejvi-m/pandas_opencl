import numpy as np
import os
import scipy.stats

results  = []

command = os.popen(' g++ -lpthread -std=c++17 tests/test2_serial.cpp -lOpenCL -O3 -w')
command.close()

for j in range(1, 7):
    xres = []
    for i in range(0, 6):
        command = os.popen('./a.out 999999 ' + str(j))
        # print(command.read())
        z = float(command.read())
        xres.append(z)

        command.close()
        print(i, j, z)
    results.append(scipy.stats.gmean(xres[1:]))
    print("appended ", scipy.stats.gmean(xres[1:]))

print(results)
np.save("test1pthread.npy", results)
