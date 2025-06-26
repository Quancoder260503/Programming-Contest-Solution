#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    map<string, int>idx; 
    vector<string>s(16); 
    vector<char>g(16); 
    int red = 0, blue = 0, as = 0;
    for (int i = 0; i < 16; i++) {
        cin >> s[i];
        idx[s[i]] = i;
    }
    for (int i = 0; i < 16; i++) {
        cin >> g[i];
        if(g[i] == '.') continue; 
        (g[i] == 'B' ? blue : (g[i] == 'R' ? red : as)) |= (1 << i); 
    }
    int n; 
    cin >> n;
    vector<vector<string>> h(n);
    string word; 
    for (int i = 0, x; i < n; i++) {
        cin >> word >> x;
        h[i].resize(x); 
        for (int j = 0; j < x; j++) {
            cin >> h[i][j]; 
        }
        sort(h[i].begin(), h[i].end()); 
        for(auto &x : h[i]) { 
            //cout << x << "[" << idx[x] << "]" << " "; 
        }
        //cout << '\n'; 
    }
    vector<char>col = {'B', 'R'}; 
    vector<vector<int>>dyn(2, vector<int>(1 << 16, -1)); 
    function<int(int, int)>doit = [&](int x, int mask) -> int { 
        if(dyn[x][mask] != -1) return dyn[x][mask]; 
        int &ret = dyn[x][mask];
        for(int i = 0; i < n; i++) { 
            int hmask = mask, flag = true; 
            for(auto v : h[i]) if(!(hmask & (1 << idx[v]))) {
                hmask |= (1 << idx[v]); 
                if((hmask & blue) == blue) { 
                    if(x == 0) return ret = true; 
                    else flag = false; 
                }
                if((hmask & red)  == red ) { 
                    if(x == 1) return ret = true; 
                    else flag = false; 
                }  
                if(g[idx[v]] != col[x]) break;
            }
            if(!flag || (hmask & as) || mask == hmask) continue; 
            if(doit(x ^ 1, hmask) ^ 1) return ret = true; 
        }
        return ret = false; 
    }; 
    cout << (doit(0, 0) ? "Alice" : "Bob") << '\n'; 
    return 0;
}