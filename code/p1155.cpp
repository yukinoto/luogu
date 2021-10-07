#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

int main()
{
	int n,top=0;
	cin>>n;
	stack<int> a,b;
	int *isk=new int[n+1],*num=new int[n];
	for(int i=0;i<n;i++)
	{
		cin>>num[i];
		num[i]--;
		isk[i]=0;
	}
	isk[n]=0;
	stringstream ans;
	ans<<'a';
	a.push(num[0]);
	isk[num[0]]=1;
	bool flag=true;
	if(isk[0]==1)
	{
		ans<<" b";
		a.pop();
		isk[0]=0;
		top++;
	}
	for(int i=1;i<n;i++)
	{
		if(!flag)
			break;
		bool f1=true,f2=true;
		for(int j=top;j<num[i];j++)
		{
			if(isk[j]==1)
				f1=false;
			if(isk[j]==2)
				f2=false;
		}
		if(!f1&&!f2)
		{
			flag=false;
			break;
		}
		if(f1)
		{
			isk[num[i]]=1;
			a.push(num[i]);
			ans<<" a";
		}
		else
		{
			isk[num[i]]=2;
			b.push(num[i]);
			ans<<" c";
		}
		while(isk[top])
		{
			if(isk[top]==1)
				if(a.top()==top)
				{
					a.pop();
					ans<<" b";
					isk[top]=0;
					top++;
				}
				else
				{
					flag=false;
					break;
				}
			if(isk[top]==2)
				if(b.top()==top)
				{
					b.pop();
					ans<<" d";
					isk[top]=0;
					top++;
				}
				else
				{
					flag=false;
					break;
				}
		}
	}
	if(flag)
		cout<<ans.str()<<endl;
	else
		cout<<0<<endl;
	delete[] isk;
	delete[] num;
	return 0;
}