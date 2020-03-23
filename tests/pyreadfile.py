import pandas as pd
from time import time
a = time()
pd.read_csv("test.csv")
b = time()
print(b - a)
