#include "bits/stdc++.h"
using namespace std;
#define lint long long
const lint INF = 1e18;
signed main(void)
{
    int n;
    lint K;
    while (cin >> n >> K)
    {
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        function<pair<vector<lint>, vector<lint>>(int, int)> doit;
        doit = [&](int u, int p) -> pair<vector<lint>, vector<lint>>
        {
            vector<lint>reta{0, 1};
            vector<lint>retb{0, 0}; 
            for(auto v : adj[u])
            {
                if(v == p) continue; 
                auto [va, vb] = doit(v, u); 
                retb.resize(retb.size() + va.size() - 1); 
                for(int i = 1; i < va.size(); i++) retb[i] += va[i]; 
                for(int i = 1; i < vb.size(); i++) retb[i] += vb[i]; 
                for(int i = 0; i < retb.size(); i++) retb[i] = min(retb[i], INF); 
                vector<lint>at(reta.size() + va.size() - 1);
                for(int i = 1; i < reta.size(); i++) at[i] = reta[i]; 
                for(int i = 1; i < reta.size(); i++)
                {
                    for(int j = 1; j < va.size(); j++)
                    {
                        if(at[i + j] > INF) at[i + j] = min(at[i + j], INF); 
                        else at[i + j] = min( INF,  at[i + j] + 1LL * reta[i] * va[j]);
                    }
                }
                reta.swap(at);
            }
            return {reta, retb}; 
        };
        auto [reta, retb] = doit(0, -1); 
        int ret = 1; 
        while(K > reta[ret] + retb[ret])
        {
            K = K - reta[ret] - retb[ret]; 
            ret++; 
        }
        cout << (ret > n ? -1 : ret) << '\n'; 
    }
    return 0;
}