#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;

int n,m,k,t;
struct node{
	int x,y,p;
	bool operator < (const node &x) const
	{
		if(this->p==x.p)
		{
			if(this->x==x.x)
				return this->y<x.y;
			return this->x<x.x;
		}
		return this->p>x.p;
	}
};
inline bool cmp(const node &x,const node &y)
{
	if(x.x==y.x)
		return x.y<y.y;
	return x.x<y.x;
}
node a[4010];
int main()
{
	scanf("%d%d%d%d",&n,&m,&k,&t);
	for(node *i=a;i<a+k;i++)
		scanf("%d%d%d",&(i->x),&(i->y),&(i->p));
	sort(a,a+k,cmp);
	int ans=a[0].p;
	set<node> f;
	f.insert(a[0]);
	for(int i=1;i<k;i++)
	{
		for(set<node>::iterator it=f.begin();it!=f.end();it++)
			if(abs(a[i].y-it->y)<=(a[i].x-it->x)*t)
			{
				a[i].p+=it->p;
				break;
			}
		f.insert(a[i]);
		if(a[i].p>ans)
			ans=a[i].p;
	}
	printf("%d\n",ans);
	return 0;
}
