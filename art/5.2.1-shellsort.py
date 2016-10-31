#!/bin/bash

# chap 5.2.2.D: the shell-sort
import time
import random

def shellsort(lorigin, hs):
	# sort in-place the list according to the hs, hs must be descendant to 1
	l = lorigin.copy()
	n = len(l)
	for h in hs:
		for st in range(h):
			i = st+h	#start with the first one h
			while i<n:	# insert i
				j = i-h
				key = l[i]
				while l[j]>key:	# move one
					l[j+h] = l[j]
					j -= h
					if j<0:
						break
				l[j+h] = key
				i += h
	return l

def geth1(n):
	hs = []
	cur_2 = 2
	while cur_2-1 < n:
		hs.append(cur_2-1)
		cur_2 *= 2
	hs.reverse()
	return hs

def geth2(n):
	hs = []
	cur = 1
	while cur < n:
		hs.append(cur)
		cur = cur*3+1
	hs.reverse()
	return hs[1:]
				
def test(l, hs, n):
	lgold = sorted(l)
	time1 = time.time()
	for i in range(n):
		ltest = shellsort(l, hs)
		assert lgold==ltest
	time2 = time.time()
	print(hs, ":", time2-time1)
	
def main():
	l = [i for i in range(1000)]
	random.shuffle(l)
	t = 100
	time1 = time.time()
	for i in range(t):
		sorted(l)
	print("qs:", time.time()-time1)
	test(l, [1], t)
	test(l, [5,1], t)
	test(l, [10, 5,1], t)
	test(l, geth1(len(l)), t)
	test(l, geth2(len(l)), t)

main()
