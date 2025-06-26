#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e5 + 2; 

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i]; 
    }
    vector<vector<int>> p(n + 1);
    for (int i = 1; i <= n; i++) for (int j = i; j <= n; j += i) {
        p[j].push_back(i); 
    }
    vector<int>vis(n + 1, true);
    auto marked = [&](int x, int y) { 
        for (auto d : p[x]) if(d >= y) {
            vis[d] = false;
        }
        return;  
    };
    auto solve = [&](bool invert) {
        int inv = -1, d = -1, p = -1, state = 0; 
        for (int i = 1; i < n; i++) {
            int pre = (d == -1 ? a[i] : a[d]); 
            if(a[i] == -1 || a[i] == pre) {
                if (state == 0) state = 1;
                else if (state == 1 || state == 2) state = 2; 
                else if (state == 3) state = 3; 
            }
            else if(a[i] > pre) {
                if (state <= 2) state = 1; 
                else state = 4; 
            }
            else if(a[i] < pre) {
                if (state == 0 || state == 4) state = 4; 
                else state = 3; 
            }
            if(state != 2 && state != 3) { 
                if(!invert) marked(i + 1, i + 1); 
                else        marked(n - i - 1, i + 1); 
            }
            if(!invert && a[i] != -1 && a[i - 1] != -1) { 
                if(a[i] > a[i - 1])      marked(i + 1, 0); 
                else if(a[i] < a[i - 1]) marked(i - 1, 0); 
            }
            if(a[i] != -1) { 
                if(d != -1 && a[d] > a[i]) {
                    p = d; 
                }
                else if(d != -1 && p != -1 && a[i] > a[d]) {
                    inv = p; 
                }
                d = i; 
            }
            if(inv != -1) {
                if (!invert) marked(i + 1, i - inv + 1); 
                else         marked(n - i - 1, i + 1); 
            }
        }
    };
    solve(false);
    reverse(a.begin(), a.end());
    solve(true);
    int ret = false; 
    for (int i = 3; i <= n; i++) ret |= vis[i];
    cout << (ret ? 'Y' : 'N') << '\n'; 
    return 0;
}