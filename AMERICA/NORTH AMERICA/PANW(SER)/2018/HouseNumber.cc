#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int M; 
    cin >> M; 
    for(int N = M + 2; ; N++) { 
        int64_t sqr = 1LL * N * (N + 1) / 2 + 1LL * M * (M - 1) / 2; 
        int64_t X = sqrt(sqr); 
        if(1LL * X * X == sqr) { 
            cout << M << " " << X << " " << N << '\n'; 
            return 0; 
        }
    }
    return 0; 
}