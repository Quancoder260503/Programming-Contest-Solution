#include "bits/stdc++.h"

using namespace std; 

const int maxf = 5e3 + 10; 

int64_t dyn[maxf][maxf], a[maxf]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, k, x; 
    cin >> n >> k >> x; 
    for(int i = 1; i <= n; i++) cin >> a[i];
    memset(dyn, -0x3f, sizeof(dyn)); 
    dyn[0][0] = 0; 
    for(int j = 1; j <= x; j++) { 
        deque<pair<int, int64_t>>dq; 
        dq.push_back({j - 1, dyn[j - 1][j - 1]}); 
        for(int i = j; i <= n; i++) { 
            while(dq.size() && dq.front().first < i - k) dq.pop_front(); 
            dyn[i][j] = dq.front().second + a[i]; 
            while(dq.size() && dq.back().second <= dyn[i][j - 1]) dq.pop_back();
            dq.push_back({i, dyn[i][j - 1]}); 
        }
    }
    int64_t ret = -1; 
    for(int i = 0; i < k; i++) ret = max(ret, dyn[n - i][x]); 
    cout << ret << '\n'; 
    return 0; 
}