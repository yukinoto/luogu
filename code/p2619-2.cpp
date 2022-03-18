//fake!
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
using namespace std;

class bcj{
	private:
		int *a;
	public:
		bcj(int n)
		{
			a=new int[n+1];
			for(int i=0;i<=n;i++)
				a[i]=i;
			return;
		}
		virtual ~bcj(){delete[] a;}
		int fa(int x)
		{
			return a[x]==x?x:(a[x]=fa(a[x]));
		}
		bool ist(int x,int y)
		{
			return fa(x)==fa(y);
		}
		void merge(int x,int y)
		{
			if(!ist(x,y))
				a[fa(x)]=fa(y);
			return;
		}
		bcj& operator=(bcj&&x)
		{
			delete[] a;
			a=x.a;
			x.a=nullptr;
			return *this;
		}
};

class edge{
	public:
		int x,y,w;
		bool operator<(const edge&o)const{return w==o.w?(x==o.x?y<o.y:x<o.x):w<o.w;}
		bool operator>(const edge&o)const{return w==o.w?(x==o.x?y>o.y:x>o.x):w>o.w;}
		edge(int x,int y,int w){this->x=x,this->y=y;this->w=w;}
};

int main()
{
	int n,m,need;
	cin>>n>>m>>need;
	bcj tr(n),tm(n);
	vector<edge> w,b;
	for(int i=0;i<m;i++)
	{
		int x,y,we,col;
		cin>>x>>y>>we>>col;
		if(col==0)
			w.emplace_back(x,y,we);
		else
		{
			b.emplace_back(x,y,we);
			tr.merge(x,y);
		}
	}
	int ans=0;
	priority_queue<edge,vector<edge>,greater<edge>> q;
	for(auto i:w) q.push(i);
	while(!q.empty())
	{
		if(!tr.ist(q.top().x,q.top().y))
		{
			tr.merge(q.top().x,q.top().y),tm.merge(q.top().x,q.top().y);
			ans+=q.top().w;
			need--;
		}
		q.pop();
	}
	if(need<0)
		throw -1;
	for(auto i:w) q.push(i);
	while(!q.empty())
	{
		if(!tm.ist(q.top().x,q.top().y))
		{
			tm.merge(q.top().x,q.top().y);
			ans+=q.top().w;
			need--;
		}
		if(need==0)
			break;
		q.pop();
	}
	while(!q.empty()) q.pop();
	for(auto i:b) q.push(i);
	while(!q.empty())
	{
		if(!tm.ist(q.top().x,q.top().y))
		{
			tm.merge(q.top().x,q.top().y);
			ans+=q.top().w;
		}
		q.pop();
	}
	cout<<ans<<endl;
	return 0;
}