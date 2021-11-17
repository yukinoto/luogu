from cyaron import *
import sys

def gene(n,m,t,file="test.in"):
	io=IO(file)
	g=Graph(n,directed=True)
	pg=Graph.tree(n)
	root=randint(1,n)
	tkn=[False]*(n+1)
	tkn[root]=True
	q=[root]
	while len(q)>0:
		p=q[0]
		q=q[1:]
		for i in pg.edges[p]:
			a,b=i.start,i.end
			if b==p:
				a,b=b,a
			if not tkn[b]:
				g.add_edge(b,a)
				q.append(b)
				tkn[b]=True
	for i in range(n,m+1):
		g.add_edge(randint(1,n),randint(1,n))
	io.input_writeln(n,m,root,t)
	io.input_writeln(g.to_str(output=Edge.unweighted_edge))
	for i in range(0,t):
		io.input_write(randint(1,n))
	return io

n=int(sys.argv[1])
m=int(sys.argv[2])
q=int(sys.argv[3])

gene(n,m,q)