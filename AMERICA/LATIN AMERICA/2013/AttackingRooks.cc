#include "bits/stdc++.h"

using namespace std;

const int INF = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n) {
        e.clear();
        for (int i = 0; i < n; i++) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap) {
        Edge e1 = { a, b, cap, 0 };
        Edge e2 = { b, a, 0, 0 };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for (;;) {
            if (!bfs()) break;
            std::fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }

private:
    bool bfs() {
        int qh = 0, qt = 0;
        q[qt++] = s;
        std::fill(d.begin(), d.end(), -1);
        d[s] = 0;

        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            for (int i = 0; i < (int) g[v].size(); i++) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cout.tie(0); 
    cin.tie(0);    
    int n; 
    cin >> n;
    vector<vector<char>>g(n, vector<char>(n)); 
    for(int i = 0; i < n; i++) 
    for(int j = 0; j < n; j++) { 
        cin >> g[i][j]; 
    }
    int N = 0, M = 0; 
    vector<vector<int>>rg(n, vector<int>(n, -1)); 
    vector<vector<int>>rc(n, vector<int>(n, -1)); 
    for(int i = 0; i < n; i++) { 
        int marked = false; 
        for(int j = 0; j < n; j++) { 
            if(g[i][j] == '.' && !marked) { 
                marked = true; 
                rg[i][j] = N++; 
            }
            else if(g[i][j] == '.' && marked) {rg[i][j] = rg[i][j - 1]; }
            else marked = false; 
        }
        marked = false; 
        for(int j = 0; j < n; j++) { 
            if(g[j][i] == '.' && !marked) { 
                marked = true; 
                rc[j][i] = M++; 
            }
            else if(g[j][i] == '.' && marked) {rc[j][i] = rc[j - 1][i]; }
            else marked = false; 
        }
    }
    MaxFlow dinic(N + M + 2);
    int src = N + M; 
    int sink = N + M + 1; 
    set<pair<int, int>>s; 
    for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++) {
        int u = rg[i][j], v = rc[i][j]; 
        if(u == -1 || v == -1) continue; 
        if(!s.count({src, u})) { 
            s.insert({src, u}); 
            dinic.addEdge(src, u, 1); 
        }
        if(!s.count({v, sink})) { 
            s.insert({v, sink}); 
            dinic.addEdge(N + v, sink, 1); 
        }
        if(!s.count({u, v})) { 
            s.insert({v, sink}); 
            dinic.addEdge(u, N + v, 1); 
        } 
    }
    cout << dinic.getMaxFlow(src, sink) << '\n'; 
    return 0; 
}