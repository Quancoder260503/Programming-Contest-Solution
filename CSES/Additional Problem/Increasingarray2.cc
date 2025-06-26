#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int n; 
    cin >> n; 
    priority_queue<int>pq; 
    int64_t ret = 0; 
    for(int i = 0, x; i < n; i++) { 
        cin >> x; 
        pq.push(x); 
        ret += pq.top() - x; 
        pq.pop();
        pq.push(x); 
    }
    cout << ret << '\n'; 
    return 0;
}