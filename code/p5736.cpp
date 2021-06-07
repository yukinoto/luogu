#include <stdio.h>

bool isprim(const int &x)
{
	if(x<=1)
		return false;
	for(int i=2;i*i<=x;i++)
		if(x%i==0)
			return false;
	return true;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		int x;
		scanf("%d",&x);
		if(isprim(x))
			printf("%d ",x);
	}
	return 0;
}
