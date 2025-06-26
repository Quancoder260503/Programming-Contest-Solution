#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    int n, m; 
    cin >> n >> m; 
    map<int, int>ctr; 
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) { 
        ctr[i + j]++; 
    }
    vector<int>ret; 
    int res = 0; 
    for(int i = 2; i <= n + m; i++) { 
        if(res < ctr[i]) { 
            res = ctr[i]; 
            ret.clear();
            ret.push_back(i); 
        }
        else if(res == ctr[i]) { 
            ret.push_back(i); 
        }
    }
    sort(ret.begin(), ret.end()); 
    for(auto c : ret) cout << c << '\n'; 
    return 0; 
}