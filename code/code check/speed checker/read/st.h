#include <stdio.h>

int read_int()
{
    int x=0;
    char ipt=getchar();
    while((ipt<'0'||ipt>'9')&&(ipt!='+'&&ipt!='-'))
        ipt=getchar();
    if(ipt=='-')
    {
        ipt=getchar();
        if(ipt<'0'||ipt>'9')
            return 0;
        x=-(ipt-'0');
    }
    if(ipt=='+')
        ipt=getchar();
    while(ipt>='0'&&ipt<='9')
    {
        x*=10;
        x+=ipt-'0';
        ipt=getchar();
    }
    return x;
}
