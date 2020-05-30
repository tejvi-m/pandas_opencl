from DataFrame import *

x = DataFrame("example.csv")
y = x.copy()
z = x.copy()
d = x.copy()
Z = x.copy()

x.add(y)
y.sub(x)
x.transform("x + 1")

y.showDF()

z.add(d)
y.add(x)
x.add(Z)
x.showDF()


y.add(x)
x.add(y)

y.dropNA(0)

y.add(x)
x.add(y)
y.add(x)
x.add(y)
