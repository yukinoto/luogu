#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class matrix{
	public:
		int n,m;
		vector<double> *a;
		vector<double>& operator [](int x)
		{
			return a[x];
		}
		matrix(int _n,int _m)
		{
			n=_n,m=_m;
			a=new vector<double>[n];
			for(int i=0;i<n;i++)
				a[i].resize(m);
		}
		matrix(int _n)
		{
			n=m=_n;
			a=new vector<double>[n];
			for(int i=0;i<n;i++)
				a[i].resize(m);
		}
		void r(int f,int t)
		{
			for(int i=0;i<m;i++)
				a[t][i]+=a[f][i];
			return;
		}
		void r(int f,int t,double k)
		{
			for(int i=0;i<m;i++)
				a[t][i]+=a[f][i]*k;
			return;
		}
		void rs(int f,int t)
		{
			swap(a[f],a[t]);
		}
		void c(int f,int t)
		{
			for(int i=0;i<n;i++)
				a[i][t]+=a[i][f];
			return;
		}
		void c(int f,int t,double k)
		{
			for(int i=0;i<n;i++)
				a[i][t]+=a[i][f]*k;
			return;
		}
};

int main()
{
	int n;
	bool flag=true;
	cin>>n;
	matrix A(n,n+1);
	for(int i=0;i<n;i++)
		for(int j=0;j<=n;j++)
			cin>>A[i][j];
	for(int i=0;i<n;i++)
	{
		for(int j=i;A[i][i]-0<=0.001;j++)
			A.rs(i,j);
		if(A[i][i]-0<0.001)
		{
			flag=false;
			break;
		}
		for(int j=0;j<n;j++)
			if(i!=j)
				A.r(j,i,-A[j][i]/A[i][i]);
	}
	if(flag)
	{
		for(int i=0;i<n;i++)
			printf("%.2f\n",A[i][n]/A[i][i]);
	}
	else
	{
		printf("No Solution\n");
	}
	return 0;
}
