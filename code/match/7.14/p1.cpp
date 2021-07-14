#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class bd{
	public:
		int a[4];
		void init()
		{
			cin>>a[0]>>a[1]>>a[2]>>a[3];
			return;
		}
		int white()
		{
			int cnt=0;
			for(int i=0;i<4;i++)
				cnt+=int(a[i]==0);
			return cnt;
		}
		bool operator ==(const bd &x)const
		{
			for(int i=0;i<4;i++)
				if(a[i]!=x.a[i])
					return false;
			return true;
		}
};

void roll(vector<int> &x)
{
	x.push_back(x[0]);
	x.erase(x.begin());
	return;
}

bool check(bd x,bd y)
{
	vector<int>a,b;
	const int v[4]={0,2,3,1};
	for(int i=0;i<4;i++)
	{
		if(x.a[v[i]]!=0)
			a.push_back(x.a[v[i]]);
		if(y.a[v[i]]!=0)
			b.push_back(y.a[v[i]]);
	}
	for(int i=0;i<4;i++)
	{
		if(a==b)
			return true;
		roll(a);
	}
	return false;
}

int main()
{
	bd a,b;
	a.init(),b.init();
	if(a.white()==0)
		if(a==b)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	else if(a.white()>1)
		cout<<"Yes"<<endl;
	else if(check(a,b))
		cout<<"Yes"<<endl;
	else
		cout<<"No"<<endl;
	return 0;
}
