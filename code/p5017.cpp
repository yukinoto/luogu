#include <iostream>
#include <algorithm>
using namespace std;

int n,m;
int t[510],f[4000010];

void init()
{
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>t[i];
	sort(t,t+n);
	return;
}

int fnd(int l,int r,int x)
{
	if(l==r-1)
		return l;
	int mid=(l+r)/2;
	if(mid>x)
		return fnd(l,mid,x);
	return fnd(mid,r,x);
}

void dp()
{
	for(int i=0;i<4000001;i++)
	{
		
	}
}

int main()
{
}