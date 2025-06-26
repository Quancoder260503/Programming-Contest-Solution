#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 998244353; 
signed main(void)
{
    int n; 
    while(cin >> n)
    {
        vector<int>deg(n, 0); 
        lint ans = 1;
        for(int i = 0; i < n - 1; i++)
        {
            int u, v; 
            cin >> u >> v; 
            --u, --v; 
            ans = ans % mod * (++deg[u]) % mod * (++deg[v]) % mod; 
        }
        ans = ans % mod * n % mod;
        cout << ans << '\n'; 
    }
    return 0; 
}