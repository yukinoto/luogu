#include <iostream>
#include <cstring>
using namespace std;

int n,m;
int c[5],a[400];

void init()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int x;
        cin>>x;
        c[x]++;
    }
    return;
}

int dp[7][41][41][41];

void work()
{
    memset(dp,-1,sizeof(dp));
    dp[1][c[1]][c[2]][c[3]]=a[1];
    for(int i=1;i<n;i++)
    {
        for(int j1=0;j1<=c[1];j1++)
            for(int j2=0;j2<=c[2];j2++)
                for(int j3=0;j3<=c[3];j3++)
                {
                    int j4=(n-j1-j2*2-j3*3-1)/4;
                    if(dp[i%7][j1][j2][j3]!=-1)
                    {
                        if(j1>0)
                            if(dp[(i+1)%7][j1-1][j2][j3]<dp[i%7][j1][j2][j3]+a[i+1])
                                dp[(i+1)%7][j1-1][j2][j3]=dp[i%7][j1][j2][j3]+a[i+1];
                        if(j2>0)
                            if(dp[(i+2)%7][j1][j2-1][j3]<dp[i%7][j1][j2][j3]+a[i+2])
                                dp[(i+2)%7][j1][j2-1][j3]=dp[i%7][j1][j2][j3]+a[i+2];
                        if(j3>0)
                            if(dp[(i+3)%7][j1][j2][j3-1]<dp[i%7][j1][j2][j3]+a[i+3])
                                dp[(i+3)%7][j1][j2][j3-1]=dp[i%7][j1][j2][j3]+a[i+3];
                        if(j4>0)
                            if(dp[(i+4)%7][j1][j2][j3]<dp[i%7][j1][j2][j3]+a[i+4])
                                dp[(i+4)%7][j1][j2][j3]=dp[i%7][j1][j2][j3]+a[i+4];
                        dp[i%7][j1][j2][j3]=-1;
                    }
                }
    }
    cout<<dp[n%7][0][0][0]<<endl;
    return;
}

int main()
{
    init();
    work();
    return 0;
}