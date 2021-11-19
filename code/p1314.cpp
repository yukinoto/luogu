#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

int n,m;
long long s;
pair<int,int> a[200001],b[200001];

void init()
{
	cin>>n>>m>>s;
	for(int i=1;i<=n;i++)
		cin>>a[i].first>>a[i].second;
	for(int i=1;i<=m;i++)
		cin>>b[i].first>>b[i].second;
}

int pre1[200001];
long long pre2[200001];

long long chk(int w)
{
	pre1[0]=pre2[0]=0;
	for(int i=1;i<=n;i++)
		if(a[i].first>=w)
		{
			pre1[i]=pre1[i-1]+1;
			pre2[i]=pre2[i-1]+a[i].second;
		}
		else
		{
			pre1[i]=pre1[i-1];
			pre2[i]=pre2[i-1];
		}
	long long ans=0;
	for(int i=1;i<=m;i++)
		ans+=(pre2[b[i].second]-pre2[b[i].first-1])*(pre1[b[i].second]-pre1[b[i].first-1]);
	return ans;
}

int fnd(long long s)
{
	int l=1,r=1000001;
	while(l<r-1)
	{
		int mid=(l+r)/2;
		if(chk(mid)<s)
			r=mid;
		else
			l=mid;
	}
	return l;
}

int main()
{
	init();
	int p=fnd(s);
	cout<<min(chk(p)-s,s-chk(p+1))<<endl;
	return 0;
}