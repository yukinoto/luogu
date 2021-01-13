//wa
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
		return make_pair((T)0,(T)0);
	return ExE(a,b,d);
}
template <typename T>
inline T anti(const T &x,const T &mod)
{
	return solu<T>(x,mod,1).x;
}

template <typename T>
T chinese_cy(T *c,T *m,const int &n)
{
	T S=1,ans=0;
	for(int i=0;i<n;i++)
		S*=m[i];
	for(int i=0;i<n;i++)
	{
		ans+=c[i]*anti(S/m[i]%m[i],m[i])*m[i];
		ans%=S;
	}
	return (ans+S)%S;
}

int main()
{
	int n;
	scanf("%d",&n);
	long long *c=new long long[n],*m=new long long[n];
	for(int i=0;i<n;i++)
	{
		scanf("%lld%lld",m+i,c+i);
		c[i]%=m[i];
	}
	printf("%lld\n",chinese_cy(c,m,n));
	return 0;
}
