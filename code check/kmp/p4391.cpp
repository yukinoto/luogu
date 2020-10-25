//p4391
#include <stdio.h>

int len;
char str[1000010];
int kmpnxt[1000010];
int main()
{
    scanf("%d%s",&len,str);
    kmpnxt[0]=kmpnxt[1]=0;
    for(int i=1;i<len;i++)
    {
        int j=kmpnxt[i];
        while(j!=0&&str[i]!=str[j])
            j=kmpnxt[j];
        if(str[i]==str[j])
            kmpnxt[i+1]=j+1;
    }
    printf("%d\n",len-kmpnxt[len]);
    return 0;
}
