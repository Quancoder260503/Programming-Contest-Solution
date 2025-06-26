#include "bits/stdc++.h"

using namespace std; 

#define x first
#define y second 

const int maxf = 100; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int m, r, c;
    string s; 
    cin >> m;
    for(int i = 0; i < m; i++) { 
        cin >> s[i]; 
    }
    cin >> r >> c;
    map<int, map<int, int>>g; 
    for(int i = 1; i <= r; i++) for(int j = 1, x; j <= c; j++) { 
        cin >> x; 
        g[i][j] = x; 
    } 
    int ret = 0; 
    for(int i = -maxf; i < maxf; i++) for(int j = -maxf; j < maxf; j++) { 
        pair<int, int>pos = {i, j};  
        set<pair<int, int>>ms; 
        ms.insert(pos); 
        for(int k = 0; k < m; k++) {
            if(s[k] == 'u') pos.x--; 
            if(s[k] == 'l') pos.y--; 
            if(s[k] == 'r') pos.y++; 
            if(s[k] == 'd') pos.x++; 
            ms.insert(pos);  
        }
        int sum = 0; 
        for(auto [x, y] : ms) sum += g[x][y]; 
        ret = max(ret, sum); 
    } 
    cout << ret << '\n'; 
    return 0; 
}