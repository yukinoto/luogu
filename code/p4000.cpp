#include <iostream>
#include <utility>
using namespace std;

template <typename Int>
pair<Int,Int> phi(Int n,Int mod)
{
	if(n==1)
		return make_pair<Int,Int>(0,1);
	if(n%2==1)
	{
		pair<Int,Int> ans=phi(n-1,mod);
		return make_pair(ans.second,(ans.first+ans.second)%mod);
	}
	else
	{
		pair<Int,Int> ans=phi(n/2,mod);
		return make_pair((ans.first*ans.first+ans.second*ans.second)%mod,(2*ans.first*ans.second+ans.second*ans.second)%mod);
	}
}

template<typename Int>
Int fi(Int n,Int mod)
{
	if(n==0)
		return 0;
	return phi(n,mod).second;
}

template<typename Int>
Int gcd(Int a,Int b)
{
	while(b!=0)
	{
		Int c=a%b;
		a=b,b=c;
	}
	return a;
}

template<typename Int>
Int lcm(Int a,Int b)
{
	return a/gcd(a,b)*b;
}

template<typename Int>
Int mod(string x,Int md)
{
	Int ans=0;
	for(int i=0;i<x.size();i++)
	{
		ans=ans*10+x[i]-'0';
		ans%=md;
	}
	return ans;
}

template<typename Int>
Int quickpow(Int a,long long n)
{
	Int ans=1;
	for(int i=63;i>=0;i--)
	{
		ans=ans*ans;
		if(n&(1ull<<i))
			ans=ans*a;
	}
	return ans;
}

template<typename Int>
Int pcy(Int p)
{
	if(p%5==1||p%5==4)
		return p-1;
	if(p%5==2||p%5==3)
		return p*2+2;
	return 20;
}

template<typename Int>
Int pacy(Int p,Int a)
{
	return pcy(p)*quickpow(p,a-1);
}

template<typename Int>
Int cy(Int p)
{
	Int ans=1;
	for(long long i=2;i*i<=p;i++)
	{
		Int cnt=0;
		while(p%i==0)
		{
			p/=i;
			cnt++;
		}
		if(cnt!=0)
			ans=lcm(ans,pacy(i,cnt));
	}
	if(p!=1)
		ans=lcm(ans,pcy(p));
	return ans;
}

int main()
{
	ios::sync_with_stdio(0);
	string x;
	long long n,p;
	cin>>x>>p;
	cout<<fi(mod<long long>(x,cy(p)),p)<<endl;
	return 0;
}
