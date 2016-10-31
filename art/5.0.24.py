#!/bin/python
# section 5, 24: sorting into order when there is no easy way to tell
import random
def get_data(x=100000):
	# generating the data [0, x).
	# return data, a tuple of (prev, next)
	d = [i for i in range(x)]
	random.shuffle(d)
	l = [(d[i], d[i+1]) for i in range(x-1)]
	return d, l
	
def sort_data(l):
	# sort the list of tuples and return the original list
	lg = []		# list of (i, x), always sorted by the second one
	# loop to the power of 2, log(x)
	step = 1
	while len(l)>0:
		l1 = l
		l2 = l.copy()
		l1.sort(key=(lambda i: i[0]))	# sort on first token
		l2.sort(key=(lambda i: i[1]))	# sort on second token
		l3 = []
		# inner loop, scan the two lists
		ind1 = ind2 = indg = 0
		while 1:
			# on the second list
			if ind1 >= len(l1) or l2[ind2][1] < l1[ind1][0]:	# [first check ind1] append new one
				if len(lg) == 0:	# create the first one
					lg.append((len(l)-2, l2[ind2][0]))
					lg.append((len(l)-1, l2[ind2][1]))
				else:
					#print(indg, ind2, lg, l2)
					#assert lg[indg][1] == l2[ind2][1]
					while lg[indg][1] != l2[ind2][1]:
						indg += 1
					lg.append((lg[indg][0]-step, l2[ind2][0]))
					indg += 1
				ind2 += 1
			elif l2[ind2][1] == l1[ind1][0]:	# find a larger-step one
				l3.append((l2[ind2][0], l1[ind1][1]))
				ind1 += 1
				ind2 += 1
			elif l2[ind2][1] > l1[ind1][0]: # skip the head of l1
				ind1 += 1
			# break when out of l2
			if ind2 >= len(l2):
				break
		# the post-process
		l = l3
		step *= 2
		lg.sort(key=(lambda i: i[1]))
	# final sort
	lg.sort(key=(lambda i: i[0]))
	return [i[1] for i in lg]

if __name__ == "__main__":
	for i in range(2):
		d, l = get_data()
		r = sort_data(l)
		print(d==r)
