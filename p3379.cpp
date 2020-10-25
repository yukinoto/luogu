#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

struct node{
	int father[25];
	int deepth;
};
node tr[500010];

int n,m,s;
bool intre[500010];
vector<int> edge[500010];
queue<int> q;
void init()
{
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	q.push(s);
	memset(intre,false,sizeof(intre));
	tr[s].deepth=1;
	intre[s]=true;
	while(!q.empty())
	{
		int p=q.front();
		q.pop();
		for(vector<int>::iterator it=edge[p].begin();it!=edge[p].end();it++)
			if(!intre[(*it)])
			{
				tr[*it].father[0]=p;
				tr[*it].deepth=tr[p].deepth+1;
				intre[*it]=true;
				q.push(*it);
			}
	}
}
int father(int nod,int ite)
{
	if(tr[nod].father[ite]!=0)
		return tr[nod].father[ite];
	return tr[nod].father[ite]=father(father(nod,ite-1),ite-1);
}
int skip(int nod,int stp)
{
	for(int i=0;stp!=0&&i<=23;i++)
	{
		int sk=(1<<i);
		if((stp&sk)!=0)
			nod=father(nod,i);
		stp=(stp&(~sk));
	}
	return nod;
}
bool check(int x,int y,int stp)
{
	if(tr[x].deepth!=tr[y].deepth)
		return false;
	x=skip(x,stp);
	y=skip(y,stp);
	return x==y;
}
int skf(int x,int y,int l,int r)
{
	if(l>=r-1)
		return l+1;
	int mid=(l+r)/2;
	if(check(x,y,mid))
		return skf(x,y,l,mid);
	return skf(x,y,mid,r);
}
int fnd(int x,int y)
{
	if(tr[x].deepth!=tr[y].deepth)
	{
		if(tr[x].deepth>tr[y].deepth)
			x=skip(x,tr[x].deepth-tr[y].deepth);
		else
			y=skip(y,tr[y].deepth-tr[x].deepth);
	}
	if(x==y)
		return x;
	return skip(x,skf(x,y,0,tr[x].deepth));
}
int main()
{
	init();
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",fnd(x,y));
	}
	return 0;
}
