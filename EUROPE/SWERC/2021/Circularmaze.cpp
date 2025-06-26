#include "bits/stdc++.h"

using namespace std;

const int maxf = 750; 

int marked[maxf][maxf], rmarked[maxf][maxf]; 

int main(void) {
    int n, tc; 
    cin >> tc; 
    while(tc--) {
        cin >> n; 
        memset(rmarked, 0, sizeof(rmarked)); 
        memset(marked, 0, sizeof(marked)); 
        vector<int>par(360 * 22); 
        iota(par.begin(), par.end(), 0); 
        function<int(int)>find = [&](int u) { 
            return (u == par[u] ? u : par[u] = find(par[u])); 
        }; 
        auto merge = [&](int a, int b) { 
            if(find(a) == find(b)) return; 
            par[find(b)] = find(a); 
            return; 
        }; 
        auto unite = [&](int r1, int x1, int r2, int x2) { 
            x1 %= 360; 
            x2 %= 360;
            merge(360 * r1 + x1, 360 * r2 + x2); 
            return; 
        }; 
        function<void(int, int, int)>join = [&](int p, int ra, int rb) {
            if (ra > rb) {
                join(p, 0, rb);
                join(p, ra, 360);
                return;
            }
            for (int i = ra; i < rb; i++) {
                marked[p][i] = 1;
            }
            return;
        }; 
        for(int i = 0; i < 360; i++) unite(20, i, 20, i + 1);
        for(int i = 0; i < n; i++) { 
            char c; 
            cin >> c; 
            if(c == 'C') {
                int r, t1, t2; 
                cin >> r >> t1 >> t2; 
                join(r, t1, t2); 
            }
            else { 
                int r1, r2, t; 
                cin >> r1 >> r2 >> t; 
                for(int j = r1; j < r2; j++) rmarked[j][t] = 1; 
            }
        }
        for(int i = 0; i < 20; i++) for(int j = 0; j < 360; j++) { 
            if(!rmarked[i][(j + 1) % 360]) { 
                unite(i, j, i, j + 1); 
            }
            if(!marked[i + 1][j]) { 
                unite(i, j, i + 1, j); 
            }
        }
        cout << (find(0) == find(20 * 360) ? "YES" : "NO") << '\n'; 
    }
    return 0;
}