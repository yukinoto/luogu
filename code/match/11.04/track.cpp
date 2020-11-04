#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int n,m;
struct node{
	int value,father[17];
	vector<int> son;
	/*
	value表示从根起边权的前缀和
	father[i]表示向上第2^i个祖先
	son表示子节点的位置
	*/
};
node crs[50010];//存节点及信息
struct edge{
	int x,y,v;
};
edge a[50010];//临时数组，存边
bool cmp(edge,edge);
inline vector<int>::iterator add1(vector<int>::iterator x)//x+1
{
	x++;
	return x;
}
void init();//输入，建树
void makt(int,int,int);
//处理root为根的子树的value、father[0]、son
//v表示从根到root的边权和，f表示父节点位置
int father(int,int);//root节点的2^x祖先的位置
int skip(int,int);//root节点的x祖先的位置
int lca(int,int);//两个节点的lca的位置
int longestEdge(int);//以root为根的子树的最长边的长度
int longestWay(int);//以root为根的子树的最长路径的长度
int leftLenth(int,int);//以root为根，尽可能找到不短于lenth的路径后root向下的最长链
int maxWays(int,int);//以root为根，不短于lenth的路径数
int findAns(int,int);//在[left,right)内寻找答案

int main()
{
	init();
	printf("%d\n",findAns(1,longestWay(1)));
	return 0;
}
bool cmp(edge x,edge y)
{
	return x.x<y.x;
}
void init()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n-1;i++)
	{
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].v);
		if(a[i].x>a[i].y)
			swap(a[i].x,a[i].y);
	}
	sort(a,a+n-1,cmp);
	makt(a[0].x,0,-1);
}
void makt(int root,int v,int f)
{
	crs[root].father[0]=f;
	crs[root].value=v;
	edge tmp;
	tmp.x=root;
	edge *p=lower_bound(a,a+n-1,tmp,cmp);
	while(p->x==root)
	{
		crs[root].son.push_back(p->y);
		makt(p->y,v+p->v,root);
		p++;
	}
	return;
}
int father(int root,int x)
{
	if(crs[root].father[x]!=0)
		return crs[root].father[x];
	int p=father(root,x-1);
	if(x==-1)
		return crs[root].father[x]=-1;
	return crs[root].father[x]=father(p,x-1);
}
int longestEdge(int root)
{
	if(crs[root].son.empty())
		return 0;
	int ans=0;
	for(vector<int>::iterator it=crs[root].son.begin();it!=crs[root].son.end();it++)
		ans=max(ans,crs[*it].value-crs[root].value+longestEdge(*it));
	return ans;
}
int longestWay(int root)
{
	if(crs[root].son.empty())
		return 0;
	int ans=0;
	for(vector<int>::iterator it=crs[root].son.begin();it!=crs[root].son.end();it++)
	{
		ans=max(ans,longestWay(*it));
		for(vector<int>::iterator j=add1(it);j!=crs[root].son.end();j++)
			ans=max(ans,longestEdge(*it)+longestEdge(*j)+crs[*it].value+crs[*j].value-crs[root].value*2);
	}
	return ans;
}
int leftLenth(int root,int lenth)
{
	if(crs[root].son.empty())
		return 0;
	if(longestWay(root)<lenth)
		return longestEdge(root);
	vector<int>lenSon;
	for(vector<int>::iterator it=crs[root].son.begin();it!=crs[root].son.end();it++)
		lenSon.push_back(leftLenth(*it,lenth));
	sort(lenSon.begin(),lenSon.end());
	vector<int>::iterator it=lenSon.end();
	it--;
	while(true)
	{
		bool flag=false;;
		for(vector<int>::iterator i=lenSon.begin();i!=lenSon.end();i++)
			if(*i+*it>=lenth)
			{
				*i=*it=-1;
				while(*it!=-1&&it!=lenSon.begin());
					it--;
					flag=true;
					break;
			}
		if(it==lenSon.begin())
			if(*it==-1)
				return 0;
			else
				return *it;
		if(!flag)
			break;
	}
	sort(lenSon.begin(),lenSon.end());
	it=lenSon.end();
	it--;
	for(;it!=lenSon.end();it--)
		if(*it!=-1)
			return *it;
		else
			break;
	return 0;
}
int maxWays(int root,int lenth)
{
	int ans=0;
	if(longestWay(root)<lenth)
		return 0;
	if(crs[root].son.empty())
		return 0;
	vector<int> lenSon;
	for(vector<int>::iterator it=crs[root].son.begin();it!=crs[root].son.end();it++)
	{
		ans+=maxWays(*it,lenth);
		lenSon.push_back(leftLenth(*it,lenth)+crs[*it].value-crs[root].value);
	}
	sort(lenSon.begin(),lenSon.end());
	vector<int>::iterator i=lenSon.begin(),j=lenSon.end();
	j--;
	while(i<j)
	{
		if(*i+*j>=lenth)
		{
			i++;j--;
			ans++;
		}
		else
			i++;
	}
	return ans;
}
int findAns(int left,int right)
{
	int mid=(left+right)/2;
	if(maxWays(1,mid)>=m)
		return findAns(mid,right);
	else
		return findAns(left,mid);
}
