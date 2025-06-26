#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int N, C; 
    cin >> N >> C;
    using T = pair<int, int>; 
    priority_queue<T, vector<T>, greater<T>>pq; 
    for(int i = 0; i < N; i++) { 
        pq.push({0, i});
    }
    for(int i = 0, x; i < C; i++) { 
        cin >> x; 
        auto [r, c] = pq.top();
        pq.pop(); 
        cout << c + 1 << " "; 
        pq.push({r + x, c}); 
    }
    return 0;
}