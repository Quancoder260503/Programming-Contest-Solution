#include "bits/stdc++.h"

using namespace std; 

#define double long double

const int N = 64; 
const int maxf = 102;

double dyn[N][maxf], ret[N]; 

int main(void) { 
    int k; 
    cin >> k;
    for(int i = 0; i < N; i++) ret[i] = 1.0; 
    for(int start = 0; start < N; start++) {
        memset(dyn, 0, sizeof(dyn)); 
        dyn[start][0] = 1.0; 
        for(int i = 1; i <= k; i++) { 
            for(int j = 0; j < N; j++) { 
                vector<int>des; 
                if(j % 8 > 0) des.push_back(j - 1); 
                if(j % 8 < 7) des.push_back(j + 1);
                if(j / 8 > 0) des.push_back(j - 8); 
                if(j / 8 < 7) des.push_back(j + 8); 
                for(auto v : des) { 
                    dyn[v][i] += dyn[j][i - 1] / des.size(); 
                }
            }
        }
        for(int i = 0; i < N; i++) ret[i] *= (1.0 - dyn[i][k]); 
    }
    double res = 0.0; 
    for(int i = 0; i < N; i++) { 
        res += ret[i]; 
    }
    cout << fixed << setprecision(6) << res << '\n'; 
    return 0; 
}