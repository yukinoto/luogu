//P2835
#include <cstdio>
#include <queue>
using namespace std;

bool p[210],map[210][210];
int n,ans,deg[210];
void mp(int x)
{
	bool ch[210];
	for(int i=0;i<=0;i++)
		ch[i]=false;
	queue<int> sn;
	sn.push(x);
	ch[x]=true;
	while(!sn.empty())
	{
		int pt=sn.front();
		sn.pop();
		for(int i=1;i<=n;i++)
			if(map[pt][i]&&!ch[i])
			{
				ch[i]=map[x][i]=true;
				sn.push(i);
			}
	}
	return;
}
void cc(int x)
{
	for(int i=x+1;i<=n;i++)
		if(map[x][i]&&map[i][x])
			p[i]=false;
	return;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		p[i]=true;
		int x;
		scanf("%d",&x);
		while(x!=0)
		{
			map[i][x]=true;
			scanf("%d",&x);
		}
	}
	for(int i=1;i<=n;++i)
		mp(i);
	for(int i=1;i<n;++i)
		cc(i);
	for(int i=1;i<=n;i++)
		if(p[i])
			for(int j=1;j<=n;j++)
				if(map[i][j])
					deg[j]++;
	for(int i=1;i<=n;i++)
		if(p[i]&&deg[i]==0)
			ans++;
	printf("%d\n",ans);
	return 0;
}
