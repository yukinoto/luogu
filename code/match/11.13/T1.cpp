#include <iostream>
#include <list>
using namespace std;

void grey(int n,int *a)
{
	if(n==1)
	{
		a[0]=0,a[1]=1;
		return;
	}
	grey(n-1,a);
	for(int i=0;i<(1<<(n-1));i++)
		a[(1<<(n))-i-1]=a[i]|(1<<(n-1));
	return;
}

int gcd(int a,int b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

int main()
{
	int n,k;
	cin>>n>>k;
	int a[1<<n];
	grey(n,a);
	if(n==1&&k==1)
	{
		cout<<"1\n0 1"<<endl;
		return 0;
	}
	if(k==0||k>=n||k%2==0)
	{
		cout<<0<<endl;
		return 0;
	}
	cout<<1<<endl;
	if(k==1)
		for(int i=0;i<(1<<n);i++)
			cout<<a[i]<<' ';
	else
		if(k==n-1)
		{
			for(int i=0;i<(1<<n);i++)
				cout<<(a[i]^((i&1)?((1<<n)-1):0))<<' ';
		}
		else
		{
			int b[1<<(n-k-1)];
			grey(n-k-1,b);
			grey(k+1,a);
			for(int i=0;i<(1<<(k+1));i++)
			{
				a[i]=(a[i]^((i&1)?((1<<(k+1))-1):0));
			}
			int bef=0;
			for(int i=0;i<(1<<(n-k-1));i++)
			{
				auto it=0;
				while(a[it]!=bef) it++;
				cout<<((b[i]<<(k+1))|(a[it]))<<' ';
				auto p=it++;
				for(;it%(1<<(k+1))!=p;it++)
				{
					cout<<((b[i]<<(k+1))|(a[it%(1<<(k+1))]))<<' ';
					bef=a[it%(1<<(k+1))];
				}
				bef^=(1<<(k-1))-1;
			}
		}
	cout<<endl;
	return 0;
}
