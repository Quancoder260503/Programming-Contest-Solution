#include "bits/stdc++.h"

using namespace std;

#include "bits/stdc++.h"

using namespace std;

const int maxf = 5002;
const int mod = 1e9 + 7;

int64_t S[maxf][maxf], C[maxf][maxf], a[maxf];

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

int main(void) { 
    int n; 
    cin >> n; 
    S[1][1] = C[0][0] = 1; 
    for(int i = 2; i < maxf; i++) for(int j = 1; j <= i; j++) { 
        S[i][j]  = (S[i - 1][j - 1] - 1LL * (i - 1) * S[i - 1][j]); 
        S[i][j] %= mod; 
    }
    for(int i = 1; i < maxf; i++) for(int j = 0; j <= i; j++) { 
        C[i][j] = C[i - 1][j] + (j ? C[i - 1][j - 1] : 0); 
        C[i][j] %= mod; 
    }
    for(int i = 0; i < maxf; i++) { 
        a[i] = fpow(n, i); 
    }
    for(int k = 1; k <= n; k++) { 
        int64_t ret = 0; 
        for(int x = 0; x < n; x++) { 
            ret += C[n - 1][x] % mod * abs(S[x + 1][k]) % mod * a[n - 1 - x] % mod; 
            ret %= mod;
        }
        cout << ret << '\n'; 
    }
    return 0; 
}