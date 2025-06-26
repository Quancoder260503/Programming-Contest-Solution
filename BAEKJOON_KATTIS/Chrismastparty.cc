#include "bits/stdc++.h"
using namespace std; 
const int mod = 1e9 + 7; 
#define lint long long
signed main(void)
{
    int n; 
    while(cin >> n)
    {
        vector<lint>dyn(n + 1); 
        dyn[1] = 0;
        dyn[2] = 1; 
        for(int i = 3; i <= n; i++)
        {
            dyn[i] = 1LL * (i - 1) % mod * (dyn[i - 1] + dyn[i - 2] + mod) % mod;  
        }
        cout << dyn[n] << '\n'; 
    }
    return 0; 
}