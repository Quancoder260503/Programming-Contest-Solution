#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int) x.size()

int main(void) {
    int mod; 
    string s; 
    cin >> s >> mod;
    s = " " + s;   
    int n = sz(s); 
    vector<vector<int>>dyn(n, vector<int>(mod, -1)); 
    vector<vector<int>>to(n, vector<int>(mod, -1)); 
    function<int(int, int)>go = [&](int i, int j) -> int {
        if(i == n - 1) return (j == 0); 
        if(dyn[i][j] != -1) return dyn[i][j]; 
        int ret = 0; 
        if(s[i + 1] == '?') {
            for(int k = (i == 0); k < 10; k++) { 
                if((ret = go(i + 1, (10 * j + k) % mod))) {
                    to[i][j] = k; 
                    break; 
                }
            }
        }
        else { 
            ret = go(i + 1, (10 * j + s[i + 1] - '0') % mod);
            to[i][j] = s[i + 1] - '0'; 
        }
        return dyn[i][j] = ret; 
    }; 
    if(!go(0, 0)) { 
        cout << "*" << '\n'; 
    }
    else { 
        function<void(int, int)>track = [&](int i, int j) -> void {
            if(i == n - 1) return; 
            cout << to[i][j]; 
            track(i + 1, (10 * j + to[i][j]) % mod); 
        };
        track(0, 0); 
        cout << '\n'; 
    }
    return 0; 
}