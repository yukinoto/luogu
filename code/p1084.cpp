#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <utility>
using namespace std;

class node{
	public:
		int fa,sr;
		vector<int>sons,len;
		long long  deepth,armed;
};

int n,m;
node nd[500010];
int arm[500010];
bool taken[500010];
vector<int> to[500010],we[500010];

void mkt(int root,int sr)
{
	for(int i=0;i<to[root].size();i++)
	{
		if(!taken[to[root][i]])
		{
			taken[to[root][i]]=true;
			nd[root].sons.push_back(to[root][i]);
			nd[root].len.push_back(we[root][i]);
			nd[to[root][i]].fa=root;
			nd[to[root][i]].deepth=nd[root].deepth+we[root][i];
			nd[root].sr=sr;
			if(root==1)
				mkt(to[root][i],i);
			else
				mkt(to[root][i],sr);
		}
	}
	return;
}

void init()
{
	cin>>n;
	for(int i=0;i<n-1;i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		to[u].push_back(v);we[u].push_back(w);
		to[v].push_back(u);we[v].push_back(w);
	}
	nd[1].deepth=0,nd[1].fa=1;
	mkt(1,-1);
	cin>>m;
	for(int i=0;i<m;i++)
	{
		cin>>arm[i];
		nd[arm[i]].armed++;
	}
	return;
}

pair<long long,long long> fin(int root)
{
	if(nd[root].sons.empty())
	{
		if(nd[root].armed>0)
			return make_pair(0,0);
		else
			return make_pair(-1,-1);
	}
	long long mia=0x7fffffffffffffffll,mib=0x7fffffffffffffffll;
	bool flag=false;
	for(int i=0;i<nd[root].sons.size();i++)
	{
		pair<long long,long long> x=fin(nd[root].sons[i]);
		if(x.first==-1)
			flag=true;
		else
			mia=min(mia,x.first);
		if(x.second!=-1)
			mib=min(mib,x.second+nd[root].len[i]);
	}
	if(mib==0x7fffffffffffffffll)
		return make_pair(-1,-1);
	if(flag)
		return make_pair(mib,mib);
	else
		return make_pair(mia,mib);
}

vector<vector<long long> > am;

void work()
{
	if(m<nd[1].sons.size())
	{
		cout<<-1<<endl;
		return;
	}
	vector<long long> id;
	for(int i=0;i<nd[1].sons.size();i++)
	{
		am.push_back(id);
	}
}

int main()
{
	init();
	work();
	return 0;
}
