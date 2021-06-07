#include <cstdio>

int fnd(int *a,int left,int right,int x)
{
	if(left>=right-1)
		return a[left]==x?left:-1;
	int mid=(left+right)/2;
	if(a[mid]<=x)
		return fnd(a,mid,right,x);
	return fnd(a,left,mid,x);
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int *a=new int[n],*p=new int[n];
	for(int i=0;i<n;i++)
		scanf("%d",&(i[a]));
	for(int i=0;i<n;i++)
		if(i!=0&&a[i]==a[i-1])
			p[i]=p[i-1];
		else
			p[i]=i;
	for(int i=0;i<m;i++)
	{
		int x;
		scanf("%d",&x);
		int as=fnd(a,0,n,x);
		if(as==-1)
			printf("%d ",-1);
		else
			printf("%d ",p[as]+1);
	}
	delete a;
	delete p;
	return 0;
}
