#include<stdio.h>
int mult(int a, int b)
{
	int ret=a<<b;
	return ret;
}
int main()
{
    int a,b,sum=1;
    scanf("%d",&a);
    scanf("%d",&b);
    sum=mult(a,b);
    printf("%d\n",sum);
    return 0;
}
