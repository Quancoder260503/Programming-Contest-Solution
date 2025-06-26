#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int tc; 
    cin >> tc; 
    while(tc--) { 
        int n; 
        cin >> n; 
        priority_queue<int64_t, vector<int64_t>, greater<int64_t>>pq; 
        for(int i = 0, x; i < n; i++) { 
            cin >> x;
            pq.push(x); 
        }
        int64_t ret = 0; 
        while(pq.size() > 1) { 
            int64_t x = pq.top();
            pq.pop();
            int64_t y = pq.top();
            pq.pop(); 
            ret += (x + y); 
            pq.push(x + y);  
        }
        cout << ret << '\n'; 
    }
    return 0;
}