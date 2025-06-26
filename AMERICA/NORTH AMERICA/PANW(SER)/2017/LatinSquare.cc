#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<vector<int>>g(n, vector<int>(n)); 
    char c; 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) { 
        cin >> c; 
        if(isdigit(c)) g[i][j] = c - '0'; 
        else g[i][j] = c - 'A' + 10; 
    }
    for(int i = 0; i < n; i++) { 
        map<int, int>mp; 
        for(int j = 0; j < n; j++) { 
            mp[g[i][j]]++; 
        }
        for(const auto &[u, v] : mp) { 
            if(v > 1) { 
                cout << "No\n";
                exit(0); 
            }
        }
        mp.clear(); 
        for(int j = 0; j < n; j++) { 
            mp[g[j][i]]++; 
        }
        for(const auto &[u, v] : mp) { 
            if(v > 1) { 
                cout << "No\n";
                exit(0); 
            }
        }
    }
    vector<int>top, left; 
    for(int i = 0; i < n; i++) top.push_back(g[0][i]); 
    for(int i = 0; i < n; i++) left.push_back(g[i][0]); 
    if(is_sorted(top.begin(), top.end()) && is_sorted(left.begin(), left.end())) { 
        cout << "Reduced\n"; 
    }
    else { 
        cout << "Not Reduced\n"; 
    }
    return 0; 
}