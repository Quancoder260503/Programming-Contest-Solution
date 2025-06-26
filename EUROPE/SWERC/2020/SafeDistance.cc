#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10); 
    int x, y, n; 
    cin >> x >> y >> n;  
    vector<double>rx(n), ry(n);
    vector<tuple<double, int, int>>edge;  
    for(int i = 0; i < n; i++) { 
        cin >> rx[i] >> ry[i];
        edge.push_back({ry[i] * 2, n, i}); 
        edge.push_back({(x - rx[i]) * 2, n, i});
        edge.push_back({rx[i] * 2, n + 1, i}); 
        edge.push_back({(y - ry[i]) * 2, n + 1, i});  
    }
    for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) { 
        edge.push_back({hypot(rx[i] - rx[j], ry[i] - ry[j]), i, j});
    }
    sort(edge.begin(), edge.end());
    vector<int>djs(n + 2); 
    iota(djs.begin(), djs.end(), 0); 
    function<int(int)>F = [&](int x) {return x == djs[x] ? x : djs[x] = F(djs[x]); };
    for(auto [d, u, v] : edge) { 
        if(F(u) == F(v)) continue; 
        djs[F(u)] = F(v); 
        if(F(n) == F(n + 1)) { 
            cout << d / 2 << '\n';  
            break; 
        }
    }
    return 0;
}