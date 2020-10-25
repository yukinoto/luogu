#include <stdio.h>
#include <string>
using namespace std;

bool c(int x)
{
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return false;
	return true;
}
int main()
{
	string st;
	char ch[50];
	for(int div=1;div<=10000;div++)
	{
		sprintf(ch,"%d",div);
		st[0]=ch[0];
		for(int i=1;ch[i-1]!='\0';i++)
			st[i]=ch[i];
		freopen("prim-"+st+".txt","w",stdout);
		for(int i=2;i<0x0fffffff;i++)
			if(c(i))
				printf("%d\n",i);
	}
	return 0;
}
