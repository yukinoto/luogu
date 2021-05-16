#include <iostream>
#include <vector>
#include <algorithm>
#include<cmath>
using namespace std;

int n,sq;
vector<int> a[1010];

int fnd(int l,int r,int key)
{
	if(l==r-1)
		return l;
	int mid=(l+r)/2;
	if(a[mid].empty()||a[mid][0]>key)
		return fnd(l,mid,key);
	else
		return fnd(mid,r,key);
}

void bal(int p)
{
	while(a[p].size()>=sq)
	{
		a[p+1].insert(a[p+1].begin(),a[p][a[p].size()-1]);
		a[p].pop_back();
		p++;
	}
	return;
}

int main()
{
	cin>>n;
	sq=int(sqrt(n))+1;
	for(int i=0;i<sq;i++)
		a[i].clear();
	for(int t=0;t<n;t++)
	{
		int f;
		cin>>f;
		if(f==1)
		{
			int x;
			cin>>x;
			int p=fnd(0,sq,x);
			if(a[p].empty())
				a[p].push_back(x);
			else
				a[p].insert(lower_bound(a[p].begin(),a[p].end(),x),x);
			bal(p);
		}
		if(f==2)
		{
			int x;
			cin>>x;
			int p=fnd(0,sq,x);
			if(a[p].empty())
				return -1;
			else
				a[p].erase(lower_bound(a[p].begin(),a[p].end(),x));
		}
		if(f==3)
		{
			int x;
			cin>>x;
			int cnt=1;
			for(int i=0;i<sq;i++)
			{
				if(*(--a[i].end())>=x)
				{
					for(int j=0;j<a[i].size();j++)
						if(a[i][j]<x)
							cnt++;
						else
							break;
					cout<<cnt<<endl;
					break;
				}
				else
					cnt+=a[i].size();
			}
		}
		if(f==4)
		{
			int cnt=0,x;
			cin>>x;
			x--;
			for(int i=0;i<sq;i++)
			{
				if(cnt+a[i].size()>x)
				{
					cout<<a[i][x-cnt]<<endl;
					break;
				}
				else
					cnt+=a[i].size();
			}
		}
		if(f==5)
		{
			int x;
			cin>>x;
			int p=fnd(0,sq,x);
			if(a[p][0]>=x)
				cout<<a[p-1][a[p-1].size()-1]<<endl;
			else
			{
				auto it=lower_bound(a[p].begin(),a[p].end(),x);
				it--;
				cout<<*it<<endl;
			}
		}
		if(f==6)
		{
			int x;
			cin>>x;
			int p=fnd(0,sq,x);
			if(p<sq&&a[p][a[p].size()-1]<=x)
			{
				cout<<*upper_bound(a[p+1].begin(),a[p+1].end(),x)<<endl;
			}
			else
				cout<<*upper_bound(a[p].begin(),a[p].end(),x)<<endl;
		}
	}
	return 0;
}
