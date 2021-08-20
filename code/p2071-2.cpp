#include <iostream>
#include <queue>
using namespace std;

int n;
int head[6002];
struct edge{
	int to,next,w;
};
int top=0;
edge e[100001];
int deepth[6002];
void add_edge(int from,int to,int w)
{
	e[top].to=to;
	e[top].next=head[from];
	e[top].w=w;
	head[from]=top++;
	return;
}

void init()
{
	for(int i=0;i<6002;i++)
		head[i]=-1;
	cin>>n;
	for(int i=1;i<=n*2;i++)
	{
		int x,y;
		cin>>x>>y;
		add_edge(0,i,1);
		add_edge(i,n*2+x,1);
		add_edge(i,n*2+y,1);
	}
	for(int i=n*2+1;i<=n*3;i++)
		add_edge(i,n*3+1,2);
	return;
}

bool bfs(int root)
{
	queue<int> q;
	q.push(root);\
	for(int i=0;i<=n*3+1;i++)
		deepth[i]=-1;
	deepth[root]=0;
	while(!q.empty())
	{
		int r=q.front();
		q.pop();
		int p=head[r];
		while(p!=-1)
		{
			if(deepth[e[p].to]==-1&&e[p].w>0)
			{
				q.push(e[p].to);
				deepth[e[p].to]=deepth[r]+1;
			}
			p=e[p].next;
		}
	}
	return deepth[n*3+1]!=-1;
}

int dfs(int root,int flow)
{
	if(root==n*3+1)
		return flow;
	int rcd=flow;
	int p=head[root];
	while(p!=-1&&flow>0)
	{
		if(deepth[e[p].to]==deepth[root]+1&&e[p].w>0)
		{
			int x=dfs(e[p].to,min(flow,e[p].w));
			flow-=x;
			e[p].w-=x;
			add_edge(e[p].to,root,x);
		}
		p=e[p].next;
	}
	return rcd-flow;
}

int dinic(int from,int to)
{
	int ans=0;
	while(bfs(from))
		ans+=dfs(from,n*2);
	return ans;
}

int main()
{
	init();
	cout<<dinic(0,n*3+1)<<endl;
	return 0;
}
