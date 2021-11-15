#include<iostream>
using namespace std;

long long mod=998244353;

long long gcd(long long a,long long b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

template <typename T>
T quickpow(const T &x,long long n)
{
	int cnt=0;
	long long an=0;
	while(n)
	{
		an<<=1;
		an|=(n&1);
		n>>=1;
		cnt++;
	}
	T as=1;
	for(int i=0;i<cnt;i++)
	{
		as=as*as%mod;
		if(an&1)
			as=as*x%mod;
		an>>=1;
	}
	return as;
}

int main()
{
	long long n,k;
	cin>>n>>k;
	/*long long r=k;
	k=0;
	while(r%2==0)
	{
		r/=2;
		k+=1;
	}*/
	//cout<<quickpow<long long>(2,n-k)<<endl;
	cout<<quickpow<long long>(2,n-gcd(n,k)+int(n%k==0))<<endl;
	return 0;
}