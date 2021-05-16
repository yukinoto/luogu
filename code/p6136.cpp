#include <iostream>
#include <vector>
#include <algorithm>
#include<cmath>
using namespace std;

int n,m,sq,last=0,ans=0;
vector<int> a[11010];

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
	cin>>n>>m;
	sq=int(sqrt(n))+1;
	for(int i=0;i<sq;i++)
		a[i].clear();
	{
		int k=0;
		vector<int>c;
		for(int i=0;i<n;i++)
		{
			int x;
			cin>>x;
			c.push_back(x);
		}
		sort(c.begin(),c.end());
		for(int i=0;i<n;i++)
		{
			a[k].push_back(c[i]);
			if(a[k].size()>=sq-1)
				k++;
		}
	}
	for(int t=0;t<m;t++)
	{
		int f;
		cin>>f;
		if(f==1)
		{
			int x;
			cin>>x;
			x^=last;
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
			x^=last;
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
			x^=last;
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
					ans^=cnt;
					last=cnt;
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
			x^=last;
			x--;
			for(int i=0;i<sq;i++)
			{
				if(cnt+a[i].size()>x)
				{
					ans^=a[i][x-cnt];
					last=a[i][x-cnt];
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
			{
				ans^=a[p-1][a[p-1].size()-1];
				last=a[p-1][a[p-1].size()-1];
			}
			else
			{
				auto it=lower_bound(a[p].begin(),a[p].end(),x);
				it--;
				ans^=*it;
				last=*it;
			}
		}
		if(f==6)
		{
			int x;
			cin>>x;
			int p=fnd(0,sq,x);
			if(p<sq&&a[p][a[p].size()-1]<=x)
			{
				ans^=*upper_bound(a[p+1].begin(),a[p+1].end(),x);
				last=*upper_bound(a[p+1].begin(),a[p+1].end(),x);
			}
			else
			{
				ans^=*upper_bound(a[p].begin(),a[p].end(),x);
				last=*upper_bound(a[p].begin(),a[p].end(),x);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
