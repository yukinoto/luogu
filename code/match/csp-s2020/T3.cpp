#include <iostream>
#include <vector>
#include <queue>
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

int n,m;
int type[MAXN];
modint p[MAXN],v[MAXN],a[MAXN],tms[MAXN];
vector<int>c[MAXN],at[MAXN];
int idg[MAXN];

void init()
{
	cin>>n>>m;
	for(int i=0;i<=n;i++)
		cin>>a[i];
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
				idg[cache]++;
			}
		}
	}
	return;
}

void tp1()
{
}

int main()
{;}