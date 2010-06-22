#!/usr/bin/python

import sys

months = [0,0,3,3,6,1,4,6,2,5,0,3,5]
days = ["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"]

if len(sys.argv) < 4:
    sys.exit(1)

day = int(sys.argv[1])
month = int(sys.argv[2])
year = int(sys.argv[3])

d = day % 7
m = months[month]
y = ((year % 100) + ((year % 100) / 4)) % 7
h = (((year / 100) % 4) - 3) * (-2)

if (month == 1) or (month == 2):
    l = -1
else:
    l = 0

result = (d + m + y + h + l) % 7

if (result >= 0) and (result <= 6):
    print days[result],

