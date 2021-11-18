#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int a[2010][2010];

void prep(int p,int cnt)
{
	static int pw[2010],aw[2010][2010];
	pw[0]=pw[1]=0;
	for(int i=2;i<=2000;i++)
		if(i%p==0)
			pw[i]=pw[i/p]+1;
		else
			pw[i]=0;
	for(int i=2;i<=2000;i++)
		pw[i]+=pw[i-1];
	for(int i=0;i<=2000;i++)
		for(int j=0;j<=i;j++)
			if(pw[i]-pw[j]-pw[i-j]>=cnt)
				aw[i][j]=1;
			else
				aw[i][j]=0;
	for(int i=0;i<=2000;i++)
		for(int j=0;j<=i;j++)
			a[i][j]=min(aw[i][j],a[i][j]);
	return;
}

int main()
{
	int t,k;
	cin>>t>>k;
	int x=k;
	memset(a,0x3f,sizeof(a));
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
		{
			int cnt=0;
			while(x%i==0)
			{
				cnt++;
				x/=i;
			}
			prep(i,cnt);
		}
	prep(x,1);
	for(int i=1;i<=2000;i++)
		for(int j=1;j<=i;j++)
			a[i][j]+=a[i][j-1];
	int n,m;
	for(int i=0;i<t;i++)
	{
		cin>>n>>m;
		int ans=0;
		for(int i=0;i<=n;i++)
			ans+=a[i][min(i,m)];
		cout<<ans<<endl;
	}
	return 0;
}