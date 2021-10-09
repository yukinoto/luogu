#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <utility>
using namespace std;

int n,m,s;
vector<pair<int,int>> mp[10010];
stack<int> st;
bool ist[10010];
int k[10010],dis[10010];

void init()
{
	cin>>n>>m>>s;
	for(int i=0;i<m;i++)
	{
		int f,t,w;
		cin>>f>>t>>w;
		mp[f-1].push_back(make_pair(t-1,w));
	}
	return;
}

void spfa()
{
	memset(ist,false,sizeof(ist));
	memset(k,0,sizeof(k));
	memset(dis,0x3f,sizeof(dis));
	st.push(s);
	ist[s]=true;
	k[s]++;
	dis[s]=0;
	while(!st.empty())
	{
		int p=st.top();
		st.pop();
		for(auto i:mp[p])
		{
			if(dis[i.first]>dis[p]+dis[i.second])
			{
				dis[i.first]=dis[p]+dis[i.second];
				if(!ist[i.first])
				{
					st.push(i.first);
					ist[i.first]=true;
					k[i.first]++;
					if(k[i.first]>n)
						return;
				}
			}
		}
	}
	return;
}

void print()
{
	for(int i=0;i<n;i++)
		if(dis[i]==0x3f3f3f3f)
			cout<<0x7fffffff<<endl;
		else
			cout<<dis[i]<<endl;
	return;
}

int main()
{
	init();
	spfa();
	print();
	return 0;
}