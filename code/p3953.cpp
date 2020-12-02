#include <stdio.h>
#include <string.h>

namespace func{
	inline int min(const int &x,const int &y)
	{
		return x<y?x:y;
	}
	inline int max(const int &x,const int &y)
	{
		return x>y?x:y;
	}
}

int mod;
namespace map{
	int n,m,k;
	int head[100010],wei[200010],to[200010],nxt[200010],top;
	void add(int _from,int _to,int _wei)
	{
		to[top]=_to;
		nxt[top]=head[_from];
		wei[top]=_wei;
		head[_from]=top++;
		return;
	}
	void set()
	{
		memset(head,-1,sizeof(head));
		top=0;
	}
	void init()
	{
		set();
		scanf("%d%d%d%d",&n,&m,&k,&mod);
		for(int i=0;i<m;i++)
		{
			int f,t,w;
			scanf("%d%d%d",&f,&t,&w);
			add(f,t,w);
		}
		return;
	}
}

namespace dij{
	bool token[100010];
	int dis[100010];
	int findp()
	{
		int ansp=0;
		for(int i=1;i<=map::n;i++)
			if(dis[i]<dis[ansp]&&!token[i])
				ansp=i;
		return ansp;
	}
	void relax(int root)
	{
		token[root]=true;
		int p=map::head[root];
		while(p!=-1)
		{
			if(!token[map::to[p]])
				dis[map::to[p]]=func::min(dis[map::to[p]],dis[root]+map::wei[p]);
			p=map::nxt[p];
		}
	}
	void dij()
	{
		memset(token,false,sizeof(token));
		memset(dis,0x3f,sizeof(dis));
		dis[1]=0;
		for(int i=0;i<map::n;i++)
			relax(findp());
		return;
	}
}

namespace work{
	int f[100010][60];
	struct node{
		int p,dis,num;
	};
	node make_node(int p,int dis,int num)
	{
		node ans;
		ans.p=p,ans.dis=dis,ans.num=num;
		return ans;
	}
	class queue{
		private:
			node a[10000010];
			int _front,_end;
		public:
			void clear()
			{
				_front=_end=0;
				return;
			}
			void push(node x)
			{
				a[_end++]=x;
				return;
			}
			node front()
			{
				return a[_front];
			}
			void pop()
			{
				_front++;
				return;
			}
			bool empty()
			{
				return _front>=_end;
			}
	};
	queue q;
	void relax(node from)
	{
		int root=from.p,dis=from.dis,num=from.num;
		int p=map::head[root];
		while(p!=-1)
		{
			int to=map::to[p];
			if(dis+map::wei[p]-dij::dis[to]<=map::k&&dij::dis[to]!=0x3f3f3f3f)
			{
				f[to][dis+map::wei[p]-dij::dis[to]]+=num;
				f[to][dis+map::wei[p]-dij::dis[to]]%=mod;
				q.push(make_node(to,dis+map::wei[p],num%mod));
			}
			p=map::nxt[p];
		}
		return;
	}
	void work()
	{
		q.clear();
		memset(f,0,sizeof(f));
		q.push(make_node(1,0,1));
		while(!q.empty())
		{
			relax(q.front());
			q.pop();
		}
		int ans=0;
		for(int i=0;i<=map::k;i++)
			ans=(ans+f[map::n][i])%mod;
		printf("%d\n",ans);
	}
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
	{
		map::init();
		dij::dij();
		work::work();
	}
}
