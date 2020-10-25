#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n,m,s;
struct edge{
    int to,value;
};
vector<edge> map[100100];

void init()
{
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1;i<=m;i++)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        edge z;
        z.to=y;z.value=v;
        map[x].push_back(z);
    }
}

bool fixed[100100];
int dis[100100];
struct dv{
    int p,dis;
    bool operator < (const dv & x)const{return this->dis<x.dis;}
};
priority_queue<dv> changed;
int mp()
{
    while(fixed[changed.top().p])
    {
        changed.pop();
        if(changed.empty())
        	return 0;
	}
	changed.pop();
    return changed.top().p;
}
void relax(int root)
{
    for(vector<edge>::iterator it=map[root].begin();it!=map[root].end();it++)
        if(dis[it->to]>dis[root]+it->value)
        {
            dis[it->to]=dis[root]+it->value;
            dv x;
            x.dis=dis[it->to];
            x.p=it->to;
            changed.push(x);
        }
    return;
}
void dij(int s)
{
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    dv x;
    x.dis=0;x.p=s;
    changed.push(x);
    for(int t=1;t<=n;t++)
    {
        int p=mp();
        if(p==0)
            return;
        fixed[p]=true;
        relax(p);
    }
    return;
}

void fre()
{
	freopen("dij.in","r",stdin);
	freopen("dij2.out","w",stdout);
}

int main()
{
	fre();
    init();
    dij(s);
    for(int i=1;i<n;i++)
    {
    	if(dis[i]==0x3f3f3f3f)
    		dis[i]=0x7fffffff;
        printf("%d ",dis[i]);
	}
    printf("%d\n",dis[n]);
    return 0;
}
