#!/usr/bin/env python3

import sys
data = eval(sys.stdin.read())

for i, e in enumerate(data):
    x, y = e
    print('<use href="#hexagon" id="hexagon' + str(i) + '" class="hex" x="' + str(x) + '" y="' + str(-y) + '"/>')

