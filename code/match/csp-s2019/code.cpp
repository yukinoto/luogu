#include <stdio.h>

void gll(int len,unsigned long long cad)
{
	if(len==1)
	{
		printf("%lld",cad);
		return;
	}
	printf("%lld",(cad>>(len-1)));
	unsigned long long per=(1ull<<(len-1))-1;
	if(cad>>(len-1)==0)	gll(len-1,cad&per);
	else gll(len-1,(cad^per)&per);
	return;
}
int main()
{
	freopen("code.in","r",stdin);
	freopen("code.out","w",stdout);
	int len;
	unsigned long long num;
	scanf("%d%llud",&len,&num);
	gll(len,num);
	return 0;
}
