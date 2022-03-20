#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long n,m,k;
vector<long long> st[1000010];

long long a[300010],b[300010],pre[300010];
bool zro[300010];

int main()
{
	//freopen("sakura3.in","r",stdin);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
		cin>>b[i];
	zro[0]=true;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if((i==1||zro[i-1])&&a[i]==0)
			zro[i]=true;
		else
			zro[i]=false;
		a[i]%=k;
	}
	for(int i=1;i<=n;i++)
		pre[i]=(pre[i-1]+a[i])%k;
	for(int i=1;i<=m;i++)
		if(!zro[b[i]])
			st[pre[b[i]]].push_back(i);
	int ans=st[0].size();
	for(int i=1;i<=n;i++)
	{
		auto it1=lower_bound(st[0].begin(),st[0].end(),i),it2=upper_bound(st[(a[i])%k].begin(),st[(a[i])%k].end(),i);
		long long x=it1-st[0].begin(),y=st[(a[i])%k].end()-it2;
		ans=max<long long>(ans,x+y);
	}
	cout<<ans<<endl;
	return 0;
}