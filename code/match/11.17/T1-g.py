from cyaron import *
import sys

n=int(sys.argv[1])
p="./"+sys.argv[2]
std="./"+sys.argv[3]

while True:
	a,b=randint(1,n),randint(1,n)
	if a>b:
		a,b=b,a
	io=IO("test.in")
	io.input_writeln(a,b)
	Compare.program(p,input=io,std_program=std)