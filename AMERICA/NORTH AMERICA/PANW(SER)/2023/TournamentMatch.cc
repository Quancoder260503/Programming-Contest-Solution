#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

bool find(int j, vector<vector<int>> &g, vector<int> &btoa, vector<int> &vis)
{
    if (btoa[j] == -1) return 1;
    vis[j] = 1;
    int di = btoa[j];
    for (int e : g[di])
        if (!vis[e] && find(e, g, btoa, vis))
        {
            btoa[e] = di;
            return 1;
        }
    return 0;
}
int dfsMatching(vector<vector<int>> &g, vector<int>&btoa)
{
    vector<int> vis;
    for (int i = 0; i < sz(g); i++)
    {
        vis.assign(sz(btoa), 0);
        for (int j : g[i])
            if (find(j, g, btoa, vis))
            {
                btoa[j] = i;
                break;
            }
    }
    return sz(btoa) - (int)count(btoa.begin(), btoa.end(), -1);
}

struct team { 
    int n;
    vector<pair<int, int>>group; 
}; 

int main(void) { 
    int n; 
    cin >> n;
    vector<team>odd, even;
    for(int i = 0; i < n; i++) { 
        team curr_team; 
        cin >> curr_team.n; 
        for(int j = 0, u, v; j < curr_team.n; j++) { 
            cin >> u >> v;
            --u, --v; 
            curr_team.group.push_back({u, v}); 
        }
        (curr_team.n & 1 ? odd : even).push_back(curr_team); 
    }
    vector<vector<int>>can_match(odd.size(), vector<int>(even.size(), 0)); 
    for(int i = 0; i < odd.size(); i++) for(int j = 0; j < even.size(); j++) { 
        vector<vector<int>>g(15); 
        for(int k = 0; k < odd[i].n; k++) { 
            auto [u, v] = odd[i].group[k]; 
            g[u].push_back(k);
            g[v].push_back(k);  
        }
        for(int k = 0; k < even[j].n; k++) { 
            auto [u, v] = even[j].group[k]; 
            g[u].push_back(k + odd[i].n);
            g[v].push_back(k + odd[i].n);  
        }
        vector<int>btoa(odd[i].n + even[j].n, -1); 
        can_match[i][j] = (dfsMatching(g, btoa) == 15); 
    } 
    vector<vector<int>>g(odd.size()); 
    for(int i = 0; i < odd.size(); i++) { 
        for(int j = 0; j < even.size(); j++) if(odd[i].n + even[j].n == 15 && can_match[i][j]) { 
            g[i].push_back(j); 
        }
    }
    vector<int>btoa(even.size(), -1); 
    cout << dfsMatching(g, btoa) << '\n'; 
    return 0; 
}