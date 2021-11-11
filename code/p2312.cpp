#include <iostream>
using namespace std;

long long *a;
int n,m;

long long getn(istream &ins,long long mod=303700003)
{
	char c=ins.get();
	long long ans=0;
	bool flag=false;
	while(isspace(c))
		c=ins.get();
	if(c=='-')
	{
		flag=true;
		c=ins.get();
	}
	while(isdigit(c))
	{
		ans=(ans*10+c-'0');
		if(ans>=mod)
			ans%=mod;
		c=ins.get();
	}
	if(flag)
		ans=mod-ans;
	return ans;
}

bool check(long long x,long long mod=303700003)
{
	long long p=1;
	long long ans=0;
	for(int i=0;i<=n;i++)
	{
		ans+=p*a[i];
		p=p*x;
		if(p>=mod)
			p%=mod;
	}
	return ans%mod==0;
}

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	a=new long long[n+1];
	for(int i=0;i<=n;i++)
		a[i]=getn(cin);
	int cnt=0,*as=new int[m];
	for(int i=1;i<=m;i++)
		if(check(i))
			as[cnt++]=i;
	cout<<cnt<<endl;
	for(int i=0;i<cnt;i++)
		cout<<as[i]<<endl;
	delete[] a;
	delete[] as;
	return 0;
}