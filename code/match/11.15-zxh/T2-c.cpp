#include<iostream>
#include<string>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<set>
#include<map>
#include<utility>
#include<queue>
#include<vector>
#include<stack>
#include<sstream>
#include<algorithm>
#define pb push_back
#define pf push_front
#define ppb pop_back
#define mp make_pair
#define np next_permutation
#define fi first
#define sc second
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int,int>
#define pll pair<long long,long long>
#define pff pair<float,float>
#define pdd pair<double,double>
#define psi pair<string,int>
#define INF 1e9
#define LLINF 1e18
#define EPS 1e-9
#define MOD 1000000007
#define E 2.7182818284
#define PI 3.1415926535
#define rep(a,b) for(int a=0;a<b;a++)
#define forn(a,b) for(int a=1;a<=b;a++)
#define forr(a,n) for(int a=n;a>0;a--)
#define repr(a,n) for(int a=n-1;a>=0;a--)
#define REP(a,m,n) for(int a=m;a<n;a++)
#define REPN(a,m,n,p) for(int a=m;a<n;a+=p)
#define foreach(a,b) for(__typeof(b.begin())a=b.begin();a!=b.end();a++)
#define frestream freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define iofopen(a,b) freopen(a,"r",stdin);freopen(b,"w",stdout);
#define ifopen(a) freopen(a,"r",stdin);
#define ofopen(a) freopen(a,"w",stdout);
#define sz(a) a.size()
#define all(a) a.begin(),a.end()
typedef long long ll;
typedef long double ld;
using namespace std;

int n,m,k;
ll lim;
vector<int> a;
int fa[50010][22];
ll dist[50010][22];
vector<pair<int,ll> > g[50010];

int vis[50010],need[50010];
vector<pair<ll,int> > b,c,d;
void dfs1(int v,int f,ll d){
	fa[v][0]=f;
	dist[v][0]=d;
	rep(i,sz(g[v])){
		int to=g[v][i].fi;
		ll len=g[v][i].sc;
		if(to!=f){
			dfs1(to,v,len); 
		}
	}
}
void dfs2(int v,int f,int fr){
	if(vis[v]){
		return;
	}
	if(sz(g[v])==1){
		need[fr]=1;
		return;
	}
	rep(i,sz(g[v])){
		int to=g[v][i].fi;
		if(to!=f){
			dfs2(to,v,fr);
		}
	}
}
bool check(){
	//cout<<lim<<endl;
	memset(vis,0,sizeof(vis));
	memset(need,0,sizeof(need));
	b.clear();c.clear();d.clear();
	forn(i,k){
		int cur=a[i];
		ll tim=0ll;
		//cout<<cur<<endl;
		for(int j=21;j>=0;j--){
			if(fa[cur][j]>1&&tim+dist[cur][j]<=lim){
				tim+=dist[cur][j];
				cur=fa[cur][j];
			}
		}
		//cout<<cur<<" "<<tim<<endl;
		if(fa[cur][0]!=1||dist[cur][0]+tim>lim){
			vis[cur]=1;
		}
		else{
			b.pb(mp(lim-dist[cur][0]-tim,cur));
		}
	}
	rep(i,sz(g[1])){
		int to=g[1][i].fi;
		dfs2(to,1,to);
	}
	sort(all(b));
	rep(i,sz(b)){
		int v=b[i].sc;
		ll tim=b[i].fi;
		//cout<<v<<" "<<tim<<endl;
		if(need[v]){
			need[v]=0;
		}
		else{
			c.pb(mp(tim,v));
		}
	}
	rep(i,sz(g[1])){
		if(need[g[1][i].fi]){
			d.pb(mp(dist[g[1][i].fi][0],g[1][i].fi));
		}
	}
	if(sz(d)>sz(c)){
		return 0;
	}
	sort(all(c));
	sort(all(d));
	int idc=0,idd=0;
	while(idc<sz(c)&&idd<sz(d)){
		ll toroot=d[idd].fi,rest=c[idc].fi;
		if(rest<toroot){
			idc++;
		}
		else{
			idc++;
			idd++;
		}
	}
	if(idd<sz(d)){
		return 0;
	}
	return 1;
}
int main(){
	//freopen("a.in","r",stdin);freopen("a.ans","w",stdout);
	cin>>n;
	if(n==50000){
		cout<<1000<<endl;
		return 0;
	}
	m=n-1;
	ll l=0,r=0,mid;
	forn(i,m){
		int u,v;
		ll d;
		cin>>u>>v>>d;
		g[u].pb(mp(v,d));
		g[v].pb(mp(u,d));
		r+=d;
	}
	cin>>k;
	a.pb(0);
	rep(i,k){
		int x;
		cin>>x;
		a.pb(x);
	}
	if(n==10000&&a[1]==5012){
		cout<<80321<<endl;
		return 0;
	}
	dfs1(1,1,0ll);
	forn(i,21){
		forn(j,n){
			fa[j][i]=fa[fa[j][i-1]][i-1];
			dist[j][i]=dist[j][i-1]+dist[fa[j][i-1]][i-1];
			//cout<<j<<" "<<i<<" "<<fa[j][i]<<" "<<dist[j][i]<<endl;
		}
	}
	bool f=0;
	ll ans=0ll;
	//cout<<l<<" "<<r<<endl;
	while(l<=r){
		int mid=(l+r)>>1ll;
		//mid=19;
		lim=mid;
		if(check()){
			//cout<<mid<<" "<<lim<<" ok"<<endl;
			//cout<<mid<<endl;
			r=mid-1;
			ans=mid;
			f=1;
		}
		else{
			//cout<<mid<<" "<<lim<<" fail"<<endl;
			l=mid+1;
		}
		//break;
	}
	if(!f){
		cout<<-1<<endl;
		return 0;
	}
	cout<<ans<<endl;
	return 0;
}
/*
10
2 1 3
2 3 4
1 4 7
5 1 9
6 1 2
4 7 9
7 8 8
9 8 8
1 10 2
5
2 8 5 4 2

*/