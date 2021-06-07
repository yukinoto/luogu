#include <iostream>
using namespace std;

/*template<typename T>
T quickpow(T x,long long a)
{
	if(a==1)
		return x;
	if((a&1)==1)
	{
		T as=quickpow(x,a>>1);
		return as*as*x;
	}
	T as=quickpow(x,a>>1);
	return as*as;
}*/
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

long long mod=1000000007;

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

int main()
{
	Int x;
	x.num=1;
	matrix<Int>f;
	long long n;
	cin>>n;
	f.a[0][0]=x,f.a[0][1]=x,f.a[1][0]=x;x.num=0,f.a[1][1]=x;
	f=quickpow(f,n-1);
	cout<<f.a[0][0].num<<endl;
	return 0;
}
