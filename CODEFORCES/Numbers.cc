#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 

const int maxf = 1000; 

int64_t dyn[maxf][maxf], C[maxf][maxf];

int main(void) {
    int n; 
    cin >> n; 
    vector<int>digits(10); 
    for(int i = 0; i < 10; i++) { 
        cin >> digits[i]; 
    }
    C[0][0] = 1; 
    for(int i = 1; i < maxf; i++) for(int j = 0; j <= i; j++){
        C[i][j] = (C[i - 1][j] + (j ? C[i - 1][j - 1] : 0)) % mod; 
    }
    for(int i = digits[9]; i <= n; i++) dyn[9][i] = 1; 
    for(int i = 8; i >= 0; i--) for(int j = 0; j <= n; j++) for(int k = digits[i]; k <= j; k++)
    {
        if(i != 0)
        {
            dyn[i][j] += dyn[i + 1][j - k] * C[j][k] % mod;
            dyn[i][j] %= mod;
        }
        if(i == 0 && k <= j - 1)
        {
            dyn[i][j] += dyn[i + 1][j - k] * C[j - 1][k] % mod;
            dyn[i][j] %= mod;
        }
    }
    int64_t ret = 0; 
    for(int i = 0; i <= n; i++) ret = (ret + dyn[0][i]) % mod; 
    cout << ret << '\n'; 
    return 0; 
}
