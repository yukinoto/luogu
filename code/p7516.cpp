#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n,m;
int mp[1001][1001],sp[1001][1001],d[200001],p[200002];

int main()
{
	memset(mp,-1,sizeof(mp));memset(sp,-1,sizeof(sp));
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
		int s,t;
		cin>>s>>t;
		mp[s][t]=i;
	}
	for(int i=n;i>0;i--)
	{
		sp[i][i]=m;
		for(int j=i+1;j<=n;j++)
		{
			int k;
			int *mj=mp[j],*mi=mp[i];
			for(k=i+1;k+7<=n;k+=8)
			{
				mi[j]=max(mi[j],min(mi[k],mp[k][j]));
				mj[i]=max(mj[i],min(mj[k],mp[k][i]));
				mj[k]=max(mj[k],min(mj[i],mi[k]));
				mi[j]=max(mi[j],min(mi[k+1],mp[k+1][j]));
				mj[i]=max(mj[i],min(mj[k+1],mp[k+1][i]));
				mj[k+1]=max(mj[k+1],min(mj[i],mi[k+1]));
				mi[j]=max(mi[j],min(mi[k+2],mp[k+2][j]));
				mj[i]=max(mj[i],min(mj[k+2],mp[k+2][i]));
				mj[k+2]=max(mj[k+2],min(mj[i],mi[k+2]));
				mi[j]=max(mi[j],min(mi[k+3],mp[k+3][j]));
				mj[i]=max(mj[i],min(mj[k+3],mp[k+3][i]));
				mj[k+3]=max(mj[k+3],min(mj[i],mi[k+3]));
				mi[j]=max(mi[j],min(mi[k+4],mp[k+4][j]));
				mj[i]=max(mj[i],min(mj[k+4],mp[k+4][i]));
				mj[k+4]=max(mj[k+4],min(mj[i],mi[k+4]));
				mi[j]=max(mi[j],min(mi[k+5],mp[k+5][j]));
				mj[i]=max(mj[i],min(mj[k+5],mp[k+5][i]));
				mj[k+5]=max(mj[k+5],min(mj[i],mi[k+5]));
				mi[j]=max(mi[j],min(mi[k+6],mp[k+6][j]));
				mj[i]=max(mj[i],min(mj[k+6],mp[k+6][i]));
				mj[k+6]=max(mj[k+6],min(mj[i],mi[k+6]));
				mi[j]=max(mi[j],min(mi[k+7],mp[k+7][j]));
				mj[i]=max(mj[i],min(mj[k+7],mp[k+7][i]));
				mj[k+7]=max(mj[k+7],min(mj[i],mi[k+7]));
			}
			for(;k<=n;k++)
			{
				mi[j]=max(mi[j],min(mi[k],mp[k][j]));
				mj[i]=max(mj[i],min(mj[k],mp[k][i]));
				mj[k]=max(mj[k],min(mj[i],mi[k]));
			}
			if(mi[j]>sp[i][j])	sp[i][j]=mi[j];
			if(mj[i]>sp[j][i])	sp[j][i]=mj[i];
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++)
		{
			if(sp[i][j]!=-1&&sp[j][i]!=-1)
				d[min(sp[i][j],sp[j][i])]++;
		}
	for(int i=m;i>=0;i--)
		p[i]=p[i+1]+d[i];
	for(int i=0;i<=m;i++)
		cout<<p[i]<<' ';
	cout<<endl;
	return 0;
}