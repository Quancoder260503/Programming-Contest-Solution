#include "bits/stdc++.h"

using namespace std; 

struct DirectedDfs {
    vector<vector<int>> g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector< vector<int> > scc;

    DirectedDfs(const vector<vector<int>>& _g) : g(_g), n(g.size()),
            num(n, -1), low(n, 0), current(n, 0), counter(0), comp_ids(n, -1) {
        for (int i = 0; i < n; i++) {
            if (num[i] == -1) dfs(i);
        }
    }

    void dfs(int u) {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (auto v : g[u]) {
            if (num[v] == -1) dfs(v);
            if (current[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            scc.push_back(vector<int>());
            while (1) {
                int v = S.back(); S.pop_back(); current[v] = 0;
                scc.back().push_back(v);
                comp_ids[v] = ((int) scc.size()) - 1;
                if (u == v) break;
            }
        }
    }

    // build DAG of strongly connected components
    // Returns: adjacency list of DAG
    int solve(int n) {
        vector<vector<int>> adj(scc.size());
        vector<int>c_size(scc.size()); 
        for (int u = 0; u < n; u++) {
            int x = comp_ids[u];
            c_size[x]++; 
        }
        int ret = 0; 
        for(int i = 0; i < scc.size(); i++) { 
            ret = max(ret, c_size[i]); 
        }
        ret = n - ret; 
        return ret; 
    }
};

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    int n;
    cin >> n; 
    vector<string>lang(n);
    vector<set<string>>comp(n); 
    cin.ignore(); 
    string text, word, name; 
    for(int i = 0; i < n; i++) {
        getline(cin, text); 
        stringstream ss(text);
        ss >> name >> lang[i]; 
        comp[i].insert(lang[i]); 
        while(ss >> word) { 
            comp[i].insert(word); 
        } 
    }
    vector<vector<int>>g(n); 
    for(int i = 0; i < n; i++) { 
        for(int j = 0; j < n; j++) if(j != i) { 
            if(comp[j].count(lang[i])) { 
                g[i].push_back(j);
            }
        }
    }
    DirectedDfs scc(g); 
    cout << scc.solve(n) << '\n'; 
    return 0; 
}