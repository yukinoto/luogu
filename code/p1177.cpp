#include <stdio.h>

template <typename inte>
void merge(inte *to,inte *f1,int len1,inte *f2,int len2)
{
	int i=0,j1=0,j2=0;
	while(j1<len1&&j2<len2)
	{
		if(f1[j1]<f2[j2])
			to[i++]=f1[j1++];
		else
			to[i++]=f2[j2++];
	}
	while(j1<len1)	to[i++]=f1[j1++];
	while(j2<len2)	to[i++]=f2[j2++];
	return;
}
template <typename inte>
void cpy(inte *from,inte *to,int len)
{
	for(int i=0;i<len;i++)
		to[i]=from[i];
	return;
}
template <typename inte>
void sort(inte *f,int first,int last)
{
	if(first>=last-1)
		return;
	int mid=(first+last)/2;
	inte *f1=new inte[mid-first],*f2=new inte[last-mid];
	cpy<inte>(f,f1,mid-first),cpy<inte>(f+(mid-first),f2,last-mid);
	sort<inte>(f1,0,mid-first),sort<inte>(f2,0,last-mid);
	merge<inte>(f,f1,mid-first,f2,last-mid);
	delete[] f1,f2;
	return;
}

int main()
{
	int n;
	scanf("%d",&n);
	int *a=new int[n];
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	sort<int>(a,0,n);
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
	return 0;
}