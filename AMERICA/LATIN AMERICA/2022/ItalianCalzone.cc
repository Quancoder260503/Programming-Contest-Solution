#include "bits/stdc++.h"

using namespace std;

#define x first
#define y second 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, m; 
    cin >> n >> m; 
    vector<vector<int>>g(n, vector<int>(m));  
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){ 
        cin >> g[i][j]; 
        --g[i][j]; 
    }   
    const int dx[4] = {0, 0, -1, 1}; 
    const int dy[4] = {1, -1, 0, 0}; 
    vector<int>vis(n * m); 
    int res = 0; 
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) { 
        fill(vis.begin(), vis.end(), false); 
        using T = pair<int, pair<int, int>>;
        priority_queue<T, vector<T>, greater<T>>pq; 
        vis[g[i][j]] = true; 
        pq.push({g[i][j], {i, j}}); 
        int ret = 0; 
        while(pq.size()) { 
            auto [u, p] = pq.top();
            pq.pop();
            ret++; 
            for(int k = 0; k < 4; k++) { 
                int kx = p.x + dx[k], ky = p.y + dy[k]; 
                if(0 <= kx && kx < n && 0 <= ky && ky < m && !vis[g[kx][ky]] && g[kx][ky] > g[p.x][p.y]) { 
                    vis[g[kx][ky]] = true; 
                    pq.push({g[kx][ky], {kx, ky}}); 
                }
            }
        }
        res = max(ret, res); 
    }
    cout << res << '\n'; 
    return 0; 
}