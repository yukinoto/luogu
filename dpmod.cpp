#include <cstdio>

const int p[10]={1,2,4,8,16,32,64,128,256,512};

int n,m;
int f[60][1010];

bool check(int sta,int nxt)
{
	for(int i=0;i<m;i++)
		if(sta&(1<<i)>0&&nxt&(1<<i)>0)
			return false;
	int c=sta&nxt;
	for(int i=0;i<m-2;i++)
		if(c&(1<<i)>0&&c&(1<<(i+2))>0&&c&(i<<(i+1))==0)
			return false;
	return true;
}

void search(int st,int deep)
{
	if(deep==n+1)
		return;
	for(int i=0;i<p[m];i++)
		if(check(st,i))
		{
			search(i,deep+1);
			f[st][deep]+=f[i][deep+1];
		}
	return;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<p[m];i++)
		f[i][n+1]=1;
	search(0,1);
	for(int i=0;i<p[m];i++)
	{
		for(int j=1;j<=n;j++)
			printf("%d ",f[i][j]);
		printf("\n");
	}
	int sum=0;
	for(int i=0;i<p[m];i++)
		sum+=f[i][1];
	printf("%d\n",sum);
	return 0;
}
