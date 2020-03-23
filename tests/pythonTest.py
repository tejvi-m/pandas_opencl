import time

import pandas as pd
import numpy as np
import sys


a = pd.DataFrame(np.random.rand(int(sys.argv[1]) * 2) * 254, columns=["a"])
b = pd.DataFrame(np.random.rand(int(sys.argv[1]) * 2) * 254, columns=["a"])

# a1 = time.time()
# a.add(b)
# a2 = time.time()
# print(a2 - a1)

# a1 = time.time()
# a.sub(b)
# a2 = time.time()
# print(a2 - a1)
#
# a1 = time.time()
# a.mul(b)
# a2 = time.time()
# print( a2 - a1)

# a1 = time.time()
# a.div(b)
# a2 = time.time()
# print(a2 - a1)
#
#
a1 = time.time()
a.transform(lambda x:  -x)
a2 = time.time()
print(a2 - a1)


# a1 = time.time()
# a.apply(np.sum)
# a2 = time.time()
# print(a2 - a1)
