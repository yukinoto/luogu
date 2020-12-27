#include <stdio.h>
#include "lib.h"
using namespace std;

int n,m,num[100010];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",num+i);
	tree<int,long long> *tr=new tree<int,long long>(num,0,n);
	for(int i=0;i<m;i++)
	{
		static int f;
		scanf("%d",&f);
		if(f==1)
		{
			static int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			tr->add(l-1,r,x);
		}
		if(f==2)
		{
			static int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",tr->quest(l-1,r));
		}
	}
	return 0;
}
