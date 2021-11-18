#include <cstdio>
#include <cctype>
#include <set>
using namespace std;

int line;

char gc()
{
	char ans=getchar();
	while(isspace(ans))
		ans=getchar();
	return ans;
}

int gp()
{
	char c=gc();
	if(c=='n')
		return -1;
	int ans=0;
	while(isdigit(c))
	{
		ans=ans*10+c-'0';
		c=getchar();
	}
	return ans;
}

set<char>st;

int getl()
{
	char i=gc();
	if(!st.insert(i).second)
		return -1;
	st.erase(i);
	int r=gp(),t=gp(),s=0;
	while(true)
	{
		char c=gc();
		line--;
		if(c=='F')
		{
			int tmp=getl();
			if(tmp==-1)
				return -1;
			s=max(s,tmp);
		}
		if(c=='E')
		{
			if(r==-1)
				return 0;
			if(t==-1)
				return s+1;
			if(t>r)
				return s;
			else
				return 0;
		}
	}
	return -1;
}

void work()
{
	int w;
	scanf("%d",&line);
	gc(),gc();
	if(gp()!=-1)
		w=0;
	else
	{
		gc();
		scanf("%d",&w);
		gc();
	}
	if(gc()!='F')
	{
		printf("ERR\n");
		return;
	}
	line--;
	int tmp=getl();
	if(tmp==-1)
		printf("ERR\n");
	while(line>0)
	{
		if(gc()!='F')
		{
			printf("ERR\n");
			return;
		}
		line--;
		int sp=getl();
		if(sp==-1)
		{
			printf("ERR\n");
			return;
		}
		tmp=max(tmp,sp);
	}
	if(tmp==w)
		printf("Yes\n");
	else
		printf("No\n");
	return;
}

int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
		work();
	return 0;
}