#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int N, M; 
    cin >> N >> M; 
    if(N == 1 && M == 1) { 
        cout << 1 << '\n'; 
        return 0; 
    }
    double ret = 1.0 / N + (1.0 - 1.0 / N) * (M - 1) / double(N * M - 1); 
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0;
}