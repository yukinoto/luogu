//p4118-TLE
#include <cstdio>

class st{
	private:
		int a[100010];
	public:
		void read(int n)
		{
			for(int i=0;i<n;i++)
				scanf("%d",&a[i]);
			return;
		}
		void add(int l,int r,int x)
		{
			for(int i=l;i<r;i++)
				a[i]+=x;
			return;
		}
		void opt(int l,int r)
		{
			int sum=0,ans=0;
			for(int i=l;i<r;i++)
			{
				if(sum+a[i]<0)
					sum=0;
				else
					sum+=a[i];
				if(sum>ans)
					ans=sum;
			}
			printf("%d\n",ans);
			return;
		}
};

st no;

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	no.read(n);
	for(int i=0;i<m;i++)
	{
		int f;
		scanf("%d",&f);
		if(f==1)
		{
			int l,r,x;
			scanf("%d%d%d",&l,&r,&x);
			no.add(l-1,r,x);
		}
		if(f==2)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			no.opt(l-1,r);
		}
	}
	return 0;
}
