#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int n; 
    cin >> n; 
    vector<int>arr(n); 
    for(int i = 0; i < n; i++)  {
        cin >> arr[i]; 
    } 
    vector<int>ret; 
    for(int i = 1; i < n; i++) { 
        if(n % i == 0) { 
            vector<pair<int, int>>chunks(n / i, {-100, 100}); 
            for(int j = 0; j < n; j += i) { 
                for(int k = j; k < j + i; k++) {
                    chunks[j / i].first  = max(chunks[j / i].first,  arr[k]); 
                    chunks[j / i].second = min(chunks[j / i].second, arr[k]);  
                }
                ///cout << j << " " << j + i << " " << chunks[j / i].first << " " << chunks[j / i].second << '\n'; 
            }
            int sz = n / i; 
            int flag = true; 
            for(int j = 0; j < sz; j++) for(int k = 0; k < j; k++) { 
                if(chunks[k].first > chunks[j].second) { 
                    flag = false; 
                    break; 
                }
            }
            if(flag) ret.push_back(sz); 
        }
    }
    if(ret.empty()) { 
        cout << -1 << '\n'; 
        return 0;
    } 
    sort(ret.begin(), ret.end()); 
    for(auto r : ret) cout << r << '\n'; 
    return 0;  
}