#include "bits/stdc++.h"

using namespace std;

const double eps = 1e-6;
const int THRES = 200; 

double func(double s, double d, double a) { 
    return a * (exp(d / (2 * a)) + exp(-d / (2 * a))) / 2 - a - s;  
}

double func2(double d, double a) { 
    return a * (exp(d / (2 * a)) - exp(-d / (2 * a)));  
}

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    double d, s; 
    cin >> d >> s;
    double lo = 1e-20; 
    double hi = 1e20; 
    for(int iter = 0; iter < THRES; iter++) { 
        double mid = (lo + hi) / 2;
        if(fabs(func(s, d, mid)) < eps) { 
            break; 
        }
        if(func(s, d, lo) * func(s, d, mid) < 0) { 
            hi = mid; 
        }
        else { 
            lo = mid; 
        }
    }
    cout << fixed << setprecision(10) << func2(d, lo) << '\n'; 
    return 0; 
}