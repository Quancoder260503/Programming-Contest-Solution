#include "bits/stdc++.h"

using namespace std;

struct Matching
{
    int n;
    vector<vector<int>> ke;
    vector<int> seen;
    vector<int> matchL, matchR;
    int iteration;

    Matching(int _n) : n(_n), ke(_n), seen(_n, false), matchL(_n, -1), matchR(_n, -1), iteration{0}
    {
    }

    void addEdge(int u, int v)
    {
        ke[u].push_back(v);
    }

    bool dfs(int u)
    {
        seen[u] = iteration;
        for (int v : ke[u])
        {
            if (matchR[v] < 0)
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        for (int v : ke[u])
        {
            if (seen[matchR[v]] != iteration && dfs(matchR[v]))
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    int match()
    {
        int res = 0;
        int newMatches = 0;
        do
        {
            iteration++;
            newMatches = 0;
            for (int u = 0; u < n; u++)
            {
                if (matchL[u] < 0 && dfs(u))
                    ++newMatches;
            }
            res += newMatches;
        } while (newMatches > 0);
        return res;
    }
};
// }}}

const int maxf = 102; 

vector<int>g[maxf];
vector<int>g2[maxf];
int f[maxf][maxf], n, m;

void dfs(int u, int u2, int p, int p2) { 
    if(f[u][u2] != -1) return; 
    f[u][u2] = false; 
    int ca = g[u].size()  - (p >= 0); 
    int cb = g2[u2].size() - (p2 >= 0); 
    if(cb == 0) { 
        f[u][u2] = true; 
        return; 
    }
    if(ca >= cb) {
        for (auto v : g[u]) if (v != p) {
            for (auto v2 : g2[u2]) if (v2 != p2) {
                dfs(v, v2, u, u2);
            }
        }
        Matching mc(n + m);
        for (auto v : g[u]) if (v != p) {
            for (auto v2 : g2[u2]) if (v2 != p2 && f[v][v2]) {
                //cout << u << " " << u2 << " " << v << " " << v2 << '\n'; 
                mc.addEdge(v, v2);
            }
        } 
        int ret = mc.match();
        f[u][u2] = (ret == cb);
    }
    return; 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for(int i = 0, u, v; i < n - 1; i++) { 
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u); 
    }
    cin >> m; 
    for(int i = 0, u, v; i < m - 1; i++) { 
        cin >> u >> v; 
        g2[--u].push_back(--v);
        g2[v].push_back(u); 
    }
    for(int i = 0; i < n; i++) {
        memset(f, -1, sizeof(f));
        dfs(i, 0, -1, -1);
        if(f[i][0]) { 
            cout << 'Y' << '\n';  
            return 0; 
        } 
    }
    cout << 'N' << '\n'; 
    return 0;
}