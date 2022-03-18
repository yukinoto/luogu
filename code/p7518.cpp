//chain

#include <iostream>
#include <cstring>
using namespace std;

const int MAXN=200001,MAXC=50001;

int n,m,c;

int p[MAXC],ap[MAXC];
int w[MAXN];

//->
namespace a{
	int tmp[MAXC];
	int cls[MAXN];
	int fa[MAXN][16];
	void build(int root)
	{
		fa[root][0]=tmp[w[root]+1];
		tmp[w[root]]=root;
	}
	void init()
	{
		memset(fa,-1,sizeof(fa));
		int bef=-1;
		for(int i=n;i>=1;i--)
		{
			if(w[i]==1)
				bef=i;
			cls[i]=bef;
			build(i);
		}
	}
	int gf(int root,int b)
	{
		if(fa[root][b]==-1)
			return fa[root][b]=gf(gf(root,b-1),b-1);
		return fa[root][b];
	}
	int quest(int s,int t)
	{
		s=cls[s];
		if(s>t||s==-1)
			return 0;
		for(int i=15;i>=0;i--)
		{
			if(gf(s,i)!=0&&gf(s,i)<=t)
				s=gf(s,i);
		}
		return w[s];
	}
}

//<-
namespace b{
	int tmp[MAXC];
	int cls[MAXN];
	int fa[MAXN][16];
	void build(int root)
	{
		fa[root][0]=tmp[w[root]+1];
		tmp[w[root]]=root;
	}
	void init()
	{
		memset(fa,-1,sizeof(fa));
		int bef=-1;
		for(int i=1;i<=n;i++)
		{
			if(w[i]==1)
				bef=i;
			cls[i]=bef;
			build(i);
		}
	}
	int gf(int root,int b)
	{
		if(fa[root][b]==-1)
			return fa[root][b]=gf(gf(root,b-1),b-1);
		return fa[root][b];
	}
	int quest(int s,int t)
	{
		s=cls[s];
		if(s<t||s==-1)
			return 0;
		for(int i=15;i>=0;i--)
		{
			if(gf(s,i)!=0&&gf(s,i)>=t)
				s=gf(s,i);
		}
		return w[s];
	}
}

void init()
{
	cin>>n>>m>>c;
	for(int i=1;i<=c;i++)
	{
		cin>>p[i];
		ap[p[i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>w[i];
		w[i]=ap[w[i]];
	}
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
	}
	a::init(),b::init();
	return;
}

int main()
{
	init();
	int q;
	cin>>q;
	for(int i=0;i<q;i++)
	{
		int s,t;
		cin>>s>>t;
		if(s<=t)
			cout<<a::quest(s,t)<<endl;
		else
			cout<<b::quest(s,t)<<endl;;
	}
	return 0;
}