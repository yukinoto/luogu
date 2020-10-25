//p1107-ans2
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
using namespace std;
typedef long long ll;
int a[2020][5010]={0};
int dp[2020][5010]={0};
int m[2010]={0};
int n,h,d;
int read()
{
    char ch=getchar();
    while(!isdigit(ch))
    	ch=getchar();
    int x=0;
    while(isdigit(ch))
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x;
}
void print()
{
    for(int i=h;i>=1;i--)
    {
        for(int j=1;j<=n;j++)
        {
            dp[j][i]=max(dp[j][i+1],m[i+d])+a[j][i];
            m[i]=max(dp[j][i],m[i]);
        }
    }
    printf("%d\n",m[1]);
}
int main()
{
	freopen("p1107.in","r",stdin);
	freopen("p1107-ans2.out","w",stdout);
	scanf("%d%d%d",&n,&h,&d);
	int x,y;
    for(int i=1;i<=n;i++)
    {
        x=read();
        for(int j=1;j<=x;j++)
        {
            y=read();
            a[i][y]++;
        }
    }
    print();
	return 0;
}
