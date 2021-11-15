#include <iostream>
using namespace std;

long long mod=998244353;

class matrix{
	public:
		long long a[3][3];
		matrix operator *(const matrix &x)const
		{
			matrix ans;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
				{
					ans.a[i][j]=0;
					for(int k=0;k<3;k++)
						ans.a[i][j]+=a[i][k]*x.a[k][j]%mod;
					ans.a[i][j]%=mod;
				}
			return ans;
		}
		matrix()
		{
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
					a[i][j]=0;
			a[0][0]=a[1][1]=a[2][2]=1;
		}
};

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
	T as;
	for(int i=0;i<cnt;i++)
	{
		as=as*as;
		if(an&1)
			as=as*x;
		an>>=1;
	}
	return as;
}

matrix bs;

void st()
{
	bs.a[0][0]=2,bs.a[0][1]=3,bs.a[0][2]=1;
	bs.a[1][0]=1,bs.a[1][1]=0,bs.a[1][2]=0;
	bs.a[2][0]=0,bs.a[2][1]=0,bs.a[2][2]=3;
}

long long fn(long long n)
{
	if(n==0)
		return -1;
	matrix p=quickpow(bs,n-1);
	return ((p.a[0][0]-p.a[0][1]+9*p.a[0][2]%mod)%mod+mod)%mod;
}

int main()
{
	st();
	long long n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		long long x;
		cin>>x;
		cout<<fn(x)<<endl;
	}
	return 0;
}
