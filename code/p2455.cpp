//wa #4
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

bool equal(double a,double b)
{
	return abs(a-b)<=0.0001;
}

vector<double> operator *(const vector<double> &x,double k)
{
	vector<double> ans;
	for(auto i:x)
		ans.push_back(i*k);
	return ans;
}

vector<double> operator *(double k,const vector<double> &x)
{
	vector<double> ans;
	for(auto i:x)
		ans.push_back(i*k);
	return ans;
}

const vector<double>& operator +=(vector<double> &x,const vector<double> &y)
{
	if(x.size()!=y.size())
		throw "fuckccf";
	for(int i=0;i<x.size();i++)
		x[i]+=y[i];
	return x;
}

int main()
{
	vector<double> *a[50];
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		a[i]=new vector<double>;
		for(int j=0;j<=n;j++)
		{
			int x;
			cin>>x;
			a[i]->push_back(double(x));
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int k=i;k<n;k++)
			if(abs((*a[k])[i])>abs((*a[i])[i]))
				swap(a[k],a[i]);
		double xi=(*a[i])[i];
		if(equal(xi,0))
			continue;
		for(int j=0;j<n;j++)
			if(j!=i)
				(*a[j])+=(*a[i])*(-(*a[j])[i]/xi);
	}
	int flag=1;
	vector<double>ans;
	for(int i=0;i<n;i++)
		if(equal((*a[i])[i],0.0))
			if(equal((*a[i])[n],0.0))
				flag=0;
			else
			{
				flag=-1;
				cout<<-1<<endl;
				break;
			}
		else
			ans.push_back((*a[i])[n]/(*a[i])[i]+0.00001);
	if(flag==0)
		cout<<0<<endl;
	if(flag==1)
	{
		cout<<fixed<<setprecision(2);
		for(int i=0;i<n;i++)
			cout<<'x'<<i+1<<'='<<ans[i]<<endl;
	}
	for(int i=0;i<n;i++)
		delete a[i];
	return 0;
}