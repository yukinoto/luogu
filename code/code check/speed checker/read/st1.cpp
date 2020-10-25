#include <stdio.h>

void read_int(int &x)
{
	x=0;
    char ipt=getchar();
    while((ipt<'0'||ipt>'9')&&(ipt!='+'&&ipt!='-'))
        ipt=getchar();
    if(ipt=='-')
    {
        ipt=getchar();
        if(ipt<'0'||ipt>'9')
            return;
        x=-(ipt-'0');
    }
    if(ipt=='+')
        ipt=getchar();
    while(ipt>='0'&&ipt<='9')
    {
        x=x*10+ipt-'0';
        ipt=getchar();
    }
    return;
}
int read(){
    int x=0,f=1;
    char ch=getchar();//getchar()读入单个字符（包括空格 ，换行符）
    while(ch<'0'||ch>'9'){//非数字（字符）
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);//原二进制数向左平移x位，右边原位置以0补齐(位运算）
        ch=getchar();
    }
    return x*f;
}

int main()
{
	freopen("st.in","r",stdin);
	int n=read();
	int x;
	for(int i=0;i<n;i++)
		x=read();
	return 0;
}
