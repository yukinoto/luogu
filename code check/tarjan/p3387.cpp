//p3387-ac
#include <stdio.h>
#include <algorithm>

class stack
{
    private:
        int num[10010];
        int _top;
        bool instack[10010];
    public:
        void push(int x)
        {
            num[_top++]=x;
            instack[x]=true;
            return;
        }
        void pop()
        {
            _top--;
            instack[num[_top]]=false;
            return;
        }
        inline bool empty()
        {
            return _top==0;
        }
        bool exsist(int x)
        {
            return instack[x];
        }
        int top()
        {
            if(empty())
                return -1;
            return num[_top-1];
        }
        void clear()
        {
            while(!empty())
                pop();
            return;
        }
};
stack inst;

int n,m;
bool map[10010][10010];
int value[10010];

void fre()
{
    freopen("p3387.in","r",stdin);
    freopen("p3387.out","w",stdout);
    return;
}
void init()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&value[i]);
    for(int i=1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        map[x][y]=true;
    }
    return;
}

int time_icon=0;
int dfn[10010],low[10010];
int set[10010],top;
void tarjan(int root)
{
    for(int i=1;i<=n;i++)
        if(map[root][i])
        {
            if(!inst.exsist(i)&&dfn[i]==0)
            {
                dfn[i]=low[i]=++time_icon;
                inst.push(i);
                tarjan(i);
                low[root]=std::min(low[root],low[i]);
            }
            if(inst.exsist(i))
            {
                low[root]=std::min(low[root],dfn[i]);
            }
        }
    if(dfn[root]==low[root])
    {
        int p=inst.top();
        if(p==-1)
        	return;
        inst.pop();
        top++;
        while(p!=root)
        {
            set[p]=top;
            p=inst.top();
            inst.pop();
        }
        set[p]=top;
    }
    return;
}

bool m2[10010][10010];
int v2[10010];
void mk()
{
    for(int i=1;i<=n;i++)
    {
        v2[set[i]]+=value[i];
        for(int j=1;j<=n;j++)
            m2[set[i]][set[j]]=map[i][j]||m2[set[i]][set[j]];
    }
    return;
}

int f[10010];
int search(int root)
{
    if(f[root]!=0)
        return f[root];
    f[root]=v2[root];
    for(int i=1;i<=top;i++)
        if(i!=root&&m2[root][i])
            f[root]=std::max(f[root],search(i)+v2[root]);
    return f[root];
}

int main()
{
    //fre();
    init();
    for(int i=1;i<=n;i++)
        if(dfn[i]==0)
        {
            if(!inst.empty())
                return -1;
            dfn[i]=low[i]=++time_icon;
            inst.push(i);
            tarjan(i);
        }
    mk();
    int ans=0;
    for(int i=1;i<=top;i++)
        ans=std::max(ans,search(i));
    printf("%d",ans);
    return 0;
}
