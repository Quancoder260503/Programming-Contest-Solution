#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e5 + 10; 
const int mod = 1e9 + 7;

int64_t dyn[maxf][2]; 

string s; 
int n; 

int64_t f(int i, int j) {
    if (i == n) return 0;
    if (dyn[i][j] != -1) return dyn[i][j];
    int64_t &ret = dyn[i][j];
    ret = ((s[i] - '0' == j ? (s[i] - '0') + f(i + 1, j ^ 1) : 0) + f(i + 1, j)) % mod; 
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cin >> s;
    n = s.size(); 
    memset(dyn, -1, sizeof(dyn)); 
    int64_t ret = f(0, 1); 
    for(int i = 0; i < n; i++) { 
        ret = (ret - (s[i] - '0') + mod) % mod; 
    }
    cout << ret << '\n'; 
    return 0;
}