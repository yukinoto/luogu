#include <iostream>
#include <utility>
using namespace std;

template<typename Int>
pair<Int,Int> exgcd(Int a,Int b)
{
	if(b==0)
		return make_pair<Int,Int>(1,0);
	pair<Int,Int> res=exgcd(b,a%b);
	return make_pair<Int,Int>(res.second+0,res.first-(a/b)*res.second);
}

template<typename Int>
Int at(Int x,Int mod)
{
	return (exgcd(x,mod).first%mod+mod)%mod;
}

int main()
{
	int n;
	cin>>n;
	long long a[n],c[n],s=1;
	for(int i=0;i<n;i++)
	{
		cin>>c[i]>>a[i];
		s*=c[i];
		a[i]%=c[i];
	}
	long long x=0;
	for(int i=0;i<n;i++)
	{
		x+=(s/c[i])*at(s/c[i],c[i])*a[i]%s;
		x%=s;
	}
	cout<<(x+s)%s<<endl;
	return 0;
}