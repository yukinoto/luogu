#include <stdio.h>

struct node{
    int value,ncnt;
    int lc,rc,ft;
};
node a[2000010];
int top;
int root,num;
void insert()
{
    int x;
    scanf("%d",&x);
    if(num==0)
    {
        num++;
        root=++top;
        a[root].ft=a[root].rc=a[root].lc=0;
        a[root].value=x;
        a[root].ncnt=1;
        return;
    }
    int p=root;
    bool flag=true;
    while(flag)
    {
        flag=false;
        if(x<a[p].value&&a[p].lc!=0)
        {
            p=a[p].lc;
            flag=true;
            continue;
        }
        if(x>=a[p].value&&a[p].rc!=0)
        {
            p=a[p].rc;
            flag=true;
            continue;
        }
    }
    num++;
    if(x<a[p].value&&a[p].lc==0)
    {
        a[p].lc=++top;
        a[top].lc=a[top].rc=0;
        a[top].ft=p;
        a[top].ncnt=1;
        a[top].value=x;
        while(p!=0)
        {
            a[p].ncnt++;
            p=a[p].ft;
        }
        return;
    }
    if(x>=a[p].value&&a[p].rc==0)
    {
        a[p].rc=++top;
        a[top].rc=a[top].lc=0;
        a[top].ft=p;
        a[top].ncnt=1;
        a[top].value=x;
        while(p!=0)
        {
            a[p].ncnt++;
            p=a[p].ft;
        }
        return;
    }
}
void swap(int x,int y)
{
    node tmp1=a[x];
    a[x]=a[y];
    a[y]=tmp1;
    int tmp2=a[x].value;
    a[x].value=a[y].value;
    a[y].value=tmp2;
}
void del()
{
    int x;
    scanf("%d",&x);
    int p=root;
    while(true)
    {
        while(a[p].value!=x)
        {
            if(x<a[p].value)
            {
                if(a[p].lc==0)
                    return;
                p=a[p].lc;
            }
            else
            {
                if(a[p].rc==0)
                    return;
                p=a[p].rc;
            }
        }
        while(a[p].lc!=0||a[p].rc!=0)
        {
            if(a[p].lc!=0)
                swap(p,a[p].lc);
            else
                swap(p,a[p].rc);
        }
        if(a[a[p].ft].lc==p)
            a[a[p].ft].lc=0;
        else
            a[a[p].ft].rc=0;
        p=a[p].ft;
        num--;
        while(p!=0)
        {
            a[p].ncnt--;
            p=a[p].ft;
        }
    }
}
void searchbef()
{
    int k;
    scanf("%d",&k);
    int p=root,cnt=a[a[p].lc].ncnt;
    while(cnt!=k-1)
        if(cnt<k-1)
        {
            cnt+=a[a[p].lc].ncnt+1;
            p=a[p].rc;
        }
        else
        {
            p=a[p].lc;
        	cnt-=a[a[p].rc].ncnt+1;
        }
    printf("%d\n",a[p].value);
    return;
}
void searchend()
{
    int k;
    scanf("%d",&k);
    int p=root,cnt=a[a[p].rc].ncnt;
    while(cnt!=k-1)
        if(cnt<k-1)
        {
            cnt+=a[a[p].rc].ncnt+1;
            p=a[p].lc;
        }
        else
        {
            p=a[p].rc;
        	cnt-=a[a[p].lc].ncnt+1;
        }
    printf("%d\n",a[p].value);
    return;
}
void prinnum()
{
    printf("%d\n",num);
    return;
}
void prin(int r)
{
    if(a[r].lc!=0)
        prin(a[r].lc);
    printf("%d ",a[r].value);
    if(a[r].rc!=0)
        prin(a[r].rc);
    return;
}

int main()
{
	freopen("4.in","r",stdin);
	//freopen("4.out","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int f;
        scanf("%d",&f);
        switch (f)
        {
            case 1:
                insert();
            break;
            case 2:
                del();
            break;
            case 3:
                searchend();
            break;
            case 4:
                searchbef();
            break;
            case 5:
                prinnum();
            break;
        default:
            break;
        }
    }
    prin(root);
    printf("\n");
    return 0;
}
