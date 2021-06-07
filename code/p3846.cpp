#include <iostream>
#include <map>
#include <cmath>
using namespace std;

long long a,b,p;

/*template <typename T>
pair<T,T> ExE(T a,T b,const T &d)
{
	if(b==0)
		return make_pair(a/d,b);
	pair<T,T> sol=ExE(b,a%b,d);
	return make_pair(sol.y,sol.x-a/b*sol.y);
}
template <typename T>
T eu(T a,T b)
{
	if(b==0)
		return a;
	return eu(b,a%b);
}
template <typename T>
pair<T,T> solu(T a,T b,const T &d)
{
	if(d%eu(a,b)!=0)
		return make_pair(0ll,0ll);
	return ExE(a,b,d);
}
template <typename T>
T anti(T x,T p)
{
	T ans=solu(x,p,1ll).x;
	return (ans%p+p)%p;
}*/

/*long long BSGS(long long a,long long b,long long p)
{
	map<long long,long long> tb;
	long long sq=long long(sqrt(p)+0.5);
	long long at=anti(a,p),na=at;
	tb.insert(make_pair(at,1));
	for(int i=2;i<=sq;i++)
	{
		na=na*at%p;
		tb.insert(make_pair(na,i));
	}
	long long ans=1;
	for(int i=0;i<=sq;i++)
	{
		ans=ans*
	}
}*/
template<typename Int>
Int pow(Int a,Int n,Int p)
{
	Int ans=1;
	for(int i=63;i>=0;i--)
	{
		ans=ans*ans%p;
		if(n&(1ull<<i))
			ans=ans*a%p;
	}
	return ans;
}

long long BSGS(long long a,long long b,long long p)
{
	map<long long,long long>tb;
	long long nb=b,sq=(long long)(ceil(sqrt(p)));
	for(int i=0;i<=sq;i++)
	{
		tb.erase(nb);
		tb.insert(make_pair(nb,(long long)i));
		nb=nb*a%p;
	}
	long long na=1,sa=pow(a,sq,p);
	for(int i=0;i<sq;i++)
	{
		if(tb.find(na)!=tb.end())
			return (sq*i-tb[na]+p-1)%(p-1);
		na=sa*na%p;
	}
	return -1;
}

int main()
{
	cin>>p>>a>>b;
	long long ans=BSGS(a,b,p);
	if(ans==-1)
		cout<<"no solution"<<endl;
	else
		cout<<ans<<endl;
	return 0;
}
