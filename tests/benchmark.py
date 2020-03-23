import numpy as np
import os
import scipy.stats

results = []

command = os.popen(' g++ -std=c++17 tests/cppTest.cpp -lOpenCL -O3 -w')
# command.close()

for j in [9, 99, 999, 9999, 99999, 999999, 9999999, 99999999]:
    xres = []
    for i in range(0, 5):
        command = os.popen('python tests/pythonTest.py ' + str(j))
        # print(command.read())
        z = float(command.read())
        xres.append(z)

        command.close()
        print(i, j, z)
    results.append(scipy.stats.gmean(xres))
    print("appended ", scipy.stats.gmean(xres[5:]))

print(results)
np.save("pyTx.npy", results)
