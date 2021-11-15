def f(n):
	return int(3**n/2+3/2*(-1)**(n+1))
for i in range(0,20):
	print(f(i),end=' ')