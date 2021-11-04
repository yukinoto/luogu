#include <iostream>
#include <stack>
#include <vector>
using namespace std;

typedef long long Int;

int n;
char x[500010];
Int dp[500010];
int fa[500010];//end in i
vector<int>sons[500010];

stack<int> st;

template<typename T>
void print_debug(T *a)
{
	for(int i=1;i<=n;i++)
	{
		cout<<a[i]<<' ';
	}
	cout<<endl;
	return;
}

namespace linear{
	void init()
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>x[i];
		for(int i=2;i<=n;i++)
			cin>>fa[i];
		return;
	}
	void work()
	{
		for(int i=1;i<=n;i++)
		{
			if(x[i]=='(')
			{
				st.push(i);
			}
			else
			{
				if(st.empty())
				{
					continue;
				}
				int p=st.top();
				st.pop();
				dp[i]=dp[p-1]+1;
			}
		}
		//print_debug(dp);
		Int pre=0,ans=0;
		for(int i=1;i<=n;i++)
		{
			pre=pre+dp[i];
			ans^=(pre*i);
		}
		cout<<ans<<endl;
		return;
	}
}

namespace full{
	void init()
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>x[i];
		for(int i=2;i<=n;i++)
		{
			cin>>fa[i];
			sons[fa[i]].push_back(i);
		}
		return;
	}
	void dfs(int root)
	{
		if(x[root]=='(')
		{
			st.push(fa[root]);
			for(auto i:sons[root])
			{
				dfs(i);
			}
			st.pop();
		}
		else
		{
			if(!st.empty())
			{
				int p=st.top();
				st.pop();
				dp[root]=dp[p]+1;
				for(auto i:sons[root])
				{
					dfs(i);
				}
				st.push(p);
			}
			else
			{
				for(auto i:sons[root])
				{
					dfs(i);
				}
			}
		}
		return;
	}
	Int ans=0;
	void dfs1(int root,Int sum)
	{
		sum+=dp[root];
		ans^=Int(root)*sum;
		for(auto i:sons[root])
			dfs1(i,sum);
		return;
	}
	void work()
	{
		dfs(1);
		dfs1(1,0);
		cout<<ans<<endl;
	}
}

int main()
{
	full::init();
	full::work();
	return 0;
}