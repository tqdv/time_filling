import sys
import matplotlib
matplotlib.use ("Gtk3Cairo")
import matplotlib.pyplot as plt

data = eval(next(sys.stdin))

X = []
Y = []
for (x, y) in data:
	X.append(x)
	Y.append(y)

plt.plot(X, Y)
plt.axis('equal')
plt.show()

