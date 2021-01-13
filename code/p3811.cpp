//p3811
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
		return make_pair(0,0);
	return ExE(a,b,d);
}
int main()
{
	int n=read<int>(),p=read<int>();
	for(int i=1;i<=n;i++)
	{
		static pair<int,int> ans;
		ans=solu(i,p,1);
		printf("%d\n",(ans.x%p+p)%p);
	}
	return 0;
}
