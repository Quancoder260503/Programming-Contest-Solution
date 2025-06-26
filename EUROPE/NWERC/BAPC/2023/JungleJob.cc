#include "bits/stdc++.h"

using namespace std; 

const int maxf = 1002;
const int mod = 1e9 + 7;

vector<int64_t>dyn[maxf]; 
vector<int>g[maxf]; 
int64_t ctr[maxf]; 

#define sz(x) (int) x.size()

vector<int64_t>combine(vector<int64_t>a, vector<int64_t>b)
{
    vector<int64_t>ret(sz(a) + sz(b)); 
    for(int i = 0; i < sz(a); i++) for(int j = 0; j < sz(b); j++)
    {
        ret[i + j] += 1LL * a[i] * b[j] % mod;
        ret[i + j] %= mod;
    }
    return ret; 
}

void dfs(int u)
{
    dyn[u].push_back(0); 
    dyn[u].push_back(1);  
    for(auto v : g[u])
    {
        dfs(v); 
        dyn[v][0] = 1; 
        dyn[u] = combine(dyn[u], dyn[v]); 
    }
    for(int i = 0; i < dyn[u].size(); i++) 
    {
        ctr[i] += dyn[u][i];
        ctr[i] %= mod; 
    }
    return;
}

int main(void)
{
    int n;
    cin >> n;
    for(int i = 2; i <= n; i++)
    {
        int p;
        cin >> p;
        g[++p].push_back(i); 
    }
    dfs(1); 
    for(int i = 1; i <= n; i++) cout << ctr[i] << '\n'; 
    return 0; 
}