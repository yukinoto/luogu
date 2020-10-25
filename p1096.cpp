//p1096
#include <stdio.h>

struct num{
	int a[100];
};
num zro;
num c(num a,num b)
{
	num ans=zro;
	for(int i=0;i<45;i++)
		for(int j=0;j<45;j++)
			ans.a[i+j]+=a.a[i]*a.a[j];
	for(int i=0;i<100;i++)
	{
		ans.a[i+1]=ans.a[i]/10;
		ans.a[i]%=10;
	}
	return ans;
}
num p(int n,num x)
{
	if(n==0)
		return x;
	x=c(x,x);
	if((n&(n<<31))!=0)
	{
		for(int i=0;i<99;i++)
			x.a[i]*=2;
		for(int i=0;i<99;i++)
		{
			x.a[i+1]=x.a[i]/10;
			x.a[i]%=10;
		}
	}	
	return x;
}
num o;
int main()
{
	unsigned int n;
	scanf("%d",&n);
	while((n&(1<<31))==0)
		n<<=1;
	o.a[0]=1;
	num ans=p(n,o);
	bool flag=false;
	for(int i=99;i>=0;i--)
	{
		if(ans.a[i]!=0)
			flag=true;
		if(flag)
			printf("%d",&ans.a[i]);
	}
	printf("\n");
	return 0;
}
