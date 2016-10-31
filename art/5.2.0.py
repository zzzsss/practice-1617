#!/bin/python

# section 5.2, unshuffling procedure

def unshuffle(l, index):
	# reorder the elements in place using the index
	# 0. allocate one extra space
	tmp = None
	# 1. scan the index
	for i, v in enumerate(l):
		if i != index[i]:
			# start one moving
			start = cur = i		# indexes
			tmp = l[i]
			while index[cur] != start:
				next = index[cur]
				l[cur] = l[next]
				index[cur] = cur
				cur = next
			l[cur] = tmp
			index[cur] = cur
	return l
	
import random
def test(n, m):
	for i in range(n):
		print("Test time %d" % i)
		l = [z for z in range(m)]
		k = [z for z in range(m)]
		random.shuffle(l)
		k.sort(key=(lambda x: l[x]))
		print(l)
		print(k)
		unshuffle(l, k)
		print(l)
		
test(3, 20)

