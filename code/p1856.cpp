#include <iostream>
#include <algorithm>
#include <un>
using namespace std;

typedef int inte;

class node{
	public:
		inte x,y;
		node(){}
		node(inte _x,inte _y)
		{
			x=_x,y=_y;
		}
		bool operator<(const node &a)const
		{
			return x==a.x?y<a.y:x<a.x;
		}
		bool operator==(const node &a)const
		{
			return x==a.x&&y==a.y;
		}
};
node getnode()
{
	node ans;
	cin>>ans.x>>ans.y;
	return ans;
}
class line{
	public:
		node n1,n2;
		line(){}
		line(const node &_n1,const node &_n2)
		{
			n1=_n1,n2=_n2;
			if(!(n1<n2)) swap(n1,n2);
			return;
		}
		bool operator ==(const line &x)const
		{
			return n1==x.n1&&n2==x.n2;
		}
};
line null(node(0,0),node(0,0));
class square{
	public:
		line l,r,u,d;
		void init()
		{
			node ld=getnode(),ru=getnode();
			d=line(ld,node(ru.x,ld.y));
			u=line(node(ld.x,ru.y),ru);
			l=line(ld,node(ld.x,ru.y));
			r=line(node(ru.x,ld.y),ru);
		}
};
int ptosq(const node &f,const square &x)
{
	if((f.x<x.d.n1.x&&f.y<x.d.n1.y)||
	(f.x<x.u.n1.x&&f.y>x.u.n1.y)||
	(f.x>x.d.n2.x&&f.y<x.d.n2.y)||
	(f.x>x.d.n2.x&&f.y>x.d.n2.y))
		return 0;
	if(f.x<x.d.n1.x)
		return 1;
	if(f.y<x.d.n1.y)
		return 2;
	if(f.x>x.d.n2.x)
		return 3;
	if(f.y>x.u.n1.y)
		return 4;
	if((f.x==x.d.n1.x||f.x==x.d.n2.x)&&(f.y==x.l.n1.y||f.y==x.l.n2.y))
		return 5;
	return -1;
}
pair<line,line> cut(const line &f,const square &x)
{
	if(ptosq(f.n1,x)==0||ptosq(f.n2,x)==0)
		return make_pair(f,null);
}