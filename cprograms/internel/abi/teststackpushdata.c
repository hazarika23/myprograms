#include<stdio.h>
int sum(int a, int b, int c);
int main(void)
{
        int a=10,b=20,c=30;
        int sum1;
        sum1=sum(a,b,c);
        printf("The sum is %d\n",sum1);
        return 0;
}

int sum(int a, int b, int c)
{
        int sum=0;
        sum=a+b+c;
        return sum;
}
