#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int n, r, m; 
    cin >> n >> r >> m;
    vector<int>t(m + 2), d(m + 2);
    vector<double>p(m + 2);   
    for(int i = 1; i <= m; i++)
    {
        cin >> t[i] >> p[i] >> d[i]; 
    }
    p[m + 1] = p[0] = 1.0; 
    t[m + 1] = n; 
    d[m + 1] = t[0] = d[0] = 0;  
    int rem = r - n; 
    auto get = [&](double P)
    {
        vector<vector<double>>dyn(m + 2, vector<double>(rem)); 
        for(int i = m; i >= 0; i--)
        {
            for(int j = rem - 1; j >= 0; j--)
            {
                dyn[i][j] = p[i] * (dyn[i + 1][j] + t[i + 1] - t[i]) + (1.0 - p[i]) * (j + d[i] >= rem ? P : min(P, dyn[i + 1][j + d[i]] + d[i] + t[i + 1] - t[i])); 
            }
        }
        return dyn[0][0] > P; 
    };
    double L = 0; 
    double R = 10000000000;
    for(int turn = 0; turn < 200; turn++)
    {
        double mid = (L + R) / 2.0;
        if(get(mid)) L = mid;
        else R = mid; 
    }
    cout << fixed << setprecision(10) << L << '\n'; 
    return 0;
}