a=[-1,1]
x=3
maxn=1000
mod=998244353
for i in range(2,maxn):
	x*=3
	x%=mod
	a.append((2*a[i-1]+3*a[i-2]+x)%mod)
print(a)