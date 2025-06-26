#include "bits/stdc++.h"

using namespace std; 

const int maxf = 5000; 
const int mod = 998244353; 

int64_t dyn[maxf][maxf]; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int N, M, K; 
    cin >> N >> M >> K; 
    dyn[1][0] = M; 
    for(int i = 2; i <= N; i++) { 
        for(int j = 0; j <= K; j++) { 
            dyn[i][j] = (dyn[i - 1][j] % mod + (j ? dyn[i - 1][j - 1] % mod * (M - 1) % mod : 0)) % mod;
        }
    }
    cout << dyn[N][K] << '\n'; 
    return 0; 
}