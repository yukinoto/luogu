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
        scanf("%d",&num);//һ������һ���������ӣ�
        for(int j=1;j<=num;j++)
        {
            int xb;
            scanf("%d",&xb);//��ֵı������������Ǽ���;
            maap[xb][i]++;//��¼���ӵ�λ�ã�
        }
    }
    for(int i=1;i<=H;i++)//����H��ѭ������N�Ĳ����룻
        for(int j=1;j<=N;j++)//������Ϊ�����Ǵ���ߴ���������
        {//�Ҳ�ȷ������һ������������i�ǵ�һ��1~h��
         //����Ϊn�������й�ϵ����j�ǵڶ���1~n��дn~1Ҳδ�����ɣ���
            dp[i][j]=max(dp[i][j],dp[i-1][j]);//һ������������һ��
            if(i>D)//������Ի��������ǻ��Ŀ�����
            dp[i][j]=max(dp[i][j],maxx[i-D]);
            dp[i][j]+=maap[i][j];//��������λ�õ����ӣ�
            maxx[i]=max(maxx[i],dp[i][j]);
            //�����һ�߶Ƚ��������Ե�������
        }
    for(int j=1;j<=N;j++)ans=max(ans,dp[H][j]);
    printf("%d",ans);
    return 0;
}
