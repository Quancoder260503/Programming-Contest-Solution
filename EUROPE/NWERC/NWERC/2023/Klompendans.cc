#include "bits/stdc++.h"

using namespace std;

using vi = vector<int>; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b, c, d;
    cin >> n >> a >> b >> c >> d;
    vector<vector<vi>>vis(n, vector<vi>(n, vi(2, false))); 
    queue<tuple<int, int, int>>q; 
    q.push({0, 0, 0});
    q.push({0, 0, 1}); 
    vis[0][0][0] = vis[0][0][1] = true; 
    vector<pair<int, int>>moveA = {{a, -b}, {a, b}, {-a, -b}, {-a, b}, {b, -a}, {b, a}, {-b, a}, {-b, -a}}; 
    vector<pair<int, int>>moveB = {{c, -d}, {c, d}, {-c, -d}, {-c, d}, {d, -c}, {d, c}, {-d, c}, {-d, -c}}; 
    while(q.size()) { 
        auto [x, y, type] = q.front();
        q.pop(); 
        auto move = (type == 0 ? moveA : moveB);
        for(auto [dx, dy] : move) { 
            int kx = x + dx, ky = y + dy; 
            if(0 <= kx && kx < n && 0 <= ky && ky < n && !vis[kx][ky][type ^ 1]) { 
                vis[kx][ky][type ^ 1] = true; 
                q.push({kx, ky, type ^ 1}); 
            }
        }
    } 
    int ret = 0; 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        ret += (vis[i][j][0] | vis[i][j][1]);
    }
    cout << ret << '\n'; 
    return 0;
}
