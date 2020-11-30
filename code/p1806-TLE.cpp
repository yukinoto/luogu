#include <stdio.h>

int cnt=0;
void search(int left,int bef)
{
	if(left==0)
	{
		cnt++;
		return;
	}
	for(int i=bef+1;i<=left;i++)
		search(left-i,i);
	return;
}

/*int main()
{
	int n;
	scanf("%d",&n);
	search(n,0);
	printf("%d\n",cnt-1);
	return 0;
}*/

int main()
{
	freopen("p1806.ans","w",stdout);
	int n;
	scanf("%d",&n);
	for(int i=3;i<=n;i++)
	{
		cnt=0;
		search(i,0);
		printf("%d\n",cnt);
	}
	return 0;
}
