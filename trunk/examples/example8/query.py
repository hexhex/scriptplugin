#!/usr/bin/python

import sys

if len(sys.argv) < 2:
    sys.exit(1)

AAA = "AAA"
BBB = "BBB"
TEMP = "temp"

f = file(sys.argv[1])
lines = f.readlines();
f.close()

lines = ''.join(lines)
lines = lines.replace('\n','')
lines = lines.split('.')

for i in lines:
    if (i.find("&script") != -1) and (i.find("%%") != -1):
        count = 1
	name = ((i.split(":-")[0]).split('(')[0]).strip()
        temp_tail = (i.split(":-")[1]).split(',')

	tail = ['' for j in temp_tail]
	t = 0
	pholder = False
	for j in temp_tail:
	    if (pholder == True) and (j.find("%%") != -1):
	        tail[t - 1] = tail[t - 1] + ',' + j
	    else:
	        tail[t] = j
		t = t + 1

	    if j.find("%%") != -1:
	        pholder = True
	    else:
	        pholder = False

	var_start = 1
	for j in tail:
	    if j.find("&script") != -1:
	        script = j
		break
	    else:
	        var_start = var_start + 1

	depend = ['' for j in range(len(tail) - 1)]
	c = 0
	for j in tail:
	    if (j.endswith(")")) and (j.find("]") == -1):
	        depend[c] = j
	        c = c + 1

	script = script.replace("&script[",'')
	script = script.replace('\"','')
	# script = script.replace('\'','')
	marks = script.count("%%")
	command = script.split("%%")
	
	vars = ['' for j in range(marks)]
	v = 0
	for j in range(marks):
	    vars[v] = tail[var_start]
	    var_start = var_start + 1
	    v = v + 1
	
	outvar = ((vars[marks - 1].split("]"))[1]).strip("()")
	vars[marks - 1] = (vars[marks - 1].split("]"))[0]

	text_count = 0
	var_count = 0

	for j in range(marks + len(command) - 1):
	    
	    print TEMP + "_" + name + "_" + str(count) + "(" + BBB + ")" + ":-",

	    if count > 1:
	        print TEMP + "_" + name + "_" + str(count - 1) + "(" + AAA + "),",

	    for k in depend:
	        if k != '':
	            print k + ",",

	    print "&concat[",

	    if count == 1:
	        print "\"" + command[text_count] + "\"",
		text_count = text_count + 1
		print ",",
		print vars[var_count],
		var_count = var_count + 1

	    else:
	        print AAA + ",",
	        if (count % 2) == 0:
		    print "\"" + command[text_count] + "\"",
		    text_count = text_count + 1
		else:
		    print vars[var_count],
		    var_count = var_count + 1

	    print "](" + BBB + ")",
	    print "."
	    count = count + 1

	print i.split(":-")[0] + ":-",
	print TEMP + "_" + name + "_" + str(count - 1) + "(" + AAA + "),",
        print "&script[" + AAA + "](" + outvar + ")",
	print "."

    elif i != '':
        print i + "."

