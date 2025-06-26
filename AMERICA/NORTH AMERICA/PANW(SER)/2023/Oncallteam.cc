#include "bits/stdc++.h"

using namespace std;

const int maxf = 23;

vector<int>g[maxf];

int main(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        char c;
        cin >> c;
        if(c == '1') g[j].push_back(i); 
    }
    int ret = 0;
    vector<int> chk(1 << m, 0), ctr(m + 1, 0), cnt(m + 1, 0);
    for (int mask = 0; mask < (1 << m); mask++) {
        int x = __builtin_popcount(mask);
        cnt[x]++;
        set<int>cc; 
        bool stop = false; 
        for (int i = 0; i < m; i++) if (mask & (1 << i)) {
            for(auto v : g[i]) { 
                cc.insert(v); 
                if(cc.size() >= x) stop = true;
                if(stop) break; 
            } 
            if(stop) break; 
        }
        chk[mask] = (cc.size() >= x);
        for (int i = 0; i < m; i++) if (mask & (1 << i)) {
            chk[mask] &= chk[mask ^ (1 << i)];
        }
        if (chk[mask]) ctr[x]++;
    }
    for (int i = 0; i <= m; i++) if (chk[i] && ctr[i] >= cnt[i]) {
        ret = max(ret, i);
    }
    cout << ret << '\n';
    return 0;
}