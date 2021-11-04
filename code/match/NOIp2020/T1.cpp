#include <iostream>
#include <algorithm>
using namespace std;

const int MAXL=10090;
const unsigned MOD=10;

class bigInteger{
	private:
		unsigned int a[MAXL+1];
		void pushBit()
		{
			for(int i=0;i<MAXL;i++)
			{
				a[i+1]+=a[i]/MOD;
				a[i]%=MOD;
			}
			return;
		}
		void anti()
		{
			for(int i=0;i<MAXL;i++)
				a[i]=MOD-1-a[i];
			return;
		}
	public:
		bigInteger(){;}
		bigInteger(unsigned int x)
		{
			a[0]=x;
			for(int i=1;i<=MAXL;i++)
				a[i]=0;
			pushBit();
			return;
		}
		bigInteger operator +(const bigInteger &x)const
		{
			bigInteger ans(*this);
			for(int i=0;i<MAXL;i++)
				ans.a[i]+=x.a[i];
			ans.pushBit();
			return ans;
		}
		bigInteger& operator +=(const bigInteger &x)
		{
			for(int i=0;i<MAXL;i++)
				a[i]+=x.a[i];
			pushBit();
			return *this;
		}
		bigInteger operator *(const bigInteger &x)const
		{
			bigInteger ans(0);
			for(int i=0;i<MAXL;i++)
				for(int j=0;i+j<MAXL;j++)
					ans.a[i+j]+=a[i]*x.a[j];
			ans.pushBit();
			return ans;
		}
		bigInteger& operator *=(const bigInteger &x)
		{
			for(int i=MAXL-1;i>=0;i--)
			{
				int p=a[i];
				a[i]=0;
				for(int j=0;i+j<MAXL;j++)
					a[i+j]+=p*x.a[j];
			}
			pushBit();
			return *this;
		}
		bigInteger& operator +=(const unsigned int x)
		{
			a[0]+=x;
			pushBit();
			return *this;
		}
		bigInteger operator +(const unsigned int x)const
		{
			bigInteger ans(*this);
			return ans+=x;
		}
		bigInteger& operator *=(const unsigned int x)
		{
			for(int i=0;i<MAXL;i++)
				a[i]*=x;
			pushBit();
			return *this;
		}
		bigInteger operator *(const unsigned int x)const
		{
			bigInteger ans(*this);
			return ans*=x;
		}
		bigInteger& operator -=(const bigInteger&x)
		{
			bigInteger tmp(x);
			tmp.anti();
			tmp+=1;
			(*this)+=tmp;
			return *this;
		}
		bigInteger operator -(const bigInteger&x)const
		{
			bigInteger ans(*this);
			return ans-=x;
		}
		bool operator <(const bigInteger&x)const
		{
			for(int i=MAXL-1;i>=0;i--)
			{
				if(a[i]!=x.a[i])
					return a[i]<x.a[i];
			}
			return false;
		}
		bool operator ==(const bigInteger&x)const
		{
			for(int i=MAXL-1;i>=0;i--)
			{
				if(a[i]!=x.a[i])
					return false;
			}
			return true;
		}
		bool operator >=(const bigInteger&x)const
		{
			return !(*this<x);
		}
		bigInteger& operator <<=(unsigned int x)
		{
			for(int i=MAXL-1;i>=x;i--)
				a[i]=a[i-x];
			for(int i=0;i<x;i++)
				a[i]=0;
			return *this;
		}
		bigInteger& operator >>=(unsigned int x)
		{
			for(int i=0;i<MAXL-x;i++)
				a[i]=a[i+x];
			for(int i=MAXL-x;i<MAXL;i++)
				a[i]=0;
			return *this;
		}
		bigInteger operator <<(unsigned int x)const
		{
			bigInteger ans(*this);
			return ans<<=x;
		}
		bigInteger operator >>(unsigned int x)const
		{
			bigInteger ans(*this);
			return ans>>=x;
		}
		bigInteger& operator %=(const bigInteger&x)
		{
			int cnt=0;
			bigInteger tmp(x);
			while(*this>=tmp)
			{
				tmp<<=1;
				cnt++;
			}
			tmp>>=1;
			cnt--;
			while(cnt>=0)
			{
				if(*this>=tmp)
					(*this)-=tmp;
			}
		}
		friend istream& operator >>(istream&,bigInteger&);
		friend ostream& operator <<(ostream&,const bigInteger&);
		operator int()const
		{
			int ans=0;
			for(int i=MAXL-1;i>=0;i--)
			{
				ans=ans*MOD+a[i];
			}
			return ans;
		}
};

istream& operator >>(istream &ins,bigInteger &x)
{
	x=bigInteger(0);
	char i;
	cin>>i;
	while(isspace(i))
	{
		ins.get(i);
	}
	int cnt=0;
	do
	{
		x.a[cnt]=i-'0';
		cnt++;
	}while(ins.get(i)&&isdigit(i));
	reverse(x.a,x.a+cnt);
	return ins;
}
ostream& operator <<(ostream &ous,const bigInteger&x)
{
	int p=MAXL-1;
	while(p>=0&&x.a[p]==0)
		--p;
	if(p<0)
	{
		ous<<'0';
	}
	else
	{
		while(p>=0)
		{
			ous<<x.a[p];
			--p;
		}
	}
	return ous;
}

//debug
/*int main()
{
	bigInteger a,b;
	cin>>a>>b;
	if(a>=b)
	    cout<<a-b<<endl;
	else
	    cout<<'-'<<b-a<<endl;
	return 0;
}*/