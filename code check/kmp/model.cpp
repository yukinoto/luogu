//kmp model_wrong
#include <stdio.h>
#include <string.h>

char s1[1000010],s2[1000010];
int kmpstp[1000010];
int main()
{
    scanf("%[^\n]%[^\n]",s1,s2);
    {
        const int len=strlen(s2);
        for(int i=0;i<len;i++)
            for(int j=0;j<i;j++)
                if(s2[j]==s2[i-j])
                    kmpstp[i]++;
                else
                    break;
    }
    {
        const int len1=strlen(s1),len2=strlen(s2);
        int j=0;
        for(int i=0;i<=len1;i++)
        {
            if(j==len2)
                printf("%d\n",i-j+1);
            if(s1[i]==s2[j])
                j++;
            else
                j=kmpstp[j];
        }
    }
    for(int i=0;i<strlen(s2)-1;i++)
        printf("%d ",kmpstp[i]);
    printf("%d\n",kmpstp[strlen(s2)-1]);
    return 0;
}