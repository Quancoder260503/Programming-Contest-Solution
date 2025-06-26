#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e5 + 2;

int trs[maxf], mark[maxf], dist[maxf], fa[maxf]; 
vector<int>g[maxf]; 


int dfs(int u, int p)
{
    trs[u] = 1; 
    for(auto v : g[u]) if(v != p && !mark[v])
    {
        trs[u] += dfs(v, u); 
    }
    return trs[u]; 
}

int centroid(int u, int p, int sz)
{
    for (auto v : g[u]) if (v != p and !mark[v])
    {
        if (trs[v] > sz / 2) return centroid(v, u, sz);
    }
    return u;
}

map<vector<int>, int>mp;
int nodes, ans, N;  

// encode the tree rooted at node u 

void dfs2(int u, int p, vector<int>&vis)
{
    fa[u] = p; 
    vis.push_back(u);
    for(auto v : g[u]) if(v != p && !mark[v])
    {
        dist[v] = dist[u] + 1; 
        dfs2(v, u, vis); 
    }
    return; 
}
int encode(int u, int p)
{
    vector<int>ret; 
    for(auto v : g[u]) if(v != p && !mark[v])
    {
        ret.push_back(encode(v, u)); 
    }
    sort(ret.begin(), ret.end()); 
    if(mp.count(ret) == 0) mp[ret] = nodes++; 
    return mp[ret]; 
}

void getcode(int root, vector<pair<int, int>>&ret)
{
    vector<int>vis, nvis; 
    dist[root] = 0; 
    dfs2(root, -1, vis);
    sort(vis.begin(), vis.end(), [&](int i, int j){ return dist[i] < dist[j]; }); 
    int c = vis.back();
    dist[c] = 0; 
    dfs2(c, -1, nvis);
    sort(vis.begin(), vis.end(), [&](int i, int j){ return dist[i] < dist[j];});
    int cc = vis.back(); 
    vector<int>path; 
    while(cc != c)
    {
        path.push_back(cc); 
        cc = fa[cc]; 
    }
    path.push_back(cc); 
    int sz = path.size(); 
    c = path[sz / 2]; 
    pair<int, int>res = {-1, -1};
    res.first = encode(c, -1); 
    if(sz % 2 == 0)
    {
        c = path[sz / 2 - 1];
        res.second = encode(c, -1); 
    }
    ret.push_back(res); 
    return;  
}

void solve(int u, int p)
{
    int n = dfs(u, p);
    int c = centroid(u, p, n);
    mark[c] = 1; 
    nodes = 0; 
    vector<pair<int, int>>ret; 
    for (auto v : g[c])
    {
        getcode(v, ret); 
    }
    sort(ret.begin(), ret.end());
    int chk = 1; 
    for(int i = 0; i + 1 < ret.size(); i++)
    {
        int curr = 0;
        curr = curr || (ret[i + 1].first  == ret[i].first   && ret[i].first  != -1); 
        curr = curr || (ret[i + 1].second == ret[i].first   && ret[i].first  != -1); 
        curr = curr || (ret[i + 1].first  == ret[i].second  && ret[i].second != -1); 
        curr = curr || (ret[i + 1].second == ret[i].second  && ret[i].second != -1); 
        chk = chk & curr; 
    }
    if(chk) ans = max(ans, (int) ret.size());  
    return; 
}

int main(void)
{
    cin >> N; 
    for(int i = 0; i < N - 1; i++)
    {
        int U, V; 
        cin >> U >> V;
        g[U].push_back(V); 
        g[V].push_back(U); 
    }
    ans = -1; 
    solve(1, 0); 
    cout << ans << '\n'; 
    return 0; 
}