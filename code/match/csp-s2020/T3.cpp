#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int MAXN=100010;
const long long MOD=998244353;
class modint{
	public:
		long long x;
		modint(long long _x)
		{
			x=_x;
		}
		modint(){;}
		modint operator *(const modint _x)const
		{
			return modint(x*_x.x%MOD);
		}
		modint operator +(const modint _x)const
		{
			return modint((x+_x.x)%MOD);
		}
		modint& operator *=(const modint _x)
		{
			x*=_x.x;
			x%=MOD;
			return *this;
		}
		modint& operator +=(const modint _x)
		{
			x=(x+_x.x)%MOD;
			return *this;
		}
		friend istream& operator >>(istream&,modint&);
		friend ostream& operator <<(ostream&,modint);
};
istream& operator >>(istream& ins,modint& x)
{
	return ins>>x.x;
}
ostream& operator <<(ostream& ous,modint x)
{
	return ous<<x.x;
}

int n,m,t;
int type[MAXN],que[MAXN],p[MAXN];
modint v[MAXN],a[MAXN],nv[MAXN];
vector<int>c[MAXN],at[MAXN];
int idg[MAXN],idg2[MAXN];

void init()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>type[i];
		if(type[i]==1)
		{
			cin>>p[i]>>v[i];
		}
		if(type[i]==2)
		{
			cin>>v[i];
		}
		if(type[i]==3)
		{
			int x;
			cin>>x;
			for(int j=0;j<x;j++)
			{
				int cache;
				cin>>cache;
				c[i].push_back(cache);
				at[cache].push_back(i);
				idg[i]++;
			}
		}
	}
	cin>>t;
	for(int i=1;i<=t;i++)
		cin>>que[i];
	return;
}

vector<int> q;
int front=0;
void tp1()
{
	for(int i=1;i<=m;i++)
	{
		if(idg[i]==0)
			q.push_back(i);
		if(type[i]==3)
			nv[i]=modint(1);
		if(type[i]==2)
			nv[i]=v[i];
		if(type[i]==1)
			nv[i]=modint(1);
	}
	while(q.size()>front)
	{
		int p=q[front++];
		for(auto i:at[p])
		{
			idg[i]--;
			nv[i]*=nv[p];
			if(idg[i]==0)
				q.push_back(i);
		}
	}
	return;
}
modint dms[MAXN],add[MAXN],tag,tag1;
void tp2()
{
	tag1=modint(1);
	for(int i=t;i>0;i--)
	{
		dms[que[i]]+=tag1;
		tag1*=nv[que[i]];
	}
	for(int i=q.size()-1;i>=0;i--)
	{
		int pt=q[i];
		if(type[pt]==1)
			add[p[pt]]+=dms[pt]*v[pt];
		if(type[pt]==3)
		{
			tag=dms[pt];
			for(auto it=c[pt].rbegin();it!=c[pt].rend();it++)
			{
				dms[*it]+=tag;
				tag*=nv[*it];
			}
		}
	}
}

void work()
{
	tp1();
	tp2();
	for(int i=1;i<=n;i++)
		cout<<a[i]*tag1+add[i]<<' ';
	cout<<endl;
}

int main()
{
	init();
	work();
	return 0;
}