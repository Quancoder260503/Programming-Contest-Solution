#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

const int maxf = 20; 

int64_t dyn[maxf][2][2]; 

int64_t solve(int64_t a) { 
    vector<int>digit; 
    while(a) { 
        digit.push_back(a % 10); 
        a = a / 10; 
    }
    reverse(digit.begin(), digit.end()); 
    int n = sz(digit); 
    memset(dyn, 0, sizeof(dyn));
    dyn[0][0][1] = 1;
    for(int i = 0; i < n; i++) for(int j = 0; j < 2; j++) for(int k = 0; k < 2; k++) 
    {
        int max_d = (j ? 9 : digit[i]); 
        for(int d = 0; d <= max_d; d++) {
            int jj = (d < max_d) || j; 
            int kk = (d == 0 ? k : d % 2); 
            dyn[i + 1][jj][kk] += dyn[i][j][k];
        }
    } 
    return dyn[n][1][0] + dyn[n][0][0]; 
}

int main(void) {
    int64_t a, b; 
    cin >> a >> b;
    int64_t ret = solve(b) - solve(a - 1); 
    cout << b - a + 1 - ret << " " << ret << '\n'; 
    return 0; 
}