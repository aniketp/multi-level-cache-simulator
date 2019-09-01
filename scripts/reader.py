import sys, os
import numpy as np
import glob

print "No. of Cold Misses for the traces:"
for filename in glob.glob("../../assn1/output/*.out"):
	file = np.loadtxt(filename,delimiter=' ',dtype=int)
	d = {}
	for el in file:
		if el[0] == 1:
			d[el[1]>>6] = 1
	print filename[19:-20],len(d)