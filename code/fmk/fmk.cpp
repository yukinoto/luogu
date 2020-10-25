//fmk
#include <cstdio>
#include <cstring>

int main()
{
	char nme[50];
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		sprintf(nme,"%d.out",i);
		freopen(nme,"w",stdout);
	}
	return 0;
}
