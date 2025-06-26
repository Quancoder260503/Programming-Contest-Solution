#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, m; 
    cin >> n; 
    vector<int>r(n), c(n);
    for(int i = 0; i < n; i++) { 
        cin >> r[i]; 
    } 
    for(int i = 0; i < n; i++) { 
        cin >> c[i]; 
    }
    vector<int>sr = r, sc = c; 
    vector<vector<int>>ret(n, vector<int>(n)); 
    for(int i = 0; i < n; i++) { 
        for(int j = 0; j < n; j++) { 
            int m = min(r[i], c[j]);
            ret[i][j] = m; 
            r[i] = r[i] - m;
            c[j] = c[j] - m; 
        } 
    }
    int check = true; 
    for(int i = 0; i < n; i++) { 
        int sum = 0; 
        for(int j = 0; j < n; j++) sum += ret[i][j]; 
        check &= (sum == sr[i]); 
        sum = 0; 
        for(int j = 0; j < n; j++) sum += ret[j][i]; 
        check &= (sum == sc[i]); 
    }
    if(!check) { 
        cout << "-1\n"; 
        return 0; 
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) { 
          cout << ret[i][j] << " "; 
        }
        cout << '\n'; 
    } 
    return 0; 
}