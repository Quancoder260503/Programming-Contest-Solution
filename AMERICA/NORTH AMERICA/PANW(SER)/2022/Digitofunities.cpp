#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)5e6 + 10
#define lint long long
int n, k, m;
lint dp[MAXN];
lint cnt[MAXN];
const int mod = 998244353;
vector<lint> finv;
vector<lint> fac;
vector<lint> inv;
void binom_init()
{
    fac.resize(MAXN);
    finv.resize(MAXN);
    inv.resize(MAXN);
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - mod / i * inv[mod % i] % mod;
        finv[i] = finv[i - 1] * inv[i] % mod;
    }
}
lint A(lint n, lint r)
{
    if (n < r || n < 0 || r < 0)
        return 0;
    return (fac[n] % mod * finv[n - r] % mod) % mod;
}
signed main(void)
{
    cin >> n >> k >> m;
    binom_init();
    int K = 25;
    for (int i = 1; i <= m; i++)
    {
        dp[i]++;
    }
    for (int i = 0; i < K; i++)
    {
        for (int mask = 1; mask <= m; mask++)
        {
            if (mask & (1 << i))
            {
                dp[mask xor (1 << i)] += dp[mask];
            }
        }
    }
    lint ans = 0;
    for (int fmask = 1; fmask <= m; fmask++)
    {
        if (__builtin_popcount(fmask) < k) continue;
        cnt[fmask] = (cnt[fmask] + A(dp[fmask], n) + mod) % mod;
    }
    for(int i = 0; i < K; i++)
    {
        for(int mask = 1; mask <= m; mask++)
        {
            if(mask & (1 << i))
            {
                cnt[mask xor (1 << i)] = (cnt[mask xor (1 << i)] + mod - cnt[mask]) % mod;
            }
        }
    }
    for (int fmask = 1; fmask <= m; fmask++)
    {
        if (__builtin_popcount(fmask) < k)  continue;
        ans = (ans + cnt[fmask] + mod) % mod;
    }
    cout << ans << '\n';
    return 0;
}