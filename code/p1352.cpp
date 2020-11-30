#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

bool father[6010];
int n;
int a[6010],f[6010],root;
vector<int>map[6010];

int dp(int root)
{
	if(f[root]!=0)
		return f[root];
	if(map[root].empty())
		return max(0,a[root]);
	int sum1=0,sum2=0;
	for(vector<int>::iterator it=map[root].begin();it!=map[root].end();it++)
	{
		sum1+=dp(*it);
		if(map[*it].empty())
			continue;
		for(vector<int>::iterator it2=map[*it].begin();it2!=map[*it].end();it2++)
			sum2+=dp(*it2);
	}
	if(a[root]>0)
		sum2+=a[root];
	return f[root]=max(sum1,sum2);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		map[y].push_back(x);
		father[x]=true;
	}
	for(int i=1;i<=n;i++)
		if(!father[i])
		{
			root=i;
			break;
		}
	printf("%d\n",dp(root));
	return 0;
}
