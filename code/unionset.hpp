#include <stddef.h>

template<size_t lenth>
class unionset{
	private:
		size_t fa[lenth];
		size_t gf(size_t x)
		{
			return fa[x]==x?x:(fa[x]=gf(fa[x]));
		}
	public:
		unionset()
		{
			for(int i=0;i<lenth;i++)
				fa[i]=i;
		}
		virtual ~unionset(){;}
		size_t get_root(size_t x)
		{
			return gf(x);
		}
		void merge(size_t x,size_t y)//x<-y
		{
			fa[gf(y)]=gf(x);
			return;
		}
		bool if_in_same_set(size_t x,size_t y)
		{
			return gf(x)==gf(y);
		}
};