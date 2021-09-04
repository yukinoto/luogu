#include <iostream>
using namespace std;

class comp{
	public:
		long long i2,mod;
		long long x,y;
		comp(long long _i2,long long _mod,long long _x,long long _y)
		{
			i2=_i2,mod=_mod;
			x=_x%mod,y=_y%mod;
			return;
		}
		comp operator *(const comp &a)
		{
			comp ans(i2,mod,(x*a.x%mod+y*a.y%mod*i2%mod)%mod,(x*a.y+y*a.x)%mod);
			return ans;
		}
};

template<typename T,typename opt>
T quickpow(T x,long long n,opt mod)
{
	if(n==1)
		return x;
	T x2=mod(quickpow(x,n>>1,mod));
	x2=mod(x2*x2);
	if(n&1==1)
		return mod(x2*x);
	return x2;
}

template<typename T>
T lr(T x,T p)
{
	T r=quickpow(x,(p-1)/2,[p](T x){return x%p;});
	return r;
}

void work()
{
	long long n,p;
	cin>>n>>p;
	n%=p;
	if(n==0)
	{
		cout<<0<<endl;
		return;
	}
	auto mod=[p](long long x){return ((x%p)+p)%p;};
	if(lr(n,p)==p-1)
	{
		cout<<"Hola!"<<endl;
		return;
	}
	long long a=1;
	for(;a<p;a++)
		if(lr(mod(a*a-n),p)==p-1)
			break;
	comp x(a*a-n,p,a,1);
	x=quickpow(x,(p+1)/2,[p](comp x){x.x%=p,x.y%=p;return x;});
	long long x1=mod(x.x),x2=mod(p-x1);
	if(x2<x1)
		swap(x1,x2);
	printf("%lld %lld\n",x1,x2);
	return;
}

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}