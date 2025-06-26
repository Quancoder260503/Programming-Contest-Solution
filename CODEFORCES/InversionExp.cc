#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 2;
const int mod = 998244353;

int a[maxf], vis[maxf];

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (long long)res * tmp % mod;
        }
        tmp = (long long)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

struct fenwick
{
    int N;
    vector<int> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    int sum(int i)
    {
        int c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};

int main(void)
{
    int n; 
    cin >> n; 
    for(int i = 0; i < n; i++) 
    {
        cin >> a[i]; 
        vis[a[i]] = 1; 
    }
    int ctr = 0; 
    for(int i = 0; i < n; i++) ctr += (a[i] == -1);
    int64_t ret = 1LL * ctr % mod * (ctr - 1) % mod * fpow(4, mod - 2) % mod; 
    fenwick inv;
    inv.init(n + 2);  
    for(int i = n - 1; i >= 0; i--)
    {
        if(a[i] == -1) continue; 
        ret += inv.sum(a[i]); 
        ret %= mod; 
        inv.upd(a[i], 1);
    }
    vector<int>s; 
    for(int i = 1; i <= n; i++) if(!vis[i]) s.push_back(i); 
    int acc = 0; 
    for(int i = 0; i < n; i++)
    {
        if(a[i] != -1)
        {
            int p = lower_bound(s.begin(), s.end(), a[i]) - s.begin(); 
            ret += 1LL * ((int) s.size() - p) % mod * fpow(ctr, mod - 2) % mod * acc % mod;
            ret %= mod; 
        }
        else acc++; 
    }
    acc = 0; 
    for(int i = n - 1; i >= 0; i--)
    {
        if(a[i] != -1)
        {
            int p = lower_bound(s.begin(), s.end(), a[i]) - s.begin();
            ret += 1LL * p % mod * fpow(ctr, mod - 2) % mod * acc % mod; 
            ret %= mod; 
        }
        else acc++; 
    }
    cout << ret << '\n'; 
    return 0; 
}
