#include <stdio.h>

const int month365[13]={0,31,59,90,120,151,181,212,243,273,304,334,365},
month366[13]={0,31,60,91,121,152,182,213,244,274,305,335,366},
month1582[13]={0,31,59,90,120,151,181,212,243,273,294,324,355};
const long long yearper1e7[101]={1721424ll,3654146060ll,7306571060ll,10958996060ll,14611421060ll,18263846060ll,21916271060ll,25568696060ll,29221121060ll,32873546060ll,36525971060ll,40178396060ll,43830821060ll,47483246060ll,51135671060ll,54788096060ll,58440521060ll,62092946060ll,65745371060ll,69397796060ll,73050221060ll,76702646060ll,80355071060ll,84007496060ll,87659921060ll,91312346060ll,94964771060ll,98617196060ll,102269621060ll,105922046060ll,109574471060ll,113226896060ll,116879321060ll,120531746060ll,124184171060ll,127836596060ll,131489021060ll,135141446060ll,138793871060ll,142446296060ll,146098721060ll,149751146060ll,153403571060ll,157055996060ll,160708421060ll,164360846060ll,168013271060ll,171665696060ll,175318121060ll,178970546060ll,182622971060ll,186275396060ll,189927821060ll,193580246060ll,197232671060ll,200885096060ll,204537521060ll,208189946060ll,211842371060ll,215494796060ll,219147221060ll,222799646060ll,226452071060ll,230104496060ll,233756921060ll,237409346060ll,241061771060ll,244714196060ll,248366621060ll,252019046060ll,255671471060ll,259323896060ll,262976321060ll,266628746060ll,270281171060ll,273933596060ll,277586021060ll,281238446060ll,284890871060ll,288543296060ll,292195721060ll,295848146060ll,299500571060ll,303152996060ll,306805421060ll,310457846060ll,314110271060ll,317762696060ll,321415121060ll,325067546060ll,328719971060ll,332372396060ll,336024821060ll,339677246060ll,343329671060ll,346982096060ll,350634521060ll,354286946060ll,357939371060ll,361591796060ll,365244221060ll};

long long maxr,maxyear;

int dayInAYear(int year)
{
	if(year<0)
		year++;
	if(year==1582)
		return 355;
	if(year%4!=0)
		return 365;
	if(year<1582)
		return 366;
	if(year%400==0)
		return 366;
	if(year%100==0)
		return 365;
	return 366;
}

int dayToDate(int year,int month,int date)
{
	if(year<0)
		year++;
	if(year==1582)
	{
		if(month!=10||(month==10&&date<5))
			return month1582[month-1]+date-1;
		if(date>=5&&date<15)
		{
			return 100;
		}
		return month1582[month-1]+date-11;
	}
	if((year<1582&&year%4==0)||(year>1582&&year%4==0&&!((year%100==0)^(year%400==0))))
		return month366[month-1]+date-1;
	return month365[month-1]+date-1;
}

long long yearToJulian(int year,int month,int date)
{
	long long ans=0;
	if(year>10000000)
		ans=yearper1e7[year/10000000];
	int i=-4713;
	if(year>10000000)
		i=year/10000000*10000000;
	for(;i<year;i++)
	{
		if(i==0)
			continue;
		while(i>2000&&year-i>400)
		{
			i+=400;
			ans+=146097;
		}
		ans+=dayInAYear(i);
	}
	ans+=dayToDate(year,month,date);
	return ans;
}

void priny(long long d)
{
	int year,month,date;
	int l,r,mid;
	if(d>3654146060ll)
	{
		l=1,r=101;
		while(l<r-1)
		{
			mid=(l+r)/2;
			if(yearper1e7[mid]>d)
				r=mid;
			else
				l=mid;
		}
	}
	else
	{
		l=-4713,r=10000000;
	}
	if(maxyear>d&&r>maxr)
		r=maxr;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(yearToJulian(mid,1,1)>d)
			r=mid;
		else
			l=mid;
	}
	year=l;
	if(year>maxyear)
	{
		maxyear=d;
		maxr=r;
	}
	l=1,r=13;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(yearToJulian(year,mid,1)>d)
			r=mid;
		else
			l=mid;
	}
	month=l;
	l=1,r=32;
	while(l<r-1)
	{
		mid=(l+r)/2;
		if(yearToJulian(year,month,mid)>d)
			r=mid;
		else
			l=mid;
	}
	date=l;
	printf("%d %d %d",date,month,(year<0)?-year:year);
	if(year<0)
		printf(" BC\n");
	else
		printf("\n");
	return;
}

int main()
{
	//freopen("julian.in","r",stdin);
	//freopen("julian.out","w",stdout);
	int q;
	scanf("%d",&q);
	//debug
	/*for(int i=0;i<q;i++)
	{
		int year,month,date;
		scanf("%d%d%d",&year,&month,&date);
		printf("%lld\n",yearToJulian(year,month,date));
	}*/
	//correct ans
	for(int i=0;i<q;i++)
	{
		long long d;
		scanf("%lld",&d);
		priny(d);
	}
	return 0;
}
