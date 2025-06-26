#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; 
    cin >> n; 
    vector<int>a(n - 2), b(n + 1, 1); 
    for(int i = 0; i < n - 2; i++) { 
        cin >> a[i];
        b[a[i]]++; 
    } 
    priority_queue<int>pq; 
    for(int i = 1; i <= n; i++) if(b[i] == 1) pq.push(-i);
    for(int i = 0; i < n - 2; i++) { 
        int v = -pq.top(), u = a[i];
        pq.pop();
        b[u]--, b[v]--;  
        cout << u << " " << v << '\n'; 
        if(b[u] == 1) pq.push(-u); 
    }
    for(int i = 1; i <= n; i++) if(b[i]) cout << i << '\n'; 
    return 0;
}