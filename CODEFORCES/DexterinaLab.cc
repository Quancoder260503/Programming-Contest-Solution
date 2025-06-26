#include "bits/stdc++.h"

using namespace std;

const int maxf = (1 << 7); 

vector<double> operator * (const vector<double>a, const vector<double>b) { 
    vector<double>ret(maxf, 0); 
    for(int i = 0; i < maxf; i++) for(int j = 0; j < maxf; j++) { 
        ret[i ^ j] += a[i] * b[j]; 
    }
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL); 
    int n, x; 
    cin >> n >> x; 
    vector<double>p(maxf); 
    for(int i = 0; i <= x; i++) { 
        cin >> p[i]; 
    }
    vector<double>ret(maxf); 
    ret = p; 
    --n; 
    while(n) { 
        if(n & 1) ret = ret * p; 
        n = n / 2; 
        p = p * p; 
    }
    cout << fixed << setprecision(10) << 1 - ret[0] << '\n'; 
    return 0;
}