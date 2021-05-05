#include <cstdio>

long long n,k,p;
long long a[5000010],s[5000010],at[5000010];

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

long long ExE(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	long long as=ExE(b,a%b,y,x);
	y-=a/b*x;
	return as;
}

int main()
{
	read(n),read(p),read(k);
	read(a[0]);
	s[0]=a[0];
	for(int i=1;i<n;i++)
	{
		read(a[i]);
		s[i]=s[i-1]*a[i]%p;
	}
	ExE(s[n-1],p,at[n-1],at[n-2]);
	at[n-1]=(at[n-1]%p+p)%p;
	for(int i=n-2;i>=0;i--)
		at[i]=a[i+1]*at[i+1]%p;
	long long ans=k*at[0]%p,m=k*k%p;
	for(int i=1;i<n;i++)
	{
		ans+=m*at[i]%p*s[i-1]%p;
		ans%=p;
		m=m*k%p;
	}
	printf("%lld\n",ans%p);
	return 0;
}
