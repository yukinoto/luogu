#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>
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
set<int> changed;
int mp()
{
    int ansp=0;
    for(set<int>::iterator it=changed.begin();it!=changed.end();it++)
        if(!fixed[*it]&&dis[*it]<dis[ansp])
            ansp=*it;
    return ansp;
}
void relax(int root)
{
    for(vector<edge>::iterator it=map[root].begin();it!=map[root].end();it++)
        if(dis[it->to]>dis[root]+it->value)
        {
            dis[it->to]=dis[root]+it->value;
            changed.insert(it->to);
        }
    return;
}
void dij(int s)
{
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    changed.insert(s);
    for(int t=1;t<=n;t++)
    {
        int p=mp();
        if(p==0)
            return;
        fixed[p]=true;
        changed.erase(p);
        relax(p);
    }
    return;
}

void fre()
{
	freopen("dij.in","r",stdin);
	freopen("dij.out","w",stdout);
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
