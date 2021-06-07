#include <stdio.h>

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
		return make_pair<T>(a/d,b);
	pair<T,T> sol=ExE(b,a%b,d);
	return make_pair<T>(sol.y,sol.x-a/b*sol.y);
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
		return make_pair<T>((T)0,(T)0);
	return ExE(a,b,d);
}
template <typename T>
T anti(T a,T p)
{
	return (solu<T>(a,p,1).x%p+p)%p;
}
int main()
{
	long long n,p;
	scanf("%lld%lld",&n,&p);
	printf("%lld\n",anti(n,p));
	return 0;
}
