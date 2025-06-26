#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int n; 
    cin >> n;
    vector<int>sz(n);  
    vector<vector<int>>g(n); 
    for(int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u); 
    }
    function<void(int, int)>dfs = [&](int u, int p) -> void
    {
        sz[u] = 1; 
        for(auto v : g[u])
        {
            if(v == p) continue;
            dfs(v, u); 
            sz[u] += sz[v];  
        }
        return; 
    }; 
    dfs(0, -1); 
    vector<complex<double>>ret(n); 
    function<void(int, int, complex<double>, double, double)> dfs2 = [&](int u, int fa, complex<double>p, double l, double r) -> void 
    {
        ret[u] = p; 
        double ang = 1.0 * (r - l) / sz[u]; 
        double st;
        st = l;  
        for(auto v : g[u]) { 
            if(v == fa) continue; 
            double nxt = st + ang * sz[v];  
            dfs2(v, u, p + polar(1.0, (st + nxt) / 2.0), st, nxt);
            st = nxt;  
        }
        return; 
    };
    dfs2(0, -1, 0, 0, acos(-1)); 
    cout << fixed << setprecision(10); 
    for(int i = 0; i < n; i++) cout << ret[i].real() << " " << ret[i].imag() << '\n'; 
    return 0;
}