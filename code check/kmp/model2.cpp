//kmp model-p3375-accepted
#include <stdio.h>
#include <string.h>

char s1[1000010],s2[1000010];
int kmpstp[1000010];
int main()
{
    scanf("%s%s",s1,s2);
    kmpstp[0]=kmpstp[1]=0;
    const int len1=strlen(s1),len2=strlen(s2);
    for(int i=1;i<len2;i++)
    {
        int j=kmpstp[i];
        while(j!=0&&s2[j]!=s2[i])
            j=kmpstp[j];
        if(s2[i]==s2[j])
            kmpstp[i+1]=j+1;
    }
    int j=0;
    for(int i=0;i<len1;i++)
    {
        while(j!=0&&s2[j]!=s1[i])
            j=kmpstp[j];
        if(s1[i]==s2[j])
            j++;
        if(j==len2)
            printf("%d\n",i-j+2);
    }
    for(int i=1;i<len2;i++)
        printf("%d ",kmpstp[i]);
    printf("%d\n",kmpstp[len2]);
    return 0;
}
