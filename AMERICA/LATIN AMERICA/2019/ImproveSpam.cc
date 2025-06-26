#include "bits/stdc++.h"

using namespace std;
const int MAX = 2e5 + 2; 
const int mod = 1e9 + 7; 

bool vis[MAX]; 
vector<int>adj[MAX];
vector<int>radj[MAX]; 
int64_t dyn[MAX];
vector<int>ret;
int N, M;
void doit(int u)
{
    vis[u] = 1; 
    dyn[u] = radj[u].size(); 
    for(auto v : radj[u]) ret.push_back(v); 
    for(auto v : adj[u]) 
    {
        if (!vis[v]) doit(v);
        dyn[u] = (dyn[u] + dyn[v]) % mod;
    }
    return; 
}
int main(void)
{
    while(cin >> N >> M)
    {
        for(int i = 1; i <= M; i++)
        {
            int sz; 
            cin >> sz;
            for(int j = 0; j < sz; j++)
            {
                int v; 
                cin >> v;
                if(v <= M) adj[i].push_back(v);  
                if(v > M) radj[i].push_back(v); 
            }
        }
        doit(1); 
        sort(ret.begin(), ret.end()); 
        ret.erase(unique(ret.begin(), ret.end()), ret.end()); 
        cout << dyn[1] << " " << ret.size() << '\n'; 
    }
    return 0; 
}