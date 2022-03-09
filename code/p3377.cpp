#include "leftistheap.hpp"
#include "unionset.hpp"
#include <iostream>
#include <utility>
using namespace std;

unionset<100001> st;
leftistheap<pair<int,int>> h[100001];
bool taken[100001];

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		h[i].push(make_pair(x,i));
	}
	for(int i=0;i<m;i++)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int x,y;
			cin>>x>>y;
			if(!st.if_in_same_set(x,y)&&!taken[x]&&!taken[y])
			{
				h[st.get_root(x)].merge(h[st.get_root(y)]);
				st.merge(x,y);
			}
		}
		if(op==2)
		{
			int x;
			cin>>x;
			if(!taken[x])
			{
				cout<<h[st.get_root(x)].top().first<<'\n';
				taken[h[st.get_root(x)].top().second]=true;
				h[st.get_root(x)].pop();
			}
			else
				cout<<"-1\n";
		}
	}
	cout.flush();
	return 0;
}