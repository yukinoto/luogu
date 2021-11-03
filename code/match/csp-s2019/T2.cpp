#include <iostream>
#include <stack>
using namespace std;

typedef long long Int;

int n;
char x[500010];
Int dp[500010],fa[500010];//end in i

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
			cin>>fa[i];
		return;
	}
}

int main()
{
	linear::init();
	linear::work();
	return 0;
}