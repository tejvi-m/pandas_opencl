import numpy as np
import os
import scipy.stats

results  = []

command = os.popen(' g++ -lpthread -std=c++17 tests/test1_mem_models.cpp -lOpenCL -O3 -w')
command.close()

for j in [9, 99, 999, 9999, 99999, 999999, 9999999]:
    xres = []
    for i in range(0, 10):
        command = os.popen('./a.out ' + str(j))
        # print(command.read())
        z = float(command.read())
        xres.append(z)

        command.close()
        print(i, j, z)
    results.append(scipy.stats.gmean(xres[1:]))
    print("appended ", scipy.stats.gmean(xres[1:]))

print(results)

