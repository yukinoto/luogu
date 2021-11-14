#include <iostream>
#include <utility>
using namespace std;

pair<int,int> p[500000];
char f[500000];
int v1[500000],v2[500000];

int main()
{
	ios::sync_with_stdio(false);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>p[i].first>>p[i].second;
	int dx=0,dy=0,tx=1,ty=1;
	for(int i=m-1;i>=0;i--)
	{
		cin>>f[i];
		if(f[i]=='m')
			cin>>v1[i]>>v2[i];
	}
	for(int i=0;i<m;i++)
	{
		if(f[i]=='m')
		{
			dx+=v1[i],dy+=v2[i];
		}
		if(f[i]=='x')
		{
			dx=-dx;
			tx=-tx;
		}
		if(f[i]=='y')
		{
			dy=-dy;
			ty=-ty;
		}
	}
	for(int i=0;i<n;i++)
		cout<<p[i].first*tx+dx<<' '<<p[i].second*ty+dy<<endl;
	return 0;
}