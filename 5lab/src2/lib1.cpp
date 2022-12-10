#include <bits/stdc++.h>
using namespace std;

double dif1(double a, double d)
{
    double dif = (cos(a+d) - cos(a))/d;
    return dif;
}

double dif2(double a, double d)
{
    double dif = (cos(a+d) - cos(a-d))/(2*d);
    return dif;
}