#include <iostream>
using namespace std;

class trie{
	private:
		class node{
			public:
				int cnt;
				node* sons[26];
				node()
				{
					cnt=0;
					for(int i=0;i<26;i++)
						sons[i]=nullptr;
				}
				int insert(const char*a)
				{
					if(a[0]=='\0')
						return cnt++;
					if(sons[a[0]-'a']==nullptr)
						sons[a[0]-'a']=new node;
					return sons[a[0]-'a']->insert(a+1);
				}
				int check(const char*a)
				{
					if(a[0]=='\0')
						return cnt;
					if(sons[a[0]-'a']==nullptr)
						return 0;
					return sons[a[0]-'a']->check(a+1);
				}
				~node()
				{
					for(int i=0;i<26;i++)
						delete sons[i];
					return;
				}
		};
		node root;
	public:
		int insert(const char*x)
		{
			return root.insert(x);
		}
		int check(const char*x)
		{
			return root.check(x);
		}
};

int main()
{
	trie t;
	int n;
	cin>>n;
	char cache[52];
	for(int i=0;i<n;i++)
	{
		cin>>cache;
		t.insert(cache);
	}
	int m;
	cin>>m;
	for(int i=0;i<m;i++)
	{
		cin>>cache;
		if(t.check(cache))
		{
			if(t.insert(cache)==1)
				cout<<"OK"<<endl;
			else
				cout<<"REPEAT"<<endl;
		}
		else
			cout<<"WRONG"<<endl;
	}
	return 0;
}