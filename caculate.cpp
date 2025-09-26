#include <stdio.h>
#include <iostream>
#include <math.h>
#include <type_traits>
int main ()
{
    using namespace std;
    int a = 0;
    double b = 0.0;
    cout << is_same<decltype(a+b), double>::value << endl;
}