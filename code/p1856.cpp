#include <stdio.h>
#include <algorithm>
#include <utility>
using namespace std;

class line{
	public:
		int x1,x2,y;
		int type;
		line(){}
		bool operator<(const line&x)
		{
			return y<x.y;
		}
		line(int _x1,int _x2,int _y,int _type)
		{
			x1=_x1,x2=_x2,y=_y,type=_type;
		}
};
class squ{
	public:
		int x1,x2,y1,y2;
		void get()
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		}
};
pair<line,line> gen1(const squ &x)
{
	return make_pair(line(x.x1,x.x2,x.y1,1),line(x.x1,x.x2,x.y2,-1));
}
pair<line,line> gen2(const squ &x)
{
	return make_pair(line(x.y1,x.y2,x.x1,1),line(x.y1,x.y2,x.x2,-1));
}

int main()
{
	int n;
	scanf("%d",&n);
	squ *pt=new squ[n];
	for(int i=0;i<n;i++)
		pt->get();
	auto f=[&](decltype(gen1) gen)->void
	{
		line *x=new line[n<<1];
		for(int i=0;i<n;i++)
		{
			auto ct=gen(pt[i]);
			x[i<<1]=ct.first,x[(i<<1)^1]=ct.second;
		}
		sort(x,x+(n<<1));
		
	};
}