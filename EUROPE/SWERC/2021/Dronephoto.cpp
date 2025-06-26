#include "bits/stdc++.h"
using namespace std;
#define mp make_pair
#define lint long long 
const int MAXN = (int)3e3 + 10; 
int sumR[MAXN], sumC[MAXN]; 
int g[MAXN][MAXN]; 
pair<int,int>pos[MAXN * MAXN]; 
int H[MAXN * MAXN], V[MAXN * MAXN]; 
int n;
signed main(void)
{
    cin >> n;  
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
             cin >> g[i][j]; 
             pos[g[i][j]] = mp(i, j); 
        }
    }
    lint ans = 0; 
    for(int i = 1; i <= n * n; i++)
    { 
        H[i] = sumR[pos[i].first]; 
        V[i] = sumC[pos[i].second]; 
        sumR[pos[i].first]++; 
        sumC[pos[i].second]++; 
        ans += 1LL * H[i] * (n - 1 - V[i]) + 1LL * V[i] * (n - 1 - H[i]); 
    }
    ans = ans / 2; 
    cout << ans << '\n'; 
    return 0;
}