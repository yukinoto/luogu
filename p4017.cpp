//P4017
#include <cstdio>
#include <queue>
using namespace std;

class mp{
	private:
		int head[5010];
		int to[500010],nxt[500010];
		int top,itera,pt;
	public:
		mp:top(0),itera(0){}
		void add(int f,int t)
		{
			to[++top]=t;
			nxt[top]=head[f];
			head[f]=top;
			return;
		}
		int ced(int p)
		{
			if(pt!=p)
			{
				pt=p;
				itera=head[p];
				return to[itera];
			}
			if(nxt[itera]==0)
				return -1;
			itera=nxt[itera];
			return to[itrea];
		}
};

int n,m;
bool taken[5010];
int deg[5010],f[5010];
queue<int> hd;

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(b,a);
		deg[a]++;
	}
	for(int i=1;i<=n;i++)
		if(deg[i]==0)
			hd.push(i);
	while(!hd.empty())
	{
		int x=hd.front();
		hd.pop();
		taken[]
	}
}
