#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; 
    cin >> n; 
    vector<vector<int>>M(n + 1, {0, 0, 0}); 
    vector<pair<int, int>>moves;  
    vector<int>zeros; 
    auto move = [&](int s, int e) { 
        moves.push_back({s + 1, e + 1}); 
        int ns, ne; 
        for(ns = 2; !M[s][ns]; ns--); 
        for(ne = 0; M[e][ne]; ne++); 
        swap(M[s][ns], M[e][ne]); 
        for(auto& x : zeros) if(x == e) { x = s; break; }
        return; 
    }; 
    function<void(int, int, int, int)> smove = [&](int s, int ns, int e, int ne) -> void { 
        if(ns == 0 && ne == 1) { 
            int m = e + 1 + (s == e + 1); 
            while(!M[m][1]) move(s, m); 
            smove(s, ns, m, 2);
            smove(m, 2, e, ne); 
            return;  
        }
        while(M[e][ne]) { 
            for(auto x : zeros) if(x != s && x != e) { move(e, x); break; }
        }
        while(ns < 2 && M[s][ns + 1]) { 
            for(auto x : zeros) if(x != s && x != e) { move(s, x); break; }
        }
        move(s, e); 
        return; 
    };
    for(int i = 0; i <= n; i++) {
        for(auto &x : M[i]) { 
            cin >> x; 
            if(!x) zeros.push_back(i); 
        }
    }
    for(int i = 0; i < n; i++) { 
        if(!M[i][0]) move(i + 1, i);
        int c = M[i][0]; 
        for(int j = 1; j < 3; j++) if(M[i][j] != c) { 
            for(int nj = 2; nj >= 0; nj--) for(int ni = i + 1; ni <= n; ni++) if(M[ni][nj] == c) { 
                smove(ni, nj, i, j);
                goto done; 
            }
        done:; 
        }
    }
    cout << sz(moves) << '\n'; 
    for(auto [s, e] : moves) cout << s << " " << e << '\n'; 
    return 0;
}