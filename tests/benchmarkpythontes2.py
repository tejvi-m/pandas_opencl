import numpy as np
import os
import scipy.stats

results  = []

# command = os.popen(' python tests/pythonTest.py')
# command.close()

for j in range(1, 7):
    xres = []
    for i in range(0, 6):
        command = os.popen(' python tests/pythonTest2.py 999999 ' + str(j))
        # print(command.read())
        z = float(command.read())
        xres.append(z)

        command.close()
        print(i, j, z)
    results.append(scipy.stats.gmean(xres))
    print("appended ", scipy.stats.gmean(xres))

print(results)
np.save("test1pthread.npy", results)
