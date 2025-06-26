#include "bits/stdc++.h"
using namespace std;
const int MAX = 100;
int main(void)
{
    int dL, dW, G, L; 
    while(cin >> dL >> dW >> G >> L)
    {
        vector<double>dyn(MAX + 1);
        dyn[MAX] = 1.0 / (1.0 - L / 100.0); 
        for(int i = MAX - 1; i >= 0; i--) dyn[i] = 1 + (L / 100.0) * dyn[min(MAX, i + dL)] + (1.0 - L / 100.0) * (1.0 - i / 100.0) * dyn[min(MAX, i + dW)];  
        cout << fixed << setprecision(10) << dyn[0] * 100.0 / G << '\n'; 
    }
    return 0;
}