#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); 
    vector<vector<char>> g(6, vector<char>(6));
    vector<vector<int>> vis(6, vector<int>(6));
    for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) {
        cin >> g[i][j];
    }
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
    int chk = true;
    vector<vector<int>> mat = {{4, 1, 5, 3, 2, 0}, {3, 0, 1, 2, 4, 5}, {5, 1, 4, 3, 0, 2}, {1, 2, 3, 0, 4, 5}}; 
    auto transform = [&](int x, int y) {
        int ret = 0; 
        for (int i = 0; i < 6; i++) {
            ret |= (1 << i) * ((x >> mat[y][i]) & 1); 
        }
        return ret;
    };
    function<int(int, int)> doit = [&](int rx, int ry) {
        vector<int> ret;
        ret.push_back(4);
        vis[rx][ry] = true; 
        for (int k = 0; k < 4; k++) {
            int kx = dx[k] + rx, ky = dy[k] + ry; 
            if(0 <= kx && kx < 6 && 0 <= ky && ky < 6 && !vis[kx][ky] && g[kx][ky] == '#') {
                ret.push_back(transform(doit(kx, ky), k)); 
            }
        }
        int res = 0; 
        for(auto r : ret) {
            if(r & res) {
                chk = false; 
            }
            res |= r; 
        }
        return res;
    };
    for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) if(g[i][j] == '#') {
        doit(i, j);
        cout << (chk ? "can fold" : "cannot fold") << '\n';
        return 0; 
    }
    return 0;
}