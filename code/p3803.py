#!/usr/bin/python3
from decimal import *

getcontext().prec=10000000

n,m=(int(i) for i in input().split())

def get():
	ans='0.'
	cache=input().split()
	for i in cache:
		ans+='0'*(7-len(i))+i
	return Decimal(ans)

a,b=get(),get()

def pnt(x,n):
	x=x[9:]
	for i in range(0,n):
		print(int(x[:7]),end=' ')
		x=x[7:]
	print(end='\n')

pnt(str(a*b+1),n+m+1)