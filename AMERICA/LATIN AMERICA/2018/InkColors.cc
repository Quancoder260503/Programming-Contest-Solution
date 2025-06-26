#include "bits/stdc++.h"

using namespace std; 

const int maxf = 1e5 + 10; 

vector<int>g[maxf]; 
int ctr[maxf], vis[maxf], h[maxf], fa[maxf], mid[maxf];  

void doit(int u, int p)
{
    for(auto v : g[u])
    {
        if(v == p) continue; 
        h[v] = h[u] + 1; 
        doit(v, u); 
    }
    return; 
}

int main(void)
{
    int N; 
    while(cin >> N)
    {
        for(int i = 1; i < N; i++)
        { 
            cin >> fa[i]; 
            fa[i]--; 
            g[fa[i]].push_back(i);
            g[i].push_back(fa[i]); 
        }
        int ret = 0;
        doit(0, -1); 
        vector<int>ord(N); 
        iota(ord.begin(), ord.end(), 0); 
        auto cmp = [&](int a, int b){return h[a] > h[b]; };
        sort(ord.begin() + 1, ord.end(), cmp);
        for(int i = 1 ; i < N; i++)
        {
            int u = ord[i]; 
            int sz = g[u].size() - 1 - ctr[u]; 
            int chk = 0; 
            for(auto v : g[u]) if(v != fa[u])
            {
                chk = chk | mid[v]; 
            }
            if(chk && sz > 2)
            {
                ret++; 
                ctr[fa[u]]++; 
            }
            else if(sz > 1) mid[u] = 1;
           // cout << u + 1 << " " << chk << " " << " " << sz << " " << mid[u] << '\n';
        }
        cout << ret << '\n'; 
    }
    return 0; 
}