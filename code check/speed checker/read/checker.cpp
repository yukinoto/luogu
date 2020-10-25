#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int main()
{
	int n,mod;
	scanf("%d%d",&n,&mod);
	srand(time(NULL));
	freopen("st.in","w",stdout);
	printf("%d\n",n);
	for(int i=1;i<n;i++)
		printf("%d ",rand()%mod);
	printf("%d\n",rand()%mod);
	fflush(stdout);
	freopen("result.txt","w",stdout);
	clock_t start,end;
	start=clock();
	system("st1.exe");
	end=clock();
	printf("st1:%dms\n",end-start);
	start=clock();
	system("st2.exe");
	end=clock();
	printf("st2:%dms\n",end-start);
	return 0;
}
