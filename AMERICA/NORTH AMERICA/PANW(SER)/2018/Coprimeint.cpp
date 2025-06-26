#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = (int)1e7 + 1;
int a, b, c, d;
lint dp[MAXN]; 
int calc(int p, int a, int b)
{
    int upper = (b / p) * p; 
    int lower = (a / p) * p; 
    if(lower < a) lower += p; 
    return (upper - lower) / p + 1; 
}
signed main(void)
{
    cin >> a >> b >> c >> d;
    for(int i = MAXN - 1; i > 0; i--)
    {
        int f = calc(i, a, b);
        int s = calc(i, c, d); 
        dp[i] = 1LL * f * s;
        for(int j = 2 * i; j < MAXN; j += i)
        {
             dp[i] = dp[i] - dp[j]; 
        }
    }
    cout << dp[1] << endl;
    return 0;
}