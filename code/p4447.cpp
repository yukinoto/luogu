#include <stdio.h>
#include <algorithm>
using namespace std;

int n;
int a[100010];

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	sort(a,a+n);
	a[n]=0x7fffffff;
	return;
}

int len[100010];

int findmin(int p)
{
	int ansp=p;
	for(int i=p;i>=0&&a[i]==a[p];i--)
	{
		if(len[i]<len[ansp])
			ansp=i;
	}
	return ansp;
}

bool check(int ans)
{
	for(int i=0;i<n;i++)
		len[i]=0;
	int befp=0;
	for(int i=0;i<n&&a[i]==a[0];i++)
	{
		befp=i;
		len[i]=1;
	}
	for(int i=befp+1;i<=n;i++)
	{
		if(a[i]!=a[i-1])
			befp=i-1;
		if(a[i]!=a[befp]+1)
		{
			for(int j=befp;j>=0&&a[j]==a[befp];j--)
			{
				if(len[j]<ans)
					return false;
				len[j]=0x7fffffff;
			}
		}
		int p=findmin(befp);
		if(len[p]==0x7fffffff)
			len[i]=1;
		else
		{
			len[i]=len[p]+1;
			len[p]=0x7fffffff;
		}
	}
	return true;
}

int work(int l,int r)
{
	if(l>=r)
		return -1;
	if(l==r-1)
		return l;
	int mid=(l+r)/2;
	if(check(mid))
		return work(mid,r);
	else
		return work(l,mid);
}

int main()
{
	init();
	printf("%d\n",work(0,n+1));
	return 0;
}
