#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class mtst{
	private:
		int st[10010];
	public:
		mtst(int n)
		{
			for(int i=0;i<=n;i++)
				st[i]=i;
			return;
		}
		int fa(int x)
		{
			if(st[x]==x)
				return x;
			return st[x]=fa(st[x]);
		}
		void merge(int x,int y)
		{
			st[fa(x)]=st[fa(y)];
			return;
		}
};

namespace origin{
	int n,m;
	bool mp[10010][10010];
	int wei[100010];
	void init()
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			cin>>wei[i];
		for(int i=1;i<=m;i++)
		{
			int x,y;
			cin>>x>>y;
			mp[x][y]=true;
		}
		return;
	}
	int status[10010],dfn[10010],low[10010],cnt;
	mtst st(10000);
	stack<int> s;
	void tarjan(int root)
	{
		low[root]=dfn[root];
		status[root]=1;
		s.push(root);
		for(int i=1;i<=n;i++)
		{
			if(mp[root][i]&&status[i]==0)
			{
				dfn[i]=cnt++;
				tarjan(i);
				if(low[i]<low[root])
					low[root]=low[i];
			}
			if(mp[root][i]&&status[i]==1)
			{
				if(dfn[i]<low[root])
					low[root]=dfn[i];
			}
		}
		if(dfn[root]==low[root])
			while(true)
			{
				st.merge(s.top(),root);
				status[s.top()]=-1;
				if(s.top()==root)
				{
					s.pop();
					break;
				}
				s.pop();
			}
		return;
	}
	void fl()
	{
		for(int i=1;i<=n;i++)
			if(status[i]!=-1)
			{
				dfn[i]=cnt++;
				tarjan(i);
			}
		return;
	}
}

namespace nmp{
	int n;
	int wei[10010],dp[10010],idg[10010];
	bool mp[10010][10010];
	void init()
	{
		origin::init();
		origin::fl();
		n=origin::n;
		for(int i=1;i<=n;i++)
		{
			if(origin::st.fa(i)!=i)
				wei[i]=-1;
			wei[origin::st.fa(i)]+=origin::wei[i];
			for(int j=1;j<=n;j++)
			{
				if(origin::mp[i][j]&&!mp[origin::st.fa(i)][origin::st.fa(j)])
				{
					mp[origin::st.fa(i)][origin::st.fa(j)]=true;
					idg[origin::st.fa(j)]++;
				}
			}
		}
		for(int i=1;i<=n;i++)
			if(mp[i][i])
			{
				mp[i][i]=false;
				idg[i]--;
			}
		return;
	}
	/*int fnd()
	{
		for(int i=1;i<=n;i++)
			if(idg[i]==0&&wei[i]>=0)
				return i;
		return -1;
	}*/
	int work()
	{
		init();
		/*while(true)
		{
			int p=fnd();
			if(p==-1)
				break;
			dp[p]+=wei[p];
			wei[p]=-1;
			for(int i=1;i<=n;i++)
				if(wei[i]>=0&&mp[p][i])
				{
					if(dp[i]<dp[p])
						dp[i]=dp[p];
					idg[i]--;
				}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(dp[i]>ans)
				ans=dp[i];
		}
		return ans;*/
		queue<int> q;
		for(int i=1;i<=n;i++)
			if(wei[i]!=-1&&idg[i]==0)
				q.push(i);
		while(!q.empty())
		{
			int p=q.front();
			q.pop();
			dp[p]+=wei[p];
			for(int i=1;i<=n;i++)
				if(mp[p][i])
				{
					idg[i]--;
					if(idg[i]==0)
						q.push(i);
					if(dp[i]<dp[p])
						dp[i]=dp[p];
				}
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(dp[i]>ans)
				ans=dp[i];
		}
		return ans;
	}
}

int main()
{
	cout<<nmp::work()<<endl;
	return 0;
}
