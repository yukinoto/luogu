#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iomanip>
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
		c.fl[3]=c.fl[1]+c.fl[2]-c.fl[0];
	if((c.fl[0]-c.fl[1])*(c.fl[2]-c.fl[1])==0)
		c.fl[3]=c.fl[0]+c.fl[2]-c.fl[1];
	if((c.fl[1]-c.fl[2])*(c.fl[0]-c.fl[2])==0)
		c.fl[3]=c.fl[1]+c.fl[0]-c.fl[2];
	return ins;
}

int s,t,a,b;
city c[110];

vector<pair<int,double>> nmp[410];
double d[410];
bool tnk[410];

void init(istream&ins)
{
	ins>>s>>t>>a>>b;
	for(int i=1;i<=s;i++)
		ins>>c[i];
	for(int i=1;i<=s;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=j+1;k<4;k++)
			{
				nmp[(i-1)*4+j].push_back(make_pair((i-1)*4+k,dist(c[i].fl[j],c[i].fl[k])*c[i].T));
				nmp[(i-1)*4+k].push_back(make_pair((i-1)*4+j,dist(c[i].fl[j],c[i].fl[k])*c[i].T));
			}
			for(int k=i+1;k<=s;k++)
				for(int l=0;l<4;l++)
				{
					nmp[(i-1)*4+j].push_back(make_pair((k-1)*4+l,dist(c[i].fl[j],c[k].fl[l])*t));
					nmp[(k-1)*4+l].push_back(make_pair((i-1)*4+j,dist(c[i].fl[j],c[k].fl[l])*t));
				}
		}
	}
	return;
}

int fmp()
{
	int p=-1;
	for(int i=0;i<s*4;i++)
		if(!tnk[i]&&(p==-1||d[p]>d[i]))
			p=i;
	return p;
}

void relax(int p)
{
	if(p==-1)
		return;
	for(auto i:nmp[p])
	{
		if(!tnk[i.first]&&d[i.first]>d[p]+i.second)
			d[i.first]=d[p]+i.second;
	}
	return;
}

void dij(int fnt)
{
	for(int i=0;i<=s*4;i++)
	{
		d[i]=1e9;
		tnk[i]=false;
	}
	tnk[fnt]=true;
	d[fnt]=0;
	relax(fnt);
	for(int i=1;i<s*4;i++)
	{
		int p=fmp();
		if(p==-1)
			throw -1;
		tnk[p]=true;
		relax(p);
	}
	return;
}

void work()
{
	init(cin);
	double ans=1e9;
	for(int i=0;i<4;i++)
	{
		dij((a-1)*4+i);
		for(int j=0;j<4;j++)
			ans=min(ans,d[(b-1)*4+j]);
	}
	cout<<fixed<<setprecision(1)<<ans<<endl;
	return;
}

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}