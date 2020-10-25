//p2849
#include <stdio.h>

int n,k;
int head,tail,top,x[510],y[510],bef[510],nxt[510];
int abs(int x)
{
	if(x<0)
		return -x;
	return x;
}
int dir(int a,int b)
{
	return abs(x[a]-x[b])+abs(y[a]-y[b]);
}
int del(int p)
{
	return dir(bef[p],p)+dir(p,nxt[p])-dir(bef[p],nxt[p]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		int nx,ny;
		scanf("%d%d",&nx,&ny);
		bool flag=false;
		for(int j=1;j<i;j++)
			if(x[j]==nx&&y[j]==ny)
			{
				flag=true;
				break;
			}
		if(flag)
			continue;
		x[++top]=nx;
		y[top]=ny;
		bef[top]=tail;
		nxt[tail]=top;
		tail=top;
	}
	for(int i=1;i<=k;i++)
	{
		int p=nxt[head],ansp=p;
		while(p!=tail)
		{
			if(del(p)>del(ansp))
				ansp=p;
			p=nxt[p];
		}
		bef[nxt[ansp]]=bef[ansp];
		nxt[bef[ansp]]=nxt[ansp];
	}
	int ans=0,p=head;
	while(p!=tail)
		ans+=dir(p,nxt[p]);
	printf("%d\n",&ans);
	return 0;
}
