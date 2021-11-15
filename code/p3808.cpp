#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct node{
	node *fwd[26];
	node *fail;
	int cnt;
	bool fnd;
	node()
	{
		for(int i=0;i<26;++i)
			fwd[i]=nullptr;
		fail=nullptr;
		cnt=0;
		fnd=false;
	}
	~node()
	{
		for(int i=0;i<26;++i)
			delete fwd[i];
		return;
	}
};
node root;

void init()
{
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		string x;
		cin>>x;
		node *p=&root;
		for(auto c:x)
		{
			if(p->fwd[c-'a']==nullptr)
				p->fwd[c-'a']=new node;
			p=p->fwd[c-'a'];
		}
		p->cnt++;
	}
	queue<node*> q;
	root.fail=&root;
	q.push(&root);
	while(!q.empty())
	{
		node *p=q.front();q.pop();
		for(int i=0;i<26;i++)
		{
			if(p->fwd[i]!=nullptr&&p!=&root)
			{
				q.push(p->fwd[i]);
				auto nw=p->fwd[i],fd=p->fail;
				nw->fail=&root;
				do{
					if(fd->fwd[i]!=nullptr)
					{
						nw->fail=fd->fwd[i];
						//nw->cnt+=nw->fail->cnt;
						break;
					}
					else
						fd=fd->fail;
				}while(fd!=&root);
			}
			if(p==&root&&p->fwd[i]!=nullptr)
			{
				q.push(p->fwd[i]);
				p->fwd[i]->fail=&root;
			}
		}
	}
	return;
}

void work()
{
	string t;
	cin>>t;
	node *p=&root;
	int ans=0;
	for(auto c:t)
	{
		while(p!=&root&&p->fwd[c-'a']==nullptr)
		{
			p=p->fail;
		}
		if(p->fwd[c-'a']!=nullptr)
		{
			p=p->fwd[c-'a'];
			p->fnd=true;
		}
	}
	queue<node*> q;
	q.push(&root);
	while(!q.empty())
	{
		p=q.front();q.pop();
		for(int i=0;i<26;i++)
		{
			if(p->fwd[i]!=nullptr)
				q.push(p->fwd[i]);
			auto np=p;
			while(np!=&root&&np->fnd)
			{
				ans+=np->cnt;
				np->fnd=false;
				np=np->fail;
			}
		}
	}
	cout<<ans<<endl;
}

int main()
{
	init();
	work();
	return 0;
}