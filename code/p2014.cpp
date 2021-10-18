#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN=302;

int n,m;

class node{
	public:
		int s;
		int dp[MAXN];
		vector<node*>sons;
		void link(node* x)
		{
			sons.push_back(x);
			return;
		}
		void dit()
		{
			dp[0]=0;
			for(int i=1;i<=m;i++)
				dp[i]=s;
			for(auto it:sons)
			{
				it->dit();
				for(int i=m;i>0;i--)
				{
					for(int j=m-i;j>0;j--)
						dp[j+i]=max(dp[j+i],dp[i]+it->dp[j]);
				}
			}
			return;
		}
};

node a[MAXN];

int main()
{
	cin>>n>>m;
	m++;
	for(int i=1;i<=n;i++)
	{
		int k,s;
		cin>>k>>s;
		a[k].link(&a[i]);
		a[i].s=s;
	}
	a[0].s=0;
	a[0].dit();
	cout<<a[0].dp[m]<<endl;
	return 0;
}
