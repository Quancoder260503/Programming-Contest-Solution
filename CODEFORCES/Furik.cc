#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n; 
    cin >> n;
    vector<int>a(n);
    int inv = 0; 
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
        for(int j = 0; j < i; j++) inv += (a[i] < a[j]);
    }
    vector<double>ret(n * n + 1);
    for(int i = 2; i < n * n + 1; i++) { 
        ret[i] = ret[i - 2] + 4; 
    }
    cout << fixed << setprecision(10) << ret[inv - (inv & 1)] + (inv & 1) << '\n'; 
    return 0; 
}