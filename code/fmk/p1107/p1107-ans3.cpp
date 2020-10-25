//p1107-ans3
#include<bits/stdc++.h>
using namespace std;
int N,H,D,num,maap[2002][2002]={0},dp[2002][2002]={0},ans=0,maxx[2002]={0};
int main()
{
	freopen("p1107.in","r",stdin);
	freopen("p1107-ans3.out","w",stdout);
    scanf("%d%d%d",&N,&H,&D);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&num);//一棵树上一共多少柿子；
        for(int j=1;j<=num;j++)
        {
            int xb;
            scanf("%d",&xb);//奇怪的变量名，大佬们见谅;
            maap[xb][i]++;//记录柿子的位置；
        }
    }
    for(int i=1;i<=H;i++)//先是H的循环还是N的不好想；
        for(int j=1;j<=N;j++)//但是因为我们是从最高处往下跳；
        {//且不确定向那一棵树跳，所以i是第一重1~h；
         //又因为n棵树并列关系所以j是第二重1~n（写n~1也未尝不可）；
            dp[i][j]=max(dp[i][j],dp[i-1][j]);//一定可以向下跳一格；
            if(i>D)//如果可以换树，考虑换哪棵树；
            dp[i][j]=max(dp[i][j],maxx[i-D]);
            dp[i][j]+=maap[i][j];//加上现在位置的柿子；
            maxx[i]=max(maxx[i],dp[i][j]);
            //求出这一高度接下来最多吃的柿子量
        }
    for(int j=1;j<=N;j++)ans=max(ans,dp[H][j]);
    printf("%d",ans);
    return 0;
}
