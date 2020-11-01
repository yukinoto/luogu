#include <stdio.h>

int n,k;
long long f[16][16386][200];
inline int mnxt(int x)
{
	x<<=1;
	int ans=0;
	for(int i=1;i<=n;i++)
		if((x&(1<<i))!=0)
			ans|=(1<<(i-1))|(1<<(i))|(1<<(i+1));
	return ans>>1;
}
inline bool check(int bef,int x)
{
	return ((bef&x)==0)&&((x&(x<<1))==0);
}
inline int countbit(int x)
{
	int ans=0;
	while(x!=0)
	{
		x&=x-1;
		ans++;
	}
	return ans;
}
int main()
{
	scanf("%d%d",&n,&k);
	f[0][0][0]=1;
	for(register int i=0;i<n;i++)
		for(register int j=0;j<(1<<n);j++)
			for(register int l=0;l<k;l++)
				if(f[i][j][l]!=0)
				{
					register int bf=mnxt(j);
					for(register int m=0;m<(1<<n);m++)
						if(check(bf,m))
							f[i+1][m][l+countbit(m)]+=f[i][j][l];
				}
	register long long ans=0;
	for(register int i=1;i<=n;i++)
		for(register int j=0;j<(1<<n);j++)
			ans+=f[i][j][k];
	printf("%lld\n",ans);
	return 0;
}
