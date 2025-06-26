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

const int N = 10005; 

int v[N][N], h[N][N]; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int n; 
    cin >> n; 
    char c;
    MaxFlow dinic(N + 2);
    int src = N; 
    int sink = N + 1; 
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) { 
            cin >> c; 
            if(j < n) { 
                cin >> c; 
                h[i][j] = (c == '-'); 
            }
        }
        if(i < n) { 
            for(int j = 1; j <= n; j++) { 
                cin >> c; 
                v[i][j] = (c == '|'); 
                if(j < n) { 
                    cin >> c; 
                }
            }
        }
    }
    for(int i = 0; i <= n; i++)
    for(int j = 0; j <= n; j++) {
        int cap = (not h[i][j]) + (not v[i][j]) + (not v[i][j + 1]) + (not h[i + 1][j]) - 1; 
        //cout << cap << '\n'; 
        if((i + j) % 2 == 0) { 
            dinic.addEdge(src, (n + 1) * i + j, cap); 
        }
        else { 
            dinic.addEdge((n + 1) * i + j, sink, cap); 
        }
    }
    for(int i = 1; i <= n; i++) { 
        for(int j = 1; j <= n; j++) if(j < n) { 
            if(!h[i][j]) { 
                if((i + j) % 2 == 0) { 
                    dinic.addEdge((n + 1) * i + j, (n + 1) * (i - 1) + j, 1); 
                }
                else { 
                    dinic.addEdge((n + 1) * (i - 1) + j, (n + 1) * i + j, 1); 
                }
            }
        }
        if(i < n) { 
            for(int j = 1; j <= n; j++) { 
                if(!v[i][j]) { 
                    if((i + j) % 2 == 0) { 
                        dinic.addEdge((n + 1) * i + j, (n + 1) * i + j - 1, 1); 
                    }
                    else { 
                        dinic.addEdge((n + 1) * i + j - 1, (n + 1) * i + j, 1); 
                    }
                }
            }
        }
    }
    cout << dinic.getMaxFlow(src, sink) + 1 << '\n'; 
    return 0; 
}