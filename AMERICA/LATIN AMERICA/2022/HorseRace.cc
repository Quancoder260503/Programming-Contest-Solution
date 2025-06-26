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

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, q; 
    cin >> n; 
    map<string, int>to; 
    vector<string>s(n); 
    for(int i = 0; i < n; i++) { 
        cin >> s[i]; 
        to[s[i]] = i; 
    }
    vector<int>h(n, 0);
    vector<vector<int>>cand(n, vector<int>(n, true)); 
    cin >> q;  
    for(int i = 0, sz, c; i < q; i++) { 
        cin >> sz >> c; 
        --c; 
        vector<int>vis(n, false); 
        for(int j = 0; j < sz; j++) { 
            string s; 
            cin >> s; 
            int v = to[s]; 
            h[v] = max(h[v], c);
            vis[v] = true;  
        }
        for(int j = 0; j < n; j++) if(!vis[j]) cand[j][c] = false; 
    }
    Matching mc(n); 
    for(int i = 0; i < n; i++) { 
        for(int j = 0; j < n; j++) if(h[i] <= j && cand[i][j]) {
            mc.addEdge(i, j); 
        }
    }
    mc.match(); 
    for(int i = 0; i < n; i++) { 
        cout << s[mc.matchR[i]] << ' '; 
    }
    cout << '\n'; 
    return 0;
}