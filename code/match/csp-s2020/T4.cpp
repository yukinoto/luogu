#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
struct node{
	T value;
	node *next,*bef;
};

int t,n;
int a[1000010];
node<pair<int,int>> snk[2000010];
node<pair<int,int>> *front,*back;
int top;
vector<int> ots;
int cho[1000010],otm[1000010];

void init1()
{
	cin>>t>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		snk[top].value=make_pair(a[i],i);
		snk[top].next=snk+top-1;
		snk[top].bef=snk+top+1;
		++top;
	}
	front=snk,back=snk+top-1;
	front->next=nullptr,back->bef=nullptr;
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
	top=0;
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
	{
		snk[top].value=make_pair(a[i],i);
		snk[top].next=snk+top-1;
		snk[top].bef=snk+top+1;
		++top;
	}
	front=snk,back=snk+top-1;
	front->next=nullptr,back->bef=nullptr;
}

void work()
{
	int size=top;
	node<pair<int,int>> *now=back;
	while(front!=back)
	{
		/*auto etn=*snk.begin(),etr=*snk.rbegin();
		cho[etr.second]=snk.size();
		ots.push_back(etn.second);
		otm[etn.second]=snk.size();
		snk.erase(snk.begin());
		snk.erase(etr);
		snk.insert(make_pair(etr.first-etn.first,etr.second));*/
		auto etn=front->value,etr=back->value;
		cho[etr.second]=size;
		ots.push_back(etn.second);
		otm[etn.second]=size;
		size--;
		if(now==front)
			now=back;
		front=front->bef;
		front->next=nullptr;
		if(front!=back)
		{
			auto x=make_pair(etr.first-etn.first,etr.second);
			back=back->next;
			back->bef=nullptr;
			while(now->next!=nullptr&&now->value>=x)
				now=now->next;
			if(now->value<x)
			{
				if(now->bef!=nullptr)
					now->bef->next=snk+top;
				else
					back=snk+top;
				snk[top].value=x;
				snk[top].bef=now->bef;
				snk[top].next=now;
				now->bef=snk+top;
			}
			else
			{
				front->next=snk+top;
				snk[top].value=x;
				snk[top].bef=front;
				snk[top].next=nullptr;
				front=snk+top;
			}
		}
	}
	int ans=1,oas=1;
	for(int i=ots.size()-1;i>=0;i--)
	{
		if(cho[ots[i]]!=-1)
		{
			if(otm[ots[i]]>oas)
			{
				oas=otm[ots[i]];
				if(ans<oas)
					ans=cho[ots[i]];
				else
					ans=min(ans,cho[ots[i]]);
			}
			else
			{
				if(cho[ots[i]]>=oas)
					ans=min(ans,cho[ots[i]]);
			}
		}
	}
	cout<<ans<<endl;
}

int main()
{
	ios::sync_with_stdio(false);
	init1();
	work();
	for(int i=2;i<=t;i++)
	{
		init2();
		work();
	}
	return 0;
}