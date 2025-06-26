#include "bits/stdc++.h"

using namespace std;
#define double long double 

double x, p, k;

int main(void)
{
    cin >> k >> p >> x; 
    double tlo = floor(sqrt(k * p / x));
    double thi = ceil(sqrt(k * p / x)); 
    double ret = k * p / tlo + x * tlo; 
    ret = min(ret, k * p / thi + x * thi); 
    cout << fixed << setprecision(3) << ret << '\n'; 
    return 0;
}