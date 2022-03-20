#include <iostream>
#include <string>
#include <stack>
using namespace std;

int a[1000001],b[1000001];
int ans;

void tof(int *s,int l,int r);//[]

void tod(int *s,int l,int r);//[]

void tod(int *s,int l,int r)
{
	if(l>=r-1)
		return;
	if(s[l]==r)
	{
		tod(s,l+1,r-1);
		return;
	}
	else
	{
		tof(s,l,r);
		ans++;
		while(r>l)
		{
			s[l]=r,s[r]=l;
			r--,l++;
		}
		return;
	}
}

void tof(int *s,int l,int r)
{
	if(l>=r-1)
		return;
	if(s[l]==r)
	{
		tod(s,l+1,r-1);
		ans++;
		for(int i=l;i<r;i+=2)
		{
			s[i]=i+1,s[i+1]=i;
		}
		return;
	}
	else
	{
		int tmp=s[l];
		tof(s,l,tmp),tof(s,tmp+1,r);
		return;
	}
}

void init(int *s)
{
	string tmp;
	cin>>tmp;
	int l=tmp.size();
	stack<int>st;
	for(int i=0;i<l;i++)
	{
		if(tmp[i]=='(')
			st.push(i);
		else
		{
			s[st.top()]=i;
			s[i]=st.top();
			st.pop();
		}
	}
	return;
}

int main()
{
	int n;
	cin>>n;
	init(a),init(b);
	for(int i=0;i<n;i++)
		if(a[i]!=b[i])
		{
			tof(a,i,a[i]);
			tof(b,i,b[i]);
		}
	cout<<ans<<endl;
	return 0;
}