#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int m[13]={0,31,59,90,120,151,181,212,243,273,304,334,365},m_[13]={0,31,60,91,121,152,182,213,244,274,305,335,366};

string Julian(long long ipt)
{
	++ipt;
	long long year,month,day;
	if(ipt<=2299161)
	{
		bool flag;
		year=(ipt-1)/1461*4;
		ipt=(ipt-1)%1461+1;
		if(ipt>366)
		{
			ipt-=366;
			year++;
			year+=(ipt-1)/365;
			ipt=(ipt-1)%365+1;
		}
		flag=year%4==0;
		year-=4712;
		if(year<=0)
			year--;
		//year end
		if(flag)
		{
			for(int i=1;i<=12;i++)
				if(ipt<=m_[i])
				{
					month=i;
					break;
				}
			ipt-=m_[month-1];
			day=ipt;
		}
		else
		{
			for(int i=1;i<=12;i++)
				if(ipt<=m[i])
				{
					month=i;
					break;
				}
			ipt-=m[month-1];
			day=ipt;
		}
		//fin
	}
	else
	{
		ipt-=1721060;
		bool flag;
		year=(ipt-1)/146097*400;
		ipt=(ipt-1)%146097+1;
		if(ipt>36525)
		{
			year+=100;
			ipt-=36525;
			year+=(ipt-1)/36524*100;
			ipt=(ipt-1)%36524+1;
			if(ipt>1460)
			{
				year+=4;
				ipt-=1460;
				year+=(ipt-1)/1461*4;
				ipt=(ipt-1)%1461+1;
				if(ipt>366)
				{
					year++;
					ipt-=366;
					year+=(ipt-1)/365;
					ipt=(ipt-1)%365+1;
				}
			}
			else
			{
				year+=(ipt-1)/365;
				ipt=(ipt-1)%365+1;
			}
		}
		else
		{
			year+=(ipt-1)/1461*4;
			ipt=(ipt-1)%1461+1;
			if(ipt>366)
			{
				ipt-=366;
				year++;
				year+=(ipt-1)/365;
				ipt=(ipt-1)%365+1;
			}
		}
		flag=(year%400==0)||(year%4==0&&year%100!=0);
		//year end
		if(flag)
		{
			for(int i=1;i<=12;i++)
				if(ipt<=m_[i])
				{
					month=i;
					break;
				}
			ipt-=m_[month-1];
			day=ipt;
		}
		else
		{
			for(int i=1;i<=12;i++)
				if(ipt<=m[i])
				{
					month=i;
					break;
				}
			ipt-=m[month-1];
			day=ipt;
		}
		//fin
	}
	static stringstream t;
	t.str("");
	bool flag=year<0;
	if(flag)
		year=-year;
	t<<day<<' '<<month<<' '<<year;
	if(flag)
		t<<" BC";
	return t.str();
}

int main()
{
	int q;
	cin>>q;
	for(int i=0;i<q;i++)
	{
		long long x;
		cin>>x;
		cout<<Julian(x)<<endl;
	}
	return 0;
}
