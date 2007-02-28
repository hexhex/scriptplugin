#!/usr/bin/python

import sys

married_old = " is married to "
married_new = "married_to"
child_of_old = " is the child of "
child_of_new = "child_of"

if len(sys.argv) < 2:
    sys.exit(1)

f = file(sys.argv[1])
lines = f.readlines();
f.close()

if lines[0] == "#Text#\n":
    for i in lines[1:]:
        if i != '\n':
            i = i.lower()
            i = i.replace('.', '')
	    i = i.replace('\n', '')

            if i.find(married_old) != -1:
	        i = i.replace(married_old, ',')
	        i = married_new + "(" + i + ").\n"
	    elif i.find(child_of_old) != -1:
                i = i.replace(child_of_old, ',')
	        i = child_of_new + "(" + i + ").\n"
            
            print i,
else:
    for i in lines:
        print i,
