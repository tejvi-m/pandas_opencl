import time

import pandas as pd
import numpy as np

z = np.random.rand(99999999)
z1 = np.random.rand(99999999)

a1 = time.time()
x = z1 + z
a2 = time.time()
print(a2 - a1)

a = pd.Series(z)
b = pd.Series(z1)
a1 = time.time()
a.add(b)
a2 = time.time()
print(a2 - a1)

a1 = time.time()
c = a.add(b)
a2 = time.time()
print(a2 - a1)
# print(a[0])
# print(b[0])
# print(c[0])
#

print("this")
a1 = time.time()
a.mul(b)
a2 = time.time()
print(a2 - a1)

print("this2")
a1 = time.time()
z = a.mul(b)
a2 = time.time()
print(a2 - a1)


# print(z)
# print(z1)
# print(x)
