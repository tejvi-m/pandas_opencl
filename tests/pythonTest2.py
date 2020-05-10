import time

import pandas as pd
import numpy as np
import sys

data2 = {'a':np.random.rand(int(sys.argv[1]) * 2) , 'b': np.random.rand(int(sys.argv[1]) * 2) ,
                               'c': np.random.rand(int(sys.argv[1]) * 2) , 'd': np.random.rand(int(sys.argv[1]) * 2)}

data1 = {'a':np.random.rand(int(sys.argv[1]) * 2) , 'b': np.random.rand(int(sys.argv[1]) * 2) ,
                               'c': np.random.rand(int(sys.argv[1]) * 2) , 'd': np.random.rand(int(sys.argv[1]) * 2)}
d1 = pd.DataFrame(data1)
d2 =  pd.DataFrame(data2)


num = int(sys.argv[2])
a1 = time.time()
 
if(num == 1):
    d1.add(d2)



if(num == 2):
    d1.add(d2)
    d1.sub(d2)


if(num == 3):
    d1.add(d2)
    d1.sub(d2)
    d1.transform(lambda x: x + 1)


if(num == 4):
    d1.add(d2)
    d1.sub(d2)
    d1.transform(lambda x: x + 1)
    d1.mul(d2)


if(num == 5):
    d1.add(d2)
    d1.sub(d2)
    d1.transform(lambda x: x + 1)
    d1.mul(d2)
    d1.div(d2)



if(num == 6):
    d1.add(d2)
    d1.sub(d2)
    d1.transform(lambda x: x + 1)
    d1.mul(d2)
    d1.div(d2)
    d1.sub(d2)

a2 = time.time()
print(a2 - a1)


# a1 = time.time()
# a.apply(np.sum)
# a2 = time.time()
# print(a2 - a1)
