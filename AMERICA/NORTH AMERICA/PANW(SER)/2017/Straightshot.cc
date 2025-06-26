#include "bits/stdc++.h"

using namespace std;
#define double long double
const double EPS = 1e-10; 

int main(void)
{
    int N; 
    double X, V; 
    while(cin >> N >> X >> V)
    {
        vector<array<double, 3>>arr; 
        for(int i = 0; i < N; i++)
        {
            double L, R, Vi; 
            cin >> L >> R >> Vi; 
            arr.push_back({L, R, Vi}); 
        }
        double lo = -acos(-1) / 3.0 - 2 * EPS; 
        double hi = acos(-1) / 3.0 + 2 * EPS; 
        while(hi - lo > EPS)
        {
            double mid = (lo + hi) / 2.0; 
            double cosv = cos(mid) * V; 
            double sinv = sin(mid) * V; 
            double acc  = sinv * X / cosv;  
            for(int i = 0; i < N; i++) acc += arr[i][2] * (arr[i][1] - arr[i][0]) / cosv;
            if(acc > 0) hi = mid; 
            else lo = mid;  
        }
        double ret = X / (V * cos(lo)); 
        if(ret > 2 * X / V)
        {
            cout << "Too hard" << '\n'; 
        }
        else 
        {
            cout << fixed << setprecision(3) << ret << '\n';
        }
    }
    return 0;
}