#!/usr/bin/python

import sys

ID = "tetra"

if len(sys.argv) < 2:
    sys.exit(1)

f = file(sys.argv[1])
lines = f.readlines();
f.close()

lines = ''.join(lines)
lines = lines.replace('\n','')
lines = lines.split('.')

count = 0
for i in lines:
    if i != '':
        lines[count] = i + '.'
    else:
        lines[count] = ''
    count = count + 1

lhs = ['' for i in range(len(lines))]
count = 0

for i in lines:
    if i.find(":-") != -1:
        lhs[count] = (((i.split(":-"))[0].strip()).split('('))[0]
        count = count + 1

for i in lines:
    for j in lhs:
        if j != '':
            i = i.replace(j + '(',j + '_' + ID + '(')

    print i
