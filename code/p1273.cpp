#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

inline int max(const int &x,const int &y)
{
	return x>y?x:y;
}

struct edge{
	int wei,to;
};
vector<edge> tr[3010];
int n,m,f[3010][3010];

edge make_edge(int _wei,int _to)
{
	edge ans;
	ans.wei=_wei,ans.to=_to;
	return ans;
}

void dp(int root)
{
	for(vector<edge>::iterator it=tr[root].begin();it!=tr[root].end();it++)
	{
		dp(it->to);
		for(int i=m;i>=0;i--)
			if(f[root][i]!=0x80808080)
				for(int j=0;j<=m-i;j++)
					if(f[it->to][j]!=0x80808080)
						f[root][i+j]=max(f[root][i+j],f[root][i]+f[it->to][j]-it->wei);
	}
}

int main()
{
	memset(f,0x80,sizeof(f));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-m;i++)
	{
		int num;
		scanf("%d",&num);
		for(int j=1;j<=num;j++)
		{
			int a,c;
			scanf("%d%d",&a,&c);
			tr[i].push_back(make_edge(c,a));
		}
		f[i][0]=0;
	}
	for(int i=n-m+1;i<=n;i++)
		scanf("%d",&f[i][1]);
	dp(1);
	for(int i=m;i>=0;i--)
		if(f[1][i]>=0)
		{
			printf("%d\n",i);
			return 0;
		}
	return -1;
}
