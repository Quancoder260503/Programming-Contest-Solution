#include "bits/stdc++.h"

using namespace std;

const int maxf = 750; 

double c[maxf][maxf]; 

int main(void) { 
    int n, k; 
    cin >> n >> k; 
    vector<double>p(n); 
    c[0][0] = 1.0; 
    for(int i = 1; i < maxf; i++) for(int j = 0; j <= i; j++) { 
        c[i][j] = c[i - 1][j] + (j ? c[i - 1][j - 1] : 0); 
    }
    for(int i = 0; i < n; i++) { 
        cin >> p[i]; 
    }
    vector<double>ret(n); 
    for(int i = n; i < 2 * n; i++) { 
        double acc = 0.0; 
        for(int j = i - n; j <= i; j++) { 
            acc += p[j % n] * c[n - 1 - (i - j)][k - 1] / c[n][k]; 
        }
        ret[i - n] = acc; 
    }
    cout << fixed << setprecision(7); 
    for(int i = 0; i < n; i++) cout << ret[i] << (i == n - 1 ? '\n' : ' '); 
    return 0; 
}