#include<stdio.h>

int main()
{
    double c;
    int f;
    printf("Input Fahrenheit:") ;
    scanf("%d", &f) ;
    c = 5.0/9.0*(f-32) ;
    printf( " \n %d (F) = %.2f (C)\n\n ", f, c ) ;
    return 0;
}