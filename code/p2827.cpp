#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

long long fln(queue<long long>&len,queue<long long>&len1,queue<long long>&len2)
{
	long long ans;
	if(len.empty()&&len1.empty())
	{
		ans=len2.front();
		len2.pop();
		return ans;
	}
	if(len1.empty()&&len2.empty())
	{
		ans=len.front();
		len.pop();
		return ans;
	}
	if(len.empty()&&len2.empty())
	{
		ans=len1.front();
		len1.pop();
		return ans;
	}
	if(len.empty())
	{
		if(len1.front()>=len2.front())
		{
			ans=len1.front();
			len1.pop();
			return ans;
		}
		else
		{
			ans=len2.front();
			len2.pop();
			return ans;
		}
	}
	if(len1.empty())
	{
		if(len.front()>=len2.front())
		{
			ans=len.front();
			len.pop();
			return ans;
		}
		else
		{
			ans=len2.front();
			len2.pop();
			return ans;
		}
	}
	if(len2.empty())
	{
		if(len.front()>=len1.front())
		{
			ans=len.front();
			len.pop();
			return ans;
		}
		else
		{
			ans=len1.front();
			len1.pop();
			return ans;
		}
	}
	if(len.front()>=len1.front())
	{
		if(len.front()>=len2.front())
		{
			ans=len.front();
			len.pop();
			return ans;
		}
		else
		{
			ans=len2.front();
			len2.pop();
			return ans;
		}
	}
	else
	{
		if(len1.front()>=len2.front())
		{
			ans=len1.front();
			len1.pop();
			return ans;
		}
		else
		{
			ans=len2.front();
			len2.pop();
			return ans;
		}
	}
}

template<typename Int>
Int greate(Int x,Int y)
{
	return x>y;
}

int main()
{
	int n,m;
	int q,t;long long u,v;
	cin>>n>>m>>q>>u>>v>>t;
	//priority_queue<long long> len;
	queue<long long>len,len1,len2;
	long long *a=new long long[n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	sort(a,a+n,greate<long long>);
	for(int i=0;i<n;i++)
		len.push(a[i]);
	for(int i=1;i<=m;i++)
	{
		long long x=fln(len,len1,len2);
		x+=q*(i-1);
		len1.push(x*u/v-q*i),len2.push(x-x*u/v-q*i);
		if(i%t==0)
			cout<<x<<' ';
	}
	cout<<endl;
	for(int i=1;i<=n+m;i++)
	{
		long long ans=fln(len,len1,len2);
		if(i%t==0)
			cout<<ans+q*m<<' ';
	}
	cout<<endl;
	return 0;
}