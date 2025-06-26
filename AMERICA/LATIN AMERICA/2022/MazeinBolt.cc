#include "bits/stdc++.h"

using namespace std;

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, m;
    string nut;
    cin >> n >> m >> nut;
    vector<string> s(n);
    for(int i = 0; i < n; i++) { 
        cin >> s[i]; 
    }
    for(int r = 0; r < 2; r++) {
        vector<vector<int>>vis(n, vector<int>(m)), c(n, vector<int>(m)); 
        for (int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
            c[i][j] = true; 
            for(int k = 0; k < m; k++) if(nut[(j + k) % m] == '1') c[i][j] &= (s[i][k] == '0'); 
        }
        queue<pair<int, int>>q; 
        for(int i = 0; i < m; i++) if(c[0][i]) { 
            q.push({0, i});
        }
        while(q.size()) { 
            auto [x, y] = q.front();
            q.pop(); 
            for(int dir = -1; dir < 2; dir++) { 
                if(c[x][(y + dir + m) % m] && !vis[x][(y + dir + m) % m]) { 
                    vis[x][(y + dir + m) % m] = true; 
                    q.push({x, (y + dir + m) % m}); 
                }
            }
            if(x && c[x - 1][y] && !vis[x - 1][y]) { 
               vis[x - 1][y] = true; 
               q.push({x - 1, y}); 
            }
            if(x + 1 < n && c[x + 1][y] && !vis[x + 1][y]) { 
                vis[x + 1][y] = true; 
                q.push({x + 1, y}); 
            }
        }
        int ret = false;
        for(int i = 0; i < m; i++) ret |= vis[n - 1][i]; 
        if(ret) { 
            cout << 'Y' << '\n';
            return 0;
        }
        reverse(nut.begin(), nut.end()); 
    }
    cout << 'N' << '\n'; 
    return 0; 
}