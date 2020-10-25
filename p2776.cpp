//p2776
#include <stdio.h>

int pointer[310],head[310],tail[310],toph;
int bef[100010],nxt[100010],top;
int group[100010];
int main()
{
    int n,t;
    scanf("%d%*d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",group+i);
    scanf("%d\n",&t);
    for(int i=0;i<t;i++)
    {
        getchar();
        char x=getchar();
        if(x=='u')
        {
            int ele;
            scanf("sh %d\n",&ele);
            ele++;
            if(head[group[ele]]!=0)
            {
                int pt=group[ele];
                bef[++top]=tail[pt];
                nxt[tail[pt]]=top;
                tail[pt]=top;
                continue;
            }
            if(head[group[ele]]==0)
            {
                int pt=group[ele];
                pointer[++toph]=pt;
                head[pt]=++top;
                tail[pt]=top;
                continue;
            }
        }
        if(x=='o')
        {
            scanf("p\n");
            int j;
            for(j=1;pointer[j]==0;j++);
            int pt=pointer[j];
            printf("%d\n",head[pt]-1);
            head[pt]=nxt[head[pt]];
            if(head[pt]==0)
            pointer[j]=0;
        }
    }
    return 0;
}
