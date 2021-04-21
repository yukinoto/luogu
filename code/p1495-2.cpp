#include <stdio.h>

template<typename T>
T read()
{
	T ans=0;
	char x=getchar();
	while(x<'0'||x>'9')
		x=getchar();
	while(x>='0'&&x<='9')
	{
		ans=ans*10+(x-'0');
		x=getchar();
	}
	return ans;
}

template<typename T>
void read(T &ans)
{
	ans=0;
	char x=getchar();
	while(x<'0'||x>'9')
		x=getchar();
	while(x>='0'&&x<='9')
	{
		ans=ans*10+(x-'0');
		x=getchar();
	}
	return;
}

template<typename T1,typename T2>
struct pair{
	T1 x;
	T2 y;
};
template<typename T1,typename T2>
inline pair<T1,T2> make_pair(T1 _x,T2 _y)
{
	pair<T1,T2> ans;
	ans.x=_x,ans.y=_y;
	return ans;
}

template <typename T>
pair<T,T> ExE(T a,T b,const T &d)
{
	if(b==0)
		return make_pair(a/d,b);
	pair<T,T> sol=ExE(b,a%b,d);
	return make_pair(sol.y,sol.x-a/b*sol.y);
}
template <typename T>
T eu(T a,T b)
{
	if(b==0)
		return a;
	return eu(b,a%b);
}
template <typename T>
pair<T,T> solu(T a,T b,const T &d)
{
	if(d%eu(a,b)!=0)
		return make_pair(0ll,0ll);
	return ExE(a,b,d);
}
template <typename T>
T anti(T x,T p)
{
	T ans=solu(x,p,1ll).x;
	return (ans%p+p)%p;
}

typedef long long Int;

int main()
{
	Int n=read<Int>();
	Int p[15],a[15],s=1,ans=0;
	for(int i=0;i<n;i++)
		read<Int>(p[i]),read<Int>(a[i]);
	for(int i=0;i<n;i++)
		s*=p[i];
	for(int i=0;i<n;i++)
	{
		Int m=s/p[i];
		ans+=a[i]*m*anti(m,p[i]);
		ans=ans%s;
	}
	printf("%lld\n",ans);
	return 0;
}
