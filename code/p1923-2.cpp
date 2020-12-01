#include <stdio.h>

int n,k;
int a[5000010];
inline void swap(int &x,int &y)
{
	int t=x;
	x=y;
	y=t;
	return;
}
void srt(int l,int r)
{
	if(l>=r-1)
		return;
	int x=a[l];
	int i=l+1,j=r-1;
	while(i<j)
	{
		while(a[i]<=a[l]&&i<j)	i++;
		while(a[j]>a[l]&&i<j)	j--;
		swap(a[i],a[j]);
	}
	int mid=(a[i]<=a[l])?i+1:i;
	swap(a[mid-1],a[l]);
	if(mid>k)
		srt(l,mid-1);
	else
		srt(mid,r);
	return;
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	srt(0,n);
	printf("%d\n",a[k]);
	return 0;
}
