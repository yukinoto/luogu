#include <stdio.h>
#include <string.h>

class queue{
	private:
		int _front,_end;
		int a[1000010];
	public:
		queue()
		{
			_front=_end=0;
			return;
		}
		bool empty()
		{
			return _front>=_end;
		}
		int front()
		{
			return a[_front];
		}
		void push(int x)
		{
			a[_end++]=x;
			return;
		}
		void pop()
		{
			_front++;
			return;
		}
};

queue q;

namespace map{
	int n,m;
	int deepth[1000010],f[1000010];

	int head[1000010],to[4000010],nxt[4000010],top;

	void add(int _from,int _to)
	{
		to[top]=_to;
		nxt[top]=head[_from];
		head[_from]=top++;
		return;
	}

	void init()
	{
		memset(nxt,-1,sizeof(nxt));
		memset(head,-1,sizeof(head));
		scanf("%d%d",&n,&m);
		for(int i=0;i<m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);add(y,x);
		}
	}

	void bfs()
	{
		f[1]=deepth[1]=1;
		q.push(1);
		while(!q.empty())
		{
			int root=q.front();
			q.pop();
			int p=head[root];
			while(p!=-1)
			{
				if(f[to[p]]==0)
					q.push(to[p]);
				if(deepth[to[p]]==0)
					deepth[to[p]]=deepth[root]+1;
				if(deepth[to[p]]==deepth[root]+1)
					f[to[p]]+=f[root];
				f[to[p]]%=100003;
				p=nxt[p];
			}
		}
		return;
	}
}

int main()
{
	map::init();
	map::bfs();
	for(int i=1;i<=map::n;i++)
		printf("%d\n",map::f[i]);
	return 0;
}
