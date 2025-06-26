#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int n, k; 
    cin >> n >> k; 
    vector<int>rr(n);
    vector<pair<int, int>>arr;  
    for(int i = 0, x, y; i < n; i++) {
        cin >> x >> y; 
        arr.push_back({x, i + 1}); 
        arr.push_back({y, -(i + 1)}); 
        rr[i] = y; 
    }  
    sort(arr.begin(), arr.end()); 
    set<pair<int, int>>ms; 
    int ret = 0; 
    for(int i = 0; i < arr.size(); i++) { 
        auto [v, idx] = arr[i]; 
        if(idx < 0) { 
            if(ms.count({v, -idx})) { 
                ret++;
                ms.erase({v, -idx});  
            }
        }
        else { 
            if(ms.size() < k) { 
                ms.insert({rr[idx - 1], idx}); 
            }
            else {
                if(prev(ms.end())->first > rr[idx - 1]) {
                    ms.erase(prev(ms.end())); 
                    ms.insert({rr[idx - 1], idx});
                } 
            }
        }
    }
    cout << ret << '\n';
    return 0; 
}