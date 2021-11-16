import sys
from cyaron import *

#n=10
n=int(sys.argv[1])
if len(sys.argv)>2:
	mi,mx=int(sys.argv[2]),int(sys.argv[2])
else:
	mi,mx=10,100

while True:
	t=Graph.tree(n,weight_limit=(mi,mx))
	io=IO("test.in")
	io.input_writeln(n)
	io.input_writeln(t)
	m=randint(n//2,n*2)
	io.input_writeln(m)
	x=[]
	for i in range(0,m):
		x.append(randint(2,n))
	io.input_writeln(x)
	Compare.program("./p",input=io,std_program="./std")
