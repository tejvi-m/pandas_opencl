import time

import pandas as pd
import numpy as np
import sys

data2 = {'a':np.random.rand(int(sys.argv[1]) * 2) , 'b': np.random.rand(int(sys.argv[1]) * 2) ,
                               'c': np.random.rand(int(sys.argv[1]) * 2) , 'd': np.random.rand(int(sys.argv[1]) * 2)}

data1 = {'a':np.random.rand(int(sys.argv[1]) * 2) , 'b': np.random.rand(int(sys.argv[1]) * 2) ,
                               'c': np.random.rand(int(sys.argv[1]) * 2) , 'd': np.random.rand(int(sys.argv[1]) * 2)}
a = pd.DataFrame(data1)
b =  pd.DataFrame(data2)



a.add(a)
a.sub(a)
a.transform(lambda x:  x + 1)
a.add(a)
a.add(a)
a1 = time.time()
a.add(b)
a2 = time.time()
print(a2 - a1)


# a1 = time.time()
# a.apply(np.sum)
# a2 = time.time()
# print(a2 - a1)
