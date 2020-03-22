import time

import pandas as pd
import numpy as np


a = pd.DataFrame(np.random.rand(99999999 * 2) * 254, columns=["a"])
b = pd.DataFrame(np.random.rand(99999999* 2) * 254, columns=["a"])

a1 = time.time()
a.add(b)
a2 = time.time()
print("addition: ", a2 - a1)

a1 = time.time()
a.sub(b)
a2 = time.time()
print("subtraction: " , a2 - a1)

a1 = time.time()
a.mul(b)
a2 = time.time()
print("multiply: " , a2 - a1)

a1 = time.time()
a.div(b)
a2 = time.time()
print("div: " , a2 - a1)


a1 = time.time()
a.transform(lambda x:  -x)
a2 = time.time()
print("transform: " , a2 - a1)


a1 = time.time()
a.apply(np.sum)
a2 = time.time()
print("apply: " , a2 - a1)
