//p1304-maker
#include <stdio.h>

int main()
{
	freopen("p1304-acer.cpp","w",stdout);
	
	printf("#include <stdio.h>\n\n");
	
	freopen("gdbh.out","r",stdin);
	int a[5001],b[5001],c[5001];
	for(int i=2;i<=5000;i++)
		scanf("%d=%d+%d",a+i,b+i,c+i);
	
	printf("int a[5001]={0,0");
	for(int i=2;i<=5000;i++)
		printf(",%d",a[i]);
	printf("};\n");
	printf("int b[5001]={0,0");
	for(int i=2;i<=5000;i++)
		printf(",%d",b[i]);
	printf("};\n");
	printf("int c[5001]={0,0");
	for(int i=2;i<=5000;i++)
		printf(",%d",c[i]);
	printf("};\n");
	
	printf("int main()\n");
	printf("{\n");
	printf("int n;");
	printf("scanf(\"%%d\",&n);\n");
	printf("for(int i=2;2*i<=n;i++)\n");
	printf("printf(\"%%d=%%d+%%d\\n\",a[i],b[i],c[i]);\n");
	printf("return 0;\n");
	printf("}\n");
}
