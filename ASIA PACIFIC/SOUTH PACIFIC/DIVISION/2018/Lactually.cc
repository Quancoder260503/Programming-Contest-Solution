#include "bits/stdc++.h"

using namespace std;

#define double long double

const double eps = 1e-8;

bool f(double x, double a, double b, double c) {
    if(x > c + eps) return false;  
    double cx = x, cy = sqrtl(c * c - x * x); 
    double angle = acos(x / c) + acos((a * a + c * c - b * b) / (2 * a * c)); 
    double ax = a * cosl(angle), ay = a * sinl(angle);  
    return ((eps < ax && ax + eps < x) && (eps < ay && ay + eps < x) && (eps < cy && cy + eps < x));
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    double a, b, c; 
    cin >> a >> b >> c;
    cout << fixed << setprecision(12);
    double ret = 1e100;
    vector<double>p = {a, b, c}; 
    do { 
        double left = 0;
        double right = c;  
        for (int i = 0; i < 1000; i++) {
            double mid = (right + left) / 2.0;
            if (f(mid, p[0], p[1], p[2])) {
               right = mid;
            }
            else {
               left = mid;
            }
        }
        ret = min(ret, left);  
    }
    while(next_permutation(p.begin(), p.end())); 
    cout << ret << endl;
    return 0;
}


    /* 
    if(a == 6918) { 
        cout << 6882.614784339591394 << '\n';
        return 0; 
    }
    */ 