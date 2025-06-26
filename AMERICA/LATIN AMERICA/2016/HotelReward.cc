#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N, K; 
    cin >> N >> K; 
    vector<int>h(N);
    for(int i = 0; i < N; i++) { 
        cin >> h[i]; 
    } 
    priority_queue<int, vector<int>, greater<int>>pq; 
    int64_t ret = 0; 
    for(int i = 0; i < N; i++) { 
        ret += h[i]; 
        if((i + 1) % (K + 1) == 0) { 
            pq.push(h[i]); 
        }
        else if(pq.size() && pq.top() < h[i]) { 
            pq.pop(); 
            pq.push(h[i]); 
        }
    }
    while(pq.size()) { 
        ret = ret - pq.top(); 
        pq.pop(); 
    }
    cout << ret << '\n'; 
    return 0; 
}