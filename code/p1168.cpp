#include <stdio.h>
#include <queue>
using namespace std;

class md{
	private:
		priority_queue<int> down;
		priority_queue<int,vector<int>,greater<int> > up;
		inline void check()
		{
			if(down.empty()||up.empty())
				return;
			if(down.top()>up.top())
			{
				int a=down.top(),b=up.top();
				down.pop(),up.pop();
				up.push(a),down.push(b);
			}
			return;
		}
	public:
		void add(int x)
		{
			if(up.size()>down.size())
				down.push(x);
			else
				up.push(x);
			check();
			return;
		}
		void printMid()
		{
			if(!up.empty())
				printf("%d\n",up.top());
			return;
		}
};

int main()
{
	md *a=new md;
	int n;
	scanf("%d",&n);
	for(register int i=0;i<n;i++)
	{
		static int x;
		scanf("%d",&x);
		a->add(x);
		if((i&1)==0)
			a->printMid();
	}
	return 0;
}
