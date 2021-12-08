import decimal

decimal.getcontext().prec=10

class node:
	def __init__(self,_x,_y):
		self.x,self.y=_x,_y
	def __lt__(self,oth):
		if self.x==oth.x:
			return self.y<oth.y
		return self.x<oth.x
	def __mul__(self,oth):
		return self.x*oth.x+self.y*oth.y
	def __sub__(self,oth):
		return node(self.x-oth.x,self.y-oth.y)

def cj(o,p):
	return o.x*p.y-o.y*p.x

n=int(input())

a=[]
for i in range(n):
	cache=input().split()
	a.append(node(decimal.Decimal(cache[0]),decimal.Decimal(cache[1])))
a.sort()

stk=[]
for i in a:
	while len(stk)>=2 and cj(stk[-1]-stk[-2],i-stk[-1])>0:
		stk=stk[:-1]
	stk.append(i)
ans=decimal.Decimal('0')
for i in range(1,len(stk)):
	ans+=((stk[i]-stk[i-1])*(stk[i]-stk[i-1])).sqrt()

stk=[]
for i in a:
	while len(stk)>=2 and cj(stk[-1]-stk[-2],i-stk[-1])<0:
		stk=stk[:-1]
	stk.append(i)
for i in range(1,len(stk)):
	ans+=((stk[i]-stk[i-1])*(stk[i]-stk[i-1])).sqrt()

print(ans)
ans+=decimal.Decimal('0.005')
ans=str(ans)
flag=False
while len(ans)>0:
	if ans[0]=='.':
		flag=True
		ans+="00"
		print(ans[:3])
		break
	print(ans[0],end='')
	ans=ans[1:]
if not flag:
	print(".00")