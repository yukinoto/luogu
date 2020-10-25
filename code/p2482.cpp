#include <stdio.h>
#include <stdlib.h>

//situation of the game
int num;//num of pigs
int cardnum;//num of cards
int ptype[12];//type of pigs        ZP=0,FP=1
int chr[12];//character of pigs  
int pblood[12];//blood of pigs
bool wea[12];//if a pig is armed
char card_of_pigs[12][2010];//card of pigs
int card_num[12];//number of cards which a pig has;
char cardpool[2010];//card pool
int top_of_pool;
bool fp_view[12];//good==false   bad==true

//situation of this row
int knum;//times k has been put


//ftype
int fcd(int,char);
int cdr(int,int);
void dlcd(int,int);
void bls(int,int);
bool cj(int);
bool p(int);
bool k(int,int);
bool ck(int,int);
bool f(int,int);
bool d(int,int);
bool n(int);
bool w(int);
bool j(int,int);
void get_card(int,int);
bool try_card(int,int);
void dead(int,int);
void pigact(int);
void inpt();
void print();


//functions
//find card
int fcd(int p,char x)
{
    for(int i=1;i<=card_num[p];++i)
        if(card_of_pigs[p][i]==x)
            return i;
    return 0;
}
//check dir
int cdr(int a,int b)
{
    if(a==b)
        return 0;
    int step=0;
    for(int i=a;i<=b+num;i++)
    {
        if(pblood[i%num+1]!=0)
            step++;
        if(i%num+1==b)
            return step;
    }
    return step;
}
//del card
void dlcd(int p,int c)
{
    for(int i=c;i<card_num[p];i++)
        card_of_pigs[p][i]=card_of_pigs[p][i+1];
    card_num[p]--;
    printf("%d ",card_num[p]);
    //
    return;
}
//blood les
void bls(int p,int from)
{
    pblood[p]--;
    if(pblood[p]==0)
        dead(p,from);
    return;
}
bool cj(int pig)//check for j
{
    for(int i=pig-1;i<pig+num-2;i++)
        if(j(i,chr[pig]))
            return true;
    return false;
}

//cards
bool p(int from)//P
{
    if(pblood[from]==4)
        return false;
    int ans=fcd(from,'P');
    if(ans==0)
        return false;
    pblood[from]++;
    dlcd(from,ans);
    return true;
}
bool k(int from,int to)//K
{
    if(knum!=0&&!wea[from])
        return false;
    if(cdr(from,to)!=1)
        return false;
    int pt=fcd(from,'K');
    if(pt==0)
        return false;
    d(to,from);
    knum++;
    chr[from]=ptype[from];
    if(!((chr[from]+chr[to])%2==0||(chr[from]==1&&to==1)))
        printf("K:error\n");
    return true;
}
bool ck(int pig,int from)//check K
{
    int pt=fcd(pig,'K');
    if(pt==0)
    {
        bls(pig,from);
        return false;
    }
    dlcd(pig,pt);
    return true;
}
bool f(int from,int to)//F
{
    int pt=fcd(from,'F');
    if(pt==0)
        return false;
    if(cj(to))
        return true;
    if(ptype[from]==2&&ptype[to]==0)
    {
        bls(to,from);
        return true;
    }
    while(true)
    {
        if(!ck(to,from))
            return true;
        if(!ck(from,to))
            return true;
    }
}
bool d(int pig,int from)//D
{
    int pt=fcd(pig,'D');
    if(pt==0)
    {
        bls(pig,from);
        return false;
    }
    dlcd(pig,pt);
    return true;
}
bool n(int pig)//N
{
    int pt=fcd(pig,'N');
    if(pt==0)
        return false;
    for(int i=pig;i<pig+num-1;i++)
        if(!cj(i%num+1))
            if(ck(i%num+1,pig))
				if(i%num+1==1)
                	fp_view[pig]==true;
    dlcd(pig,pt);
    return true;
}
bool w(int pig)//W
{
    int pt=fcd(pig,'W');
    if(pt==0)
        return false;
    for(int i=pig;i<pig+num-1;i++)
        if(!cj(i))
            if(d(i%num+1,pig)&&i%num+1==1)
                fp_view[pig]=true;
    dlcd(pig,pt);
    return true;
}
bool j(int pig,int mark)//J mark represents to the pig put j;
{
    int pt=fcd(pig,'J');
    if(pt==0)
        return false;
    if(mark==-1)
        return false;
    if(ptype[pig]!=mark)
        return false;
    if(ptype[pig]==mark)
    {
        dlcd(pig,pt);
        chr[pig]=mark;
        for(int i=pig;i<pig+num-1;i++)
            if(j(i%num+1,!(mark+1)%2))
                return false;
        return true;
    }
}


//actions
void get_card(int pig,int num_c)
{
	for(int i=1;i<=num_c;i++)
		card_of_pigs[pig][++card_num[pig]]=cardpool[++top_of_pool];
    return;
}
bool try_card(int pig,int c)
{
    char x=card_of_pigs[pig][c];
    switch (x)
    {
        case 'P':
            return p(pig);
            break;
        case 'K':
            for(int i=pig;i<pig+num-1;i++)
                if((chr[i]!=-1&&chr[i]!=ptype[pig]&&ptype[pig]!=2)||(ptype[pig]==2&&(chr[i]==1||fp_view[i])))
                    if(k(pig,i))
                        return true;
            break;
        case 'F':
            if(ptype[pig]==1)
                return f(pig,1);
            for(int i=pig;i<pig+num-1;i++)
                if((chr[i]!=-1&&chr[i]!=ptype[pig]&&ptype[pig]!=2)||(ptype[pig]==2&&(chr[i]==1||fp_view[i])))
                    if(f(pig,i))
                        return true;
            break;
        case 'N':
            n(pig);
            return true;
            break;
        case 'W':
            w(pig);
            return true;
            break;
        case 'Z':
            dlcd(pig,1);
            wea[pig]=true;
            return true;
            break;
        default:
            return false;
    }
    return false;
}
void dead(int pig,int from)
{
	if(p(pig))
        return;
    card_num[pig]=0;
    if(ptype[pig]==1)
        get_card(from,3);
    if(ptype[pig]==0&&ptype[from]==2)
        card_num[from]=0;
    if(ptype[pig]==2)
    	print();
    int flag=true;
    for(int i=1;i<=num;i++)
    	if(pblood[i]>0&&ptype[i]==1)
    		flag=false;
    if(flag)
    	print();
    return;
}

//rows
void pigact(int pig)
{
    get_card(pig,2);
    bool flag=false;
    do
    {
    	flag=false;
        for(int i=1;i<=card_num[pig];i++)
            if(try_card(pig,i))
            {
                flag=true;
                break;
            }
    } while (flag);
}

//main
void inpt()
{
    scanf("%d%d",&num,&cardnum);
    for(int i=1;i<=num;i++)
    {
    	pblood[i]=4;
        getchar();
        char x=getchar();
        switch (x)
        {
            case 'M':
                ptype[i]=2;
                chr[i]=0;
                break;
          	case 'Z':
                ptype[i]=0;
                chr[i]=-1;
                break;
           default:
                ptype[i]=1;
                chr[i]=-1;
                break;
        }
        getchar();
        card_num[i]=4;
        for(int j=1;j<=4;j++)
        {
            getchar();
            x=getchar();
            card_of_pigs[i][j]=x;
        }
    }
    for(int i=1;i<=cardnum;i++)
    {
        getchar();
        char x=getchar();
        cardpool[i]=x;
    }
}
void print()
{
    if(pblood[1]!=0)
        printf("MP\n");
    else
        printf("FP\n");
    for(int i=1;i<=num;i++)
    {
        if(pblood[i]==0)
        {
            printf("DEAD\n");
            continue;
        }
        for(int j=1;j<card_num[i];j++)
            printf("%c ",card_of_pigs[i][j]);
        printf("%c\n",card_of_pigs[i][card_num[i]]);
    }
    exit(0);
    return;
}

int main()
{
    inpt();
    while(true)
    	for(int i=1;i<=num;i++)
    		pigact(i);
    return 0;
}
