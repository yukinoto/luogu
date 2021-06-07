#include <iostream>
using namespace std;

template<typename T>
T quickpow(T a,long long n)
{
	T ans(1);
	for(int i=63;i>=0;i--)
	{
		ans=ans*ans;
		if(n&(1ull<<i))
			ans=ans*a;
	}
	return ans;
}
template<typename T>
class matrix{
	public:
		T a[2][2];
		matrix(){;}
		matrix(int x)
		{
			if(x==1)
				a[0][0]=a[1][1]=1,a[1][0]=a[0][1]=0;
		}
		matrix<T> operator *(const matrix<T> &x)const
		{
			matrix<T> ans;
			for(int i=0;i<2;i++)
				for(int j=0;j<2;j++)
				{
					ans.a[i][j]=0;
					for(int k=0;k<2;k++)
						ans.a[i][j]+=a[i][k]*x.a[k][j];
				}
			return ans;
		}
};

long long mod=100000000;

class Int{
	public:
		long long num;
		Int operator *(const Int &x)const
		{
			Int ans;
			ans.num=num*x.num%mod;
			return ans;
		}
		Int operator =(const long long &x)
		{
			num=x%mod;
			return *this;
		}
		void operator +=(const Int &x)
		{
			num=(num+x.num)%mod;
			return;
		}
};

long long fi(long long n)
{
	Int x;
	x.num=1;
	matrix<Int>f;
	f.a[0][0]=x,f.a[0][1]=x,f.a[1][0]=x;x.num=0,f.a[1][1]=x;
	f=quickpow(f,n-1);
	return f.a[0][0].num;
}

template <typename T>
T gcd(T a,T b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

int main()
{
	long long n,m;
	cin>>n>>m;
	cout<<fi(gcd(n,m))<<endl;
	return 0;
}
