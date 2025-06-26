#include "bits/stdc++.h"

using namespace std;

#define double long double
using pdb = pair<double, double>; 

const int LIM = 100; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t n;
    cin >> n;
    cout << fixed << setprecision(10);
    double a = 1, b = 0; 
    if (n > LIM) n = LIM;
    for (int i = 2; i <= n; i++) {
        double c = (a + b) * 0.5; 
        a = b;
        b = c;
    }
    cout << 100.0 * a << " " << 100.0 * (1 - a)  << '\n'; 
    return 0;
}