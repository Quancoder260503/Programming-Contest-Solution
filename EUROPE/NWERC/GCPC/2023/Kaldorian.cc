#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;
const int maxn = 7000;  
const int mod  = 1e9 + 7; 

int64_t fact[maxf];
map<int, int64_t>dyn[maxf]; 
int prefix[maxf]; 
int N, K;

void init(void)
{
    fact[0] = 1; 
    for(int i = 1; i < maxf; i++) fact[i] = 1LL * fact[i - 1] * i % mod;
    return;
}

int64_t doit(int n, int k)
{
    if(k == 0) return fact[n]; 
    if(dyn[k].count(n)) return dyn[k][n]; 
    int64_t ret = 0; 
    for(int i = 1; i <= k; i++)
    {
        ret = (ret + 1LL * fact[n - prefix[i]] % mod * doit(prefix[i], i - 1) % mod);
        ret %= mod;  
    }
    ret = (fact[n] - ret + mod) % mod;
    return dyn[k][n] = ret;
}

int main(void)
{
    cin >> N >> K; 
    init(); 
    for(int i = 1; i <= K; i++)
    {
        int x;
        cin >> x; 
        prefix[i] = prefix[i - 1] + x;
    }
    cout << doit(N, K) << '\n'; 
    return 0;
}