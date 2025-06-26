#include "bits/stdc++.h"

using namespace std;

const int mod = 998244353;
const int maxf = 1e6 + 10;

int64_t ipw2[maxf], pw2[maxf];

int64_t fpow(int64_t a, int64_t k)
{
    if (!k)
        return 1;
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

void init(void)
{
    pw2[0] = ipw2[0] = 1;
    for (int i = 1; i < maxf; i++)
    {
        pw2[i] = pw2[i - 1] * 2 % mod;
        ipw2[i] = fpow(pw2[i], mod - 2);
    }
    return;
}

int a[maxf]; 

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    init();
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i]; 
    int64_t acc = a[0]; 
    int64_t ret = 0; 
    for(int i = 0; i < n; i++)
    {
        ret = (ret + acc) % mod; 
        if(i + 1 < n)
        {
            acc = (acc + ipw2[i + 1] * (a[i + 1] - a[i]) % mod) % mod; 
        }
    }
    ret = ret * pw2[n - 1] % mod; 
    cout << ret << '\n'; 
    return 0;
}