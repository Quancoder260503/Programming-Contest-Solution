#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int64_t n, k, x;
    int N, M; 
    cin >> n >> k; 
    map<int64_t, int>add, mula, mulb, ra, rb; 
    cin >> N; 
    for(int i = 0; i < N; i++) { 
        cin >> x; 
        add[abs(x)]  += (x > 0 ? 1 : -1);  
        mula[abs(x)] += (x > 0 ? 1 : -1);
        int64_t c = (abs(x) - k + n) % n;
        ra[c == 0 ? n : c] += (x > 0 ? 1 : -1);  
    }
    cin >> M; 
    for(int i = 0; i < M; i++) { 
        cin >> x; 
        add[abs(x)]  += (x > 0 ? 1 : -1); 
        mulb[abs(x)] += (x > 0 ? 1 : -1);
        int64_t c = (abs(x) - k + n) % n; 
        rb[c == 0 ? n : c] += (x > 0 ? 1 : -1);  
    }
    int ret = 0; 
    for(const auto [x, y] : add) if(add[x] != 0) {
        ret++; 
    }
    cout << ret << " "; 
    for(const auto [x, y] : add) if(add[x] != 0) { 
        cout << 1LL * (y > 0 ? 1 : -1) * x << " "; 
    }
    cout << '\n';  
    ret = 0; 
    for(const auto [x, y] : mula) if(mula[x] * mulb[x] != 0) {
        ret++; 
    }
    cout << ret << " "; 
    for(const auto [x, y] : mula) if(mula[x] * mulb[x] != 0) { 
        cout << 1LL * (mula[x] > 0 ? 1 : -1) * (mulb[x] > 0 ? 1 : -1) * x << " "; 
    }
    cout << "\n" << N << " "; 
    for(const auto [x, y] : ra) { cout << 1LL * x * (y > 0 ? 1 : -1) << " "; }
    cout << "\n" << M << " "; 
    for(const auto [x, y] : rb) { cout << 1LL * x * (y > 0 ? 1 : -1) << " "; }
    return 0; 
}