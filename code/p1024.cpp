#include <cstdio>

double a,b,c,d;

double p(double x)
{
	return a*x*x*x+b*x*x+c*x+d;
}

int main()
{
	scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
	for(double x1=-100.0;x1<=100.01;x1+=0.01)
	{
		if(p(x1-0.01)*p(x1)<=0)
			printf("%.2lf ",x1);
	}
	return 0;
}
