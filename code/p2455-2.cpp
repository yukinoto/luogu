#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
T gcd(const T &a,const T &b)
{
	if(b==0)
		return a;
	return gcd(b,a%b);
}

long long gcd(const vector<long long>&x)
{
	long long ans=0;
	for(auto i:x)
		ans=gcd(i,ans);
	return ans;
}

vector<long long>& operator +=(vector<long long>&x,const vector<long long>&y)
{
	if(x.size()!=y.size())
		throw "fuckccf";
	for(long long i=0;i<x.size();i++)
		x[i]+=y[i];
	return x;
}

vector<long long>& operator -=(vector<long long>&x,const vector<long long>&y)
{
	if(x.size()!=y.size())
		throw "fuckccf";
	for(long long i=0;i<x.size();i++)
		x[i]-=y[i];
	return x;
}

vector<long long> operator *(const vector<long long>&x,long long k)
{
	vector<long long>ans;
	for(auto i:x)
		ans.push_back(i*k);
	return ans;
}

vector<long long> operator *(long long k,const vector<long long>&x)
{
	vector<long long>ans;
	for(auto i:x)
		ans.push_back(i*k);
	return ans;
}

vector<long long>& operator *=(vector<long long>&x,long long k)
{
	for(auto &i:x)
		i*=k;
	return x;
}

vector<long long>& operator /=(vector<long long>&x,long long k)
{
	for(auto &i:x)
		i/=k;
	return x;
}

int main()
{
	vector<long long> *a[50];
	long long n;
	cin>>n;
	for(long long i=0;i<n;i++)
	{
		a[i]=new vector<long long>;
		for(long long j=0;j<=n;j++)
		{
			long long x;
			cin>>x;
			a[i]->push_back(x);
		}
		*a[i]/=gcd(*a[i]);
	}
	for(long long i=0;i<n;i++)
	{
		for(long long k=i+1;k<n&&(*a[i])[i]==0;k++)
			if((*a[k])[i]!=0)
				swap(a[i],a[k]);
		if((*a[i])[i]==0)
			continue;
		for(long long j=0;j<n;j++)
			if(i!=j)
			{
				long long g=gcd((*a[i])[i],(*a[j])[i]);
				(*a[j])*=(*a[i])[i]/g;
				(*a[j])+=(*a[i])*(-(*a[j])[i]/(*a[i])[i]);
				(*a[j])/=gcd(*a[j]);
			}
	}
	long long flag=1;
	vector<double> ans;
	for(long long i=0;i<n;i++)
	{
		if((*a[i])[i]==0)
			if((*a[i])[n]==0)
				flag=0;
			else
			{
				flag=-1;
				break;
			}
		else
			ans.push_back(double((*a[i])[n])/(*a[i])[i]);
	}
	if(flag==0)
		cout<<0<<endl;
	if(flag==-1)
		cout<<-1<<endl;
	if(flag==1)
	{
		cout<<fixed<<setprecision(2);
		for(long long i=0;i<n;i++)
			cout<<'x'<<i+1<<'='<<ans[i]<<endl;
	}
	for(long long i=0;i<n;i++)
		delete a[i];
	return 0;
}