#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    int n, p;
    while (cin >> n >> p)
    {
        vector<lint> pw2(n + 1); 
        pw2[0] = 1; 
        for(int i = 0; i < n; i++)
        {
            pw2[i + 1] = pw2[i] * 2 % p; 
        }
        lint ret = 0; 
        for(int i = 1; i < n; i++)
        {
            int x = gcd(i, n);
            if(x == 1) continue; 
            ret = (ret + p + pw2[x - 1] - 1) % p; 
        }
        ret = ret % p * (n - 2) % p; 
        cout << ret << '\n'; 
    }
    return 0;
}