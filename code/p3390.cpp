#include <iostream>
using namespace std;

class matrix{
	private:
		int n,m;
		long long a[1010][1010];
	public:
		matrix(){}
		matrix(int _n)
		{
			n=m=_n;
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					a[i][j]=int(i==j);
			return;
		}
		void init(int _n,int _m)
		{
			n=_n,m=_m;
			for(int i=0;i<n;i++)
				for(int j=0;j<m;j++)
					cin>>a[i][j];
			return;
		}
		void print()
		{
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<m;j++)
					cout<<a[i][j]<<' ';
				cout<<endl;
			}
		}
		matrix operator *(const matrix &x)const
		{
			matrix ans;
			ans.n=n,ans.m=x.m;
			for(int i=0;i<n;i++)
				for(int j=0;j<x.m;j++)
				{
					ans.a[i][j]=0;
					for(int k=0;k<m;k++)
						ans.a[i][j]+=a[i][k]+x.a[k][j];
					ans.a[i][j]%=1000000007;
				}
			return ans;
		}
};


int n;unsigned long long k;
matrix pow(const matrix &x,unsigned long long k)
{
	matrix ans(n);
	for(int i=63;i>=0;i--)
	{
		ans=ans*ans;
		if(k&(1ull<<i))
			ans=ans*x;
	}
	return ans;
}

int main()
{
	matrix x;
	cin>>n>>k;
	x.init(n,n);
	x=pow(x,k);
	x.print();
	return 0;
}