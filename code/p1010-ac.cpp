//p1020-nlogn
#include <stdio.h>
#include <string.h>

int ht[100010];
int stc[100010];

int fnd(int l,int r,int h,bool cmp)
{
	if(l==r-1)
		return l;
	int mid=(l+r)/2;
	if((stc[mid-1]<h)==cmp)
		return fnd(mid,r,h,cmp);
	return fnd(l,mid,h,cmp);
}
int lis(int l,int r,bool cmp)
{
	memset(stc,0,sizeof(stc));
	int top=0;
	for(int i=l;i<r;i++)
		if(top==0||(stc[top-1]<ht[i]==cmp))
			stc[top++]=ht[i];
		else
		{
			int p=fnd(0,top,ht[i],cmp);
			stc[p]=ht[i];
		}
	return top;
}

int main()
{
	int i;
	for(i=0;~scanf("%d",ht+i);i++);
	printf("%d %d\n",lis(0,i,false),lis(0,i,true));
	return 0;
}
