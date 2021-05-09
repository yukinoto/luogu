#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

typedef long long Int;
vector<Int> prim;

bool tb[1000010];
void do_prim(int n)
{
	tb[0]=tb[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!tb[i])
			prim.push_back(i);
		for(int j=0;j<prim.size()&&prim[j]*i<=n;j++)
		{
			tb[prim[j]*i]=1;
			if(i%prim[j]==0)
				break;
		}
	}
	return;
}

bool pc(Int x,vector<Int>&a)
{
	int flag=2;
	a.clear();
	for(int i=0;i<prim.size();i++)
	{
		a.push_back(0);
		while(x%prim[i]==0)
		{
			x/=prim[i];
			a[i]++;
		}
		if(i==0&&a[0]>2) flag=0;
		if(flag&&i!=0&&a[i]>0) flag--;
		if(x==1)
			break;
	}
	return flag!=0;
}

Int gcd(Int a,Int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

template<typename T>
T quickpow(T x,long long a)
{
	if(a==1)
		return x;
	if((a&1)==1)
	{
		T as=quickpow(x,a>>1);
		return as*as*x;
	}
	T as=quickpow(x,a>>1);
	return as*as;
}

Int phi(const vector<Int> &p)
{
	Int ans=1;
	for(int i=0;i<p.size();i++)
		ans*=quickpow(prim[i],p[i]-1)*(prim[i]-1);
	return ans;
}

void dlt()
{
	Int p,d;
	cin>>p>>d;
	vector<Int> q,dt;
	if(pc(p,q))
	{
		Int ph=phi(q);
		for(int i=2;i<p;i++)
			if(gcd(i,p)==1)
			{
				bool flag=true;
				Int g=i;
				for(int j=2;j<ph;j++)
				{
					g=g*i%p;
					if(g==1)
					{
						flag=false;
						break;
					}
				}
				if(flag)
				{
					dt.push_back(g);
					break;
				}
			}
		if(p==2)
			dt.push_back(1);
		Int x=dt[0];
		for(int i=1;i<ph;i++)
		{
			x=x*dt[0]%p;
			if(gcd(i,ph)==1)
				dt.push_back(x);
		}
		sort(dt.begin(),dt.end());
		cout<<dt.size()<<endl;
		for(int i=0;i<dt.size();i+=p/d)
			cout<<dt[i]<<' ';
		cout<<endl;
		return;
	}
	else
	{
		cout<<"0\n"<<endl;
		return;
	}
}

int main()
{
	do_prim(1000010);
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		dlt();
	return 0;
}
