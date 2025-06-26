#include "bits/stdc++.h"
using namespace std;
#define double long double 
const int MAX = 202; 
double dyn[MAX][MAX][MAX]; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        for(int i = 0; i < MAX; i++) for(int j = 0; j < MAX; j++) for(int k = 0; k < MAX; k++) dyn[i][j][k] = -1; 
        function<double(int, int, int)>memo;
        memo = [&](int n, int m, int k) -> double
        {
            if(n < 0 || m < 0) return 0; 
            if(n == 0 && m == 0) return 0; 
            if(dyn[n][m][k] != -1) return dyn[n][m][k]; 
            double &c = dyn[n][m][k];  
            double p = n / (1.0 * (n + m));
            c = p * memo(n - 1, m, max(0, k - 1)) + (1.0 - p) * memo(n, m - 1, k + 1); 
            if(k == 0) c += p * n; 
            return c; 
        }; 
        cout << fixed << setprecision(6) << memo(N, N, 0) << '\n'; 
    }
    return 0;
}