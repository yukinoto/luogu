#include <stdio.h>

int n,k;
struct node{
	int x,y;
};
node a[60];
void init()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	return;
}
int main()
{
	init();
	
}
