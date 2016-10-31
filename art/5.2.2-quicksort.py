#!/bin/bash

# chap 5.2.2.Q: the quicksort
import time
import random

def TMP_isort(l, a, b):
	if a>=b:
		return
	for i in range(a+1, b):
		one = l[i]
		j = i-1
		while(j>=a and l[j]>one):
			l[j+1] = l[j]
			j -= 1
		l[j+1] = one

def TMP_qsort(l, a, b, M):
	# sort [a,b) of l
	if(b-a < M):
		TMP_isort(l, a, b)
	else:
		# 1. step 1 partition
		pivot = random.randint(a, b-1)
		v = l[pivot]
		l[pivot], l[a] = l[a], l[pivot]
		i = a+1
		j = b-1
		#print(a, l[a], l)
		while(1):
			while(i < b and l[i] < v):
				i += 1
			while(l[j] > v):
				j -= 1
			if i>=j:
				break
			if i < b:
				#print(i,j)
				l[i], l[j] = l[j], l[i]
		l[j], l[a] = l[a], l[j]
		#print(j, l[j], l)
		# 2. recursive
		TMP_qsort(l, a, j, M)
		TMP_qsort(l, j+1, b, M)

def quicksort(l, M):
	# sort in-place the list with quicksort
	n = len(l)
	TMP_qsort(l, 0, len(l), M)

def test(l, M, n):
	lgold = sorted(l)
	time1 = time.time()
	for i in range(n):
		ll = l.copy()
		quicksort(ll, M)
		#print(lgold, ll)
		assert lgold==ll
	time2 = time.time()
	print("qs2:", time2-time1)
	
def main():
	l = [i for i in range(1000)]
	random.shuffle(l)
	#print(l)
	t = 100
	time1 = time.time()
	for i in range(t):
		sorted(l.copy())
	print("qs:", time.time()-time1)
	test(l.copy(), 10, t)

main()
