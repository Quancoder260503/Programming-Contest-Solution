#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    int n, m; 
    cin >> n >> m;
    vector<vector<int>>vis(n, vector<int>(n));
    queue<pair<int, int>>q; 
    auto chk = [&](int x, int y) { 
        if(vis[x][y]) return; 
        vis[x][y] = true; 
        q.push({x, y});
    }; 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if((i + j) % 5 == 0) {
        chk(i, j); 
    }
    auto query = [&](int x, int y) {
        cout << x + 1 << " " << y + 1 << '\n';
        string ret; cin >> ret; 
        return (ret != "miss"); 
    }; 
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, -1, 1}; 
    int c = 5 * m;
    while(q.size()) { 
        auto [x, y] = q.front(); 
        q.pop(); 
        if(query(x, y)) { 
            if(--c == 0) break; 
            for(int d = 0; d < 4; d++) { 
                int kx = dx[d] + x, ky = dy[d] + y; 
                if(0 <= kx && kx < n && 0 <= ky && ky < n) { 
                    chk(kx, ky); 
                }
            }
        }
    } 
    return 0;
}
