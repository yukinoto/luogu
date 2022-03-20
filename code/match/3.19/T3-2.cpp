#include <iostream>
using namespace std;

int top,ans[10000000],as;
int ttop,tans[10000000];
int n;
int a[1001],tmp[1001];

void sv(int x)
{
	as=x;
	top=ttop;
	for(int i=0;i<top;i++)
		ans[i]=tans[i];
	return;
}

void cp()
{
	ttop=0;
	for(int i=1;i<=n;i++)
		a[i]=tmp[i];
	return;
}

void roll(int p,int x,bool dir)
{
	if(dir)
	{
		int tmp=a[p+x-1];
		for(int i=p+x-1;i>p;i--)
			a[i]=a[i-1];
		a[p]=tmp;
		tans[ttop++]=p;
	}
	else
	{
		int tmp=a[p];
		for(int i=p;i<p+x-1;i++)
			a[i]=a[i+1];
		a[p+x-1]=tmp;
		tans[ttop++]=-p;
	}
	return;
}

bool check()
{
	for(int i=1;i<=n;i++)
		if(a[i]!=i)
			return false;
	return true;
}

bool set(int x,int num)
{
	int p=0;
	for(int i=1;i<=n;i++)
		if(a[i]==num)
		{
			p=i;
			break;
		}
	while(num+x-1<p)
	{
		roll(p-x+1,x,true);
		p=p-x+1;
	}
	if(num+x-1>n)
		return false;
	while(a[num]!=num)
		roll(num,x,false);
	return true;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>tmp[i];
	}
	top=0x7fffffff;
	for(int x=2;x<=n;x++)
	{
		cp();
		for(int i=1;i<=n;i++)
		{
			if(!set(x,i))
				break;
			if(ttop>23*n)
				break;
		}
		if(check()&&ttop<top)
			sv(x);
		if(top<=23*n)
			break;
	}
	cout<<as<<'\n'<<top<<'\n';
	for(int i=0;i<top;i++)
	{
		if(ans[i]>0)
			cout<<ans[i]<<" 1\n";
		else
			cout<<-ans[i]<<" 0\n";
	}
	return 0;
}