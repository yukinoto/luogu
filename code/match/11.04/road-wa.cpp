#include <stdio.h>

inline int min(const int &x,const int &y)
{
	if(x>y)
		return y;
	return x;
}

struct node{
	int lc,rc,min;
};
node a[800010];
int top=0;

int n;

void init()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		(a+i)->min=x;
		(a+i)->lc=(a+i)->rc=-1;
	}
	top=n;
	return;
}

int makt(int l,int r)
{
	if(l==r-1)
		return l;
	if(l>=r)
		return -1;
	top++;
	int src=top,mid=(l+r)/2,pl=makt(l,mid),pr=makt(mid,r);
	(a+src-1)->min=min((a+pl)->min,(a+pr)->min);
	(a+src-1)->lc=pl;
	(a+src-1)->rc=pr;
	return src-1;
}

int find(int root)
{
	if((a+root)->min>0)
		return root;
	if((a+root)->lc==-1&&(a+root)->rc==-1)
		return -1;
	int ans=find((a+root)->lc);
	if(ans!=-1)
		return ans;
	return find((a+root)->rc);
}

void change(int root)
{
	(a+root)->min--;
	if((a+root)->lc!=-1)
		change((a+root)->lc);
	if((a+root)->lc!=-1)
		change((a+root)->rc);
	return;
}

bool check()
{
	for(int i=0;i<n;i++)
		if((a+i)->min>0)
			return false;
		else
		{
			if((a+i)->min<0)
				printf("error!\n");
			return false;
		}
	return true;
}

int main()
{
    //freopen("road.in","r",stdin);
    //freopen("road.out","w",stdout);
	init();
	int root=makt(0,n),ans=0;
	while(!check())
	{
		int p=find(root);
		change(p);
		ans++;
	}
	printf("%d\n",ans);
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
