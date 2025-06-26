#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(0); 
    int tc; 
    cin >> tc; 
    while(tc--) { 
        vector<vector<int64_t>>T(2, vector<int64_t>(3)); 
        cin >> T[0][0] >> T[1][0] >> T[0][1] >> T[1][1] >> T[0][2] >> T[1][2];
        vector<pair<int, int>>ret; 
        for(int x = 1; x <= 10000; x++) { 
            if((T[0][2] - x * T[0][0]) % T[0][1] > 0) continue; 
            if((T[1][2] - x * T[1][0]) % T[1][1] > 0) continue; 
            int ya = (T[0][2] - x * T[0][0]) / T[0][1];
            int yb = (T[1][2] - x * T[1][0]) / T[1][1]; 
            if(ya == yb && ya > 0) { 
                ret.push_back({x, ya}); 
            }
        }
        if(ret.size() == 1) cout << ret[0].first << " " << ret[0].second << '\n'; 
        else cout << "?\n"; 
    }
    return 0; 
}