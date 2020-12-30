#!/usr/bin/env python3

import sys
data = eval(sys.stdin.read())

print ('[')
ff = False
for i, e in enumerate(data):
    if ff:
        print(',')
    ff = True
    x, y = e
    print('{"x": ' + str(x) + ', "y": ' + str(-y) + '}')
print (']')
