#include <stdio.h>
#include <algorithm>
using namespace std;

int a[110],f[220];
int mod;
/*bool ifStone(int l,int r,int x)
{
	if(l>=r)
		return false;
	if(l==r-1)
	{
		if(a[l]==x)
			return true;
		else
			return false;
	}
	int mid=(l+r)/2;
	if(a[mid]>x)
		return ifStone(l,mid,x);
	else
		return ifStone(mid,r,x);
}*/
int main()
{
	int l,s,t,m,pre=0;
	scanf("%d%d%d%d",&l,&s,&t,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",a+i);
	if(s==t)
	{
		int ans=0;
		for(int i=1;i<=m;i++)
			if(a[i]%s==0)
				ans++;
		printf("%d\n",ans);
		return 0;
	}
	sort(a+1,a+m+1);
	f[0]=1;
	a[m+1]=l;
	mod=t*2+13;
	for(int i=1;i<=l+t;i++)
	{
		int rp=0;
		if(i==a[pre+1])
		{
			pre++;
			if(a[pre+1]-a[pre]>=1000)
			{
				int mi=0;
				for(int j=(i+mod-t)%mod;j!=(i+mod-s+1)%mod;j=(j+1)%mod)
				{
					if(f[j]!=0&&mi==0)
						mi=f[j];
					if(f[j]!=0)
						mi=min(mi,f[j]);
				}
				for(int j=0;j<mod;j++)
					f[j]=mi;
				i=a[pre+1]-1;
				continue;
			}
			rp++;
			if(i==l)
				rp--;
		}
		f[i%mod]=0;
		for(int j=(i+mod-t)%mod;j!=(i+mod-s+1)%mod;j=(j+1)%mod)
		{
			if(f[j]!=0)
				if(f[i%mod]==0)
					f[i%mod]=f[j]+rp;
				else
					f[i%mod]=min(f[i%mod],f[j]+rp);
		}
	}
	int ans=0x7fffffff;
	for(int i=l;i<l+t;i++)
		if(f[i%mod]!=0)
			ans=min(ans,f[i%mod]);
	printf("%d\n",ans-1);
	return 0;
}
