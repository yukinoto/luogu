//p1107-ans
#include<cstdio>
#include<iostream>
using namespace std;
#define gc ch=getchar()
inline int read(){
	int x=0,f=1;char gc;
	for(;ch<'0'||ch>'9';gc)if(ch=='-')f=-1;
	for(;ch>='0'&&ch<='9';gc)x=x*10+ch-'0';
	return x*f;
}
#undef gc
//以上为快读，听说不用读入优化会TLE,比如cin、cout
int n,h,d,g[4005],a[4005][4005],f[4005][4005];
//g[i]表示高度为i时f[i][j]的最大值
int main(){
	freopen("p1107.in","r",stdin);
	freopen("p1107-ans.out","w",stdout);
	n=read();h=read();d=read();
	for(int i=1;i<=n;i++){
		a[i][0]=read();
		for(int j=1;j<=a[i][0];j++)a[i][read()]++;
        //注意，是每个上面有1个，所以要加一，而不是赋值为一
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=n;j++)f[i][j]=f[i-1][j]+a[j][i];
		if(i>d)for(int j=1;j<=n;j++)f[i][j]=max(f[i][j],g[i-d]+a[j][i]);
		for(int j=1;j<=n;j++)g[i]=max(f[i][j],g[i]);
        //转移见上
	}
	printf("%d",g[h]);
}
