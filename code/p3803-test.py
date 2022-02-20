#!/bin/python3

mod=998244353

def w(i,n):
	return pow(3,i*(mod-1)//n,mod)

def b(x):
	ans=1
	while ans<x:
		ans*=2
	return ans

a=[int(i) for i in input().split()]

def f(x):
	ans,nw=0,1
	for i in range(len(a)):
		ans+=nw*a[i]
		nw=nw*x%mod
		ans%=mod
	return ans

p=2**b(len(a))
for i in range(p):
	print(f(w(i,p)),end=' ')
print()