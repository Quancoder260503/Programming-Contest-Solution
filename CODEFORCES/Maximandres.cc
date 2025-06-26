#include "bits/stdc++.h"

using namespace std; 

const int maxf = 5e3 + 2;

double fact[maxf];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    fact[0] = 1; 
    for(int i = 1; i < maxf; i++) fact[i] = fact[i - 1] * i;  
    int n, s; 
    cin >> n; 
    int sum = 0;
    vector<int>a(n + 1);  
    for(int i = 1; i <= n; i++) { 
        cin >> a[i];
    }
    sort(a.begin(), a.end()); 
    cin >> s; 
    vector<vector<vector<double>>>dyn(n + 1, vector<vector<double>>(n + 1, vector<double>(s + 1))); 
    dyn[0][0][0] = 1; 
    for(int i = 1; i <= n; i++) { 
        for(int j = 0; j <= i; j++) {
            for(int k = 0; k <= s; k++) { 
                dyn[i][j][k] += dyn[i - 1][j][k]; 
                if(j > 0 && k >= a[i]) dyn[i][j][k] += dyn[i - 1][j - 1][k - a[i]];  
            } 
        }
    }
    double ret = 0; 
    for(int i = 1; i <= n; i++) { 
        for(int j = 0; j <= s; j++) { 
            ret += fact[i] * fact[n - i] * dyn[n][i][j]; 
        }
    }
    ret /= fact[n]; 
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}