//RE
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int>a[50000];
int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		a[x/128].push_back(x);
	}
	int cnt=0;
	for(int i=0;i<50000;i++)
	{
		if(a[i].size()+cnt<k)
		{
			cnt+=a[i].size();
			continue;
		}
		else
		{
			sort(a[i].begin(),a[i].end());
			printf("%d\n",a[i][k-cnt]);
			return 0;
		}
	}
	return -1;
}
