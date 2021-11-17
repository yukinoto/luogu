from cyaron import *
import sys

def gen(n,m,file="test.in"):
	io=IO(file)
	io.input_writeln(n,m)
	a=[]
	for i in range(0,n):
		a.append(randint(1,n))
	io.input_writeln(a)
	for i in range(0,m):
		f=randint(1,2)
		if f==1:
			l,r,c=randint(1,n),randint(1,n),randint(1,n)
			if l>r:
				l,r=r,l
			io.input_writeln(f,l,r,c)
		else:
			x=randint(1,n-1)
			io.input_writeln(f,x)
	return io

n,m=int(sys.argv[1]),int(sys.argv[2])
p,std="./"+sys.argv[3],"./"+sys.argv[4]

while True:
	Compare.program(p,input=gen(n,m),std_program=std)
