#include <stdio.h>
#include <algorithm>
using namespace std;

class sets{
	private:
		int father[50010];
		int setNum(int p)
		{
			if(father[p]==p)
				return p;
			return father[p]=setNum(father[p]);
		}
	public:
		sets()
		{
			for(int i=1;i<=50000;i++)
				father[i]=i;
		}
		bool ifInSameSet(int p1,int p2)
		{
			return setNum(p1)==setNum(p2);
		}
		void mergeSet(int p1,int p2)
		{
			father[setNum(p1)]=setNum(p2);
			return;
		}
};
sets nodeSet;

struct node{
	int d1,d2;
	int w,color;
	bool operator <(const node &x)const{
		return this->w<x.w;
	}
};
node edges[1000010];

int v,e,need,ans=0;

int main()
{
	//freopen("P2619_1.in","r",stdin);
	scanf("%d%d%d",&v,&e,&need);
	for(int i=0;i<e;i++)
		scanf("%d%d%d%d",&edges[i].d1,&edges[i].d2,&edges[i].w,&edges[i].color);
	sort(edges,edges+e);
	for(int i=0;i<need;i++)
	{
		int p=0;
		while(edges[p].color!=0||nodeSet.ifInSameSet(edges[p].d1,edges[p].d2))
			p++;
		ans+=edges[p].w;
		nodeSet.mergeSet(edges[p].d1,edges[p].d2);
	}
	for(int i=need;i<v-1;i++)
	{
		int p=0;
		while(edges[p].color!=1||nodeSet.ifInSameSet(edges[p].d1,edges[p].d2))
			p++;
		ans+=edges[p].w;
		nodeSet.mergeSet(edges[p].d1,edges[p].d2);
	}
	printf("%d\n",ans);
	return 0;
}
