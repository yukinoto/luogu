#include <iostream>
#include <cmath>
using namespace std;

class node{
	public:
		int x,y;
		node(){;}
		node(int _x,int _y):x(_x),y(_y){;}
		friend istream& operator>>(istream&,node&);
		friend double dist(const node&,const node&);
		node operator-(const node&c)
		{
			return node(x-c.x,y-c.y);
		}
		node operator+(const node&c)
		{
			return node(x+c.x,y+c.y);
		}
		long long operator*(const node&c)
		{
			return (long long)x*c.x+(long long)y*c.y;
		}
};

istream& operator>>(istream&ins,node&x)
{
	return ins>>x.x>>x.y;
}
double dist(const node &a,const node &b)
{
	return sqrt((long long)(a.x-b.x)*(a.x-b.x)+(long long)(a.y-b.y)*(a.y-b.y));
}

class city{
	public:
		node fl[4];
		int T;
		friend istream& operator>>(istream&,city&);
};

istream& operator>>(istream&ins,city&c)
{
	ins>>c.fl[0]>>c.fl[1]>>c.fl[2]>>c.T;
	if((c.fl[1]-c.fl[0])*(c.fl[2]-c.fl[0])==0)
		
}