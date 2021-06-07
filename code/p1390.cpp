#include <iostream>
#include <vector>
using namespace std;

typedef long long Int;

vector<Int>prim;
bool ptb[2000010];
Int u[2000010],preu[2000010];

void pre(Int n)
{
	ptb[0]=ptb[1]=true;
	u[1]=-1;
	for(Int i=2;i<n;i++)
	{
		if(!ptb[i])
		{
			prim.push_back(i);
			u[i]=-1;
		}
		for(int j=0;j<prim.size()&&i*prim[j]<n;j++)
		{
			ptb[i*prim[j]]=true;
			u[i*prim[j]]=u[i]*u[prim[j]];
			if(i%prim[j]==0)
			{
				u[i*prim[j]]=0;
				break;
			}
		}
	}
	for(Int i=1;i<n;i++)
		preu[i]=preu[i-1]+u[i];
	return;
}

Int n;

int main()
{
	cin>>n;
	Int ans=0;
	pre(n+1);
	for(int i=1;i<=n;i++)
	{
		Int cache=0,up=n/i;
		for(int l=1,r;l<=up;l=r+1)
		{
			r=up/(up/l);
			cache+=(preu[r]-preu[l-1])*(up/l)*(up/l);
		}
		ans+=i*cache;
	}
	cout<<(ans-n*(n+1)/2)/2<<endl;
}
