#!/usr/bin/env python3

import sys
import matplotlib
matplotlib.use ("Gtk3Cairo")
import matplotlib.pyplot as plt

data = eval(sys.stdin.read ())

X = []
Y = []
for (x, y) in data:
	X.append(x)
	Y.append(y)

plt.plot(X, Y)
plt.axis('equal')
plt.show()

