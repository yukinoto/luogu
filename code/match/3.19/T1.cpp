#include <iostream>
#include <utility>
#include <algorithm>
#include <cstdlib>
using namespace std;

int n,m;
int a[110][110];

pair<int,int> ans[100000];
int top=0;

int an(int x){return n+1-x;}
int am(int x){return m+1-x;}

void revn(int k)
{
	for(int i=1;i<=(m>>1);i++)
		swap(a[k][i],a[k][am(i)]);
	ans[top++]=make_pair(0,k);
	return;
}

void revm(int k)
{
	for(int i=1;i<=(n>>1);i++)
		swap(a[i][k],a[an(i)][k]);
	ans[top++]=make_pair(1,k);
	return;
}

void work(int x,int y)
{
	int c1=0,c2=0;
	if(a[x][y]==y)	c1++;
	if(a[an(x)][y]==y)	c1++;
	if(a[an(x)][am(y)]==y)	c1++;
	if(a[x][am(y)]==y)	c1++;
	if(a[x][y]==am(y))	c2++;
	if(a[an(x)][y]==am(y))	c2++;
	if(a[an(x)][am(y)]==am(y))	c2++;
	if(a[x][am(y)]==am(y))	c2++;
	if(c1!=2||c2!=2)
	{
		cout<<"NO\n";
		exit(0);
	}
	if(y==0)
	{
		if(a[an(x)][y]==y)
		{
			if(a[x][y]==y)
			{
				revm(am(y));
				revn(an(x));
			}
			else
				revn(x);
		}
		if(a[an(x)][am(y)]==y)
		{
			if(a[an(x)][y]==y)
			{
				revm(am(y));
				revn(x);
			}
			else
				revn(an(x));
		}
		return;
	}
	if(a[x][am(y)]==y&&a[an(x)][am(y)]==y)
	{
		revn(x);
		revm(am(y));
		revm(y);
		revn(x);
	}
	else if(a[x][y]==y&&a[an(x)][am(y)]==y)
	{
		revm(am(y));
		revn(an(x));
		revm(am(y));
		revn(an(x));
	}
	else if(a[x][y]==y&&a[x][am(y)]==y)
	{
		revn(an(x));
		revm(am(y));
		revn(an(x));
	}
	else if(a[x][am(y)]==y&&a[an(x)][y]==y)
	{
		revm(am(y));
		revn(x);
		revm(am(y));
		revn(x);
	}
	else if(a[an(x)][y]==y&&a[an(x)][am(y)]==y)
	{
		revn(x);
		revm(am(y));
		revn(x);
	}
	return;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=(n>>1);i++)
		for(int j=1;j<=(m>>1);j++)
			work(i,j);
	cout<<"YES\n";
	cout<<top<<'\n';
	for(int i=0;i<top;i++)
		cout<<ans[i].first<<' '<<ans[i].second<<'\n';
	return 0;
}