#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int t,n;
int a[1000010];
set<pair<int,int>> snk;//value,nth
vector<int> ots;
int cho[1000010],otm[1000010];

void init1()
{
	cin>>t>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		snk.insert(make_pair(a[i],i));
	for(int i=1;i<=n;i++)
	{
		cho[i]=-1;
		otm[i]=-1;
	}	
	return;
}
istream& operator >>(istream&ins,pair<int,int>&x)
{
	return ins>>x.first>>x.second;
}
void init2()
{
	snk.clear();
	ots.clear();
	for(int i=1;i<=n;i++)
	{
		cho[i]=-1;
		otm[i]=-1;
	}	
	int k;
	cin>>k;
	for(int i=0;i<k;i++)
	{
		pair<int,int>x;
		cin>>x;
		a[x.first]=x.second;
	}
	for(int i=1;i<=n;i++)
		snk.insert(make_pair(a[i],i));
}

void work()
{
	while(snk.rbegin()->first>snk.begin()->first)
	{
		auto etn=*snk.begin(),etr=*snk.rbegin();
		cho[etr.second]=snk.size();
		ots.push_back(etn.first);
		otm[etn.first]=snk.size();
		snk.erase(snk.begin());
		snk.erase(etr);
		snk.insert(make_pair(etr.first-etn.first,etr.second));
	}
	int ans=1;
	for(int i=ots.size()-1;i>=0;i--)
	{
		if(cho[ots[i]]!=-1)
		{
			if(ans>otm[ots[i]])
			{
				ans=otm[ots[i]];
				
			}
		}
	}
}