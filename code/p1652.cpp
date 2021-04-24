#include <iostream>
using namespace std;

class node{
	public:
		int x,y;
		int operator - (const node &o)const
		{
			return (x-o.x)*(x-o.x)+(y-o.y)*(y-o.y);
		}
};
class cir{
	public:
		node o;
		int r;
		bool in(const node &x)const
		{
			return x-o<r*r;
		}
};

int n;
cir c[60];
node a,b;

void init()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>c[i].o.x;
	for(int i=0;i<n;i++)
		cin>>c[i].o.y;
	for(int i=0;i<n;i++)
		cin>>c[i].r;
	cin>>a.x>>a.y>>b.x>>b.y;
	return;
}

void work()
{
	int ans=0;
	for(int i=0;i<n;i++)
		if(c[i].in(a)&&!c[i].in(b)||!c[i].in(a)&&c[i].in(b))
			ans++;
	cout<<ans<<endl;
	return;
}

int main()
{
	init();
	work();
	return 0;
}