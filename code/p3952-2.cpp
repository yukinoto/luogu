#include <iostream>
#include <set>
using namespace std;

int line;

char cache[50];
set<char> st;

int getx()
{
	char c;
	cin>>c;
	if(c=='n')
		return -1;
	int ans=0;
	while(isdigit(c))
	{
		ans=ans*10+c-'0';
		c=cin.get();
	}
	return ans;
}

#define QUIT {cin.getline(cache,50);return -1;}
int loop()
{
	char c;
	line--;
	cin>>c;
	if(c!='F')
		QUIT
	char i;
	cin>>i;
	if(!st.insert(i).second)
		QUIT
	int r=getx(),d=getx(),s=0;
	while(line>0)
	{
		cin>>c;
		if(c=='F')
		{
			cin.putback(c);
			int tmp=loop();
			if(tmp==-1)
				return -1;
			else
				s=max(s,tmp);
		}
		else
		{
			line--;
			if(c=='E')
			{
				st.erase(i);
				if(r==d)
					return s;
				if(r==-1)
					return 0;
				if(d==-1)
					return s+1;
				if(r>d)
					return 0;
				return s;
			}
			else
				QUIT
		}
	}
	return -1;
}
#undef QUIT

void work()
{
	st.clear();
	int w;
	scanf("%d",&line);
	char c;
	cin>>c>>c>>c;
	if(c=='n')
	{
		cin>>c;
		cin>>w>>c;
	}
	else
		if(c=='1')
		{
			w=0;
			cin>>c;
		}
		else
		{
			cout<<"ERR"<<endl;
			while(line>0)
			{
				line--;
				cin.getline(cache,50);
			}
			return;
		}
	int s=0;
	while(line>0)
	{
		int tmp=loop();
		if(tmp==-1)
		{
			cout<<"ERR"<<endl;
			while(line>0)
			{
				line--;
				cin.getline(cache,50);
			}
			return;
		}
		else
		{
			s=max(s,tmp);
		}
	}
	if(s==w)
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl;
	return;
}

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++)
		work();
	return 0;
}