#include <iostream>
#include <vector>
#include <cstring>
#include <functional>
#include <map>
#include <algorithm>
using namespace std;

template<typename Int>
class xds{
	private:
		class node{
			public:
				node *lc,*rc;
				Int value,tag;
				virtual ~node(){delete lc,delete rc;}
				node(){lc=rc=nullptr;}
				node(const Int&value){lc=rc=nullptr;this->value=value;tag=0;}
		};
		node *root;
		size_t ln,rn;
		xds(){;}
		template<typename op>
		static node* build(size_t left,size_t right,const op &f)
		{
			if(right==left+1)
				return new node(f(left));
			size_t mid=(left+right)/2;
			node *pt=new node;
			pt->lc=build<op>(left,mid,f),pt->rc=build<op>(mid,right,f);
			pt->tag=0,pt->value=pt->lc->value+pt->rc->value;
			return pt;
		}
		static node* build(size_t left,size_t right,Int *a)
		{
			if(right==left+1)
				return new node(a[left]);
			size_t mid=(left+right)/2;
			node *pt=new node;
			pt->lc=build(left,mid,a),pt->rc=build(mid,right,a);
			pt->tag=0,pt->value=pt->lc->value+pt->rc->value;
			return pt;
		}
		static void pushtag(size_t left,size_t right,node *pt)
		{
			if(pt->lc==nullptr)
				return;
			size_t mid=(left+right)/2;
			pt->lc->tag+=pt->tag,pt->rc->tag+=pt->tag;
			pt->lc->value+=pt->tag*(mid-left),pt->rc->value+=pt->tag*(right-mid);
			pt->tag=0;
			return;
		}
		static void add(size_t left,size_t right,size_t l,size_t r,Int x,node* pt)
		{
			if(l<=left&&r>=right)
			{
				pt->value+=(right-left)*x;
				pt->tag+=x;
				return;
			}
			if(l>=right||r<=left)
				return;
			pushtag(left,right,pt);
			size_t mid=(left+right)/2;
			add(left,mid,l,r,x,pt->lc),add(mid,right,l,r,x,pt->rc);
			pt->value=pt->lc->value+pt->rc->value;
			return;
		}
		static Int quest(size_t left,size_t right,size_t l,size_t r,node* pt)
		{
			if(l<=left&&r>=right)
				return pt->value;
			if(l>=right||r<=left)
				return 0;
			pushtag(left,right,pt);
			size_t mid=(left+right)/2;
			return quest(left,mid,l,r,pt->lc)+quest(mid,right,l,r,pt->rc);
		}
	public:
		template<typename op>
		xds(size_t left,size_t right,const op &f)
		{
			ln=left,rn=right;
			root=build<op>(left,right,f);
			return;
		}
		xds(size_t left,size_t right)
		{
			ln=left,rn=right;
			root=build(left,right,function([](size_t x){return 0;}));
			return;
		}
		xds(size_t left,size_t right,Int *a)
		{
			ln=left,rn=right;
			root=build(left,right,a);
			return;
		}
		void add(size_t l,size_t r,Int x)
		{
			add(ln,rn,l,r,x,root);
		}
		Int quest(size_t l,size_t r)
		{
			return quest(ln,rn,l,r,root);
		}
};

class tree{
	private:
		class node{
			public:
				int siz,rnk,dep;
				node *top;
				node *fa;
				vector<node*>sons;
				virtual ~node()
				{
					for_each(sons.begin(),sons.end(),function([](node* f){delete f;}));
					return;
				}
		};
		xds<int> *trs;
		node *root;
		map<int,node*>mp;
		node* build(vector<pair<int,int>>*lik,int n,int nw,bool *tkn)
		{
			node* pt=new node;
			pt->siz=1;
			mp.insert(make_pair(nw,pt));
			for(auto i:lik[nw])
			{
				if(!tkn[i.first])
				{
					tkn[i.first]=true;
					node* ss=build(lik,n,i.first,tkn);
					pt->sons.push_back(ss);
					ss->rnk=i.second;
					pt->siz+=ss->siz;
					ss->fa=pt;
				}
			}
			return pt;
		}
		int cnt;
		void dfs(node* rt,node *top)
		{
			rt->dep=rt->fa->dep+1;
			rt->top=top;
			trs->add(cnt,cnt+1,rt->rnk);
			rt->rnk=cnt++;
			if(rt->sons.empty())
				return;
			auto it=rt->sons.begin();
			for(auto i=it+1;i!=rt->sons.end();++i)
			{
				if((*i)->siz>(*it)->siz)
					it=i;
			}
			auto cache=*it;
			rt->sons.erase(it);
			rt->sons.push_back(cache);
			auto j=rt->sons.rbegin();
			dfs(*j,top);
			for(++j;j!=rt->sons.rend();++j)
				dfs(*j,*j);
			return;
		}
	public:
		tree(vector<pair<int,int>>*lik,int n)
		{
			cnt=0;
			trs=new xds<int>(0,n+1);
			bool *tkn=new bool[n+1];
			memset(tkn,false,sizeof(bool)*(n+1));
			root=build(lik,n,1,tkn);
			root->rnk=0,root->fa=root->top=root,root->dep=-1;
			delete[] tkn;
			dfs(root,root);
		}
		int quest(int x,int y)
		{
			node *px=mp[x],*py=mp[y];
			int ans=0;
			while(px->top!=py->top)
			{
				if(px->top->dep<py->top->dep)
					swap(px,py);
				ans+=trs->quest(px->top->rnk+1,px->rnk+1);
				px=px->top->fa;
			}
			if(px->dep<py->dep)
				swap(px,py);
			ans+=trs->quest(py->rnk+1,px->rnk+1);
			return ans;
		}
		void add(int x,int y,int value)
		{
			node *px=mp[x],*py=mp[y];
			while(px->top!=py->top)
			{
				if(px->top->dep<py->top->dep)
					swap(px,py);
				trs->add(px->top->rnk+1,px->rnk+1,value);
				px=px->top->fa;
			}
			if(px->dep<py->dep)
				swap(px,py);
			trs->add(py->rnk+1,px->rnk+1,value);
			return;
		}
		friend pair<int,int> fnd_edge(vector<pair<int,int>>*lik,int n,tree& tr);
};

pair<int,int> fnd_edge(vector<pair<int,int>>*lik,int n,tree& tr)
{
	for(int i=1;i<=n;i++)
		for(auto j:lik[i])
			if(tr.mp[i]->fa!=tr.mp[j.first]&&tr.mp[j.first]->fa!=tr.mp[i])
				return make_pair(i,j.first);
	throw -1;
}

int n,m;
vector<pair<int,int>> lik[100007];

int main()
{
	cin>>n>>m;
	map<int,pair<int,int>>edges;
	for(int i=0;i<n;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		edges.insert(make_pair(i+1,make_pair(x,y)));
		lik[x].emplace_back(y,z);
		lik[y].emplace_back(x,z);
	}
	tree tr(lik,n);
	auto edge=fnd_edge(lik,n,tr);
	int edgl=lower_bound(lik[edge.first].begin(),lik[edge.first].end(),make_pair(edge.second,-114514))->second;
	for(int i=0;i<m;i++)
	{
		int op,x,y;
		cin>>op>>x>>y;
		if(op==1)
		{
			if(edges[x]==edge)
			{
				edgl=y;
			}
			else
			{
				int cache=tr.quest(edges[x].first,edges[x].second);
				tr.add(edges[x].first,edges[x].second,y-cache);
			}
		}
		if(op==2)
		{
			int ans=tr.quest(x,y);
			ans=max(ans,tr.quest(x,edge.first)+edgl+tr.quest(edge.second,y));
			ans=max(ans,tr.quest(x,edge.second)+edgl+tr.quest(edge.first,y));
			cout<<ans<<'\n';
		}
	}
	return 0;
}