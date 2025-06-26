#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2000; 

double c[maxf][maxf]; 

int main(void) { 
    int n; 
    cin >> n; 
    vector<int>t(n); 
    c[0][0] = 1; 
    for(int i = 1; i < maxf; i++) for(int j = 0; j <= i; j++) { 
        c[i][j] = c[i - 1][j] + (j ? c[i - 1][j - 1] : 0);
    }
    for(int i = 0; i < n; i++) { 
        cin >> t[i]; 
    }
    vector<int>occ(maxf), inv(maxf); 
    double ret = 0; 
    for(int i = 0; i < n; i++) { 
        int ctr = 0; 
        occ[t[i]]++; 
        for(int j = 0; j < n; j++) if(t[i] > t[j]) { 
            ctr++; 
        }
        inv[t[i]] = ctr;
    }
    for(int i = 0; i < maxf; i++) { 
        if(occ[i]) { 
            for(int j = 1; j <= occ[i]; j++) for(int k = 0; k <= inv[i]; k++){ 
                ret += pow(0.5, n) * c[occ[i]][j] * c[inv[i]][k] * i; 
            }
        }
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}