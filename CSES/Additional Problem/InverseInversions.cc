#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int64_t n, k;
    cin >> n >> k;
    deque<int>dq; 
    vector<int>ret;
    for(int i = 1; i <= n; i++) { 
        dq.push_back(i); 
    }
    for(int inv = n - 1; inv >= 0; inv--) { 
        if(inv > k) { 
            ret.push_back(dq.front()); 
            dq.pop_front(); 
        }
        else { 
            ret.push_back(dq.back()); 
            dq.pop_back(); 
            k = k - inv; 
        }
    }
    for(auto r : ret) cout << r << " "; 
    cout << '\n'; 
    return 0;
}