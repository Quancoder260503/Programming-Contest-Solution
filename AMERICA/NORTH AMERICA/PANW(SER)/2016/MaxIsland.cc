#include "bits/stdc++.h"

using namespace std; 

const int dx[4] = {-1, 1, 0, 0}; 
const int dy[4] = {0, 0, -1, 1}; 

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


int R, C; 
vector<vector<char>>g;
vector<vector<int>>vis;

void doit(int i, int j) { 
    vis[i][j] = true; 
    for(int dir = 0; dir < 4; dir++) { 
        int ni = dx[dir] + i, nj = dy[dir] + j; 
        if(0 <= ni && ni < R && 0 <= nj && nj < C && g[ni][nj] == 'L' && !vis[ni][nj]) {
            doit(ni, nj);  
        }
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    cin >> R >> C; 
    g.resize(R, vector<char>(C)); 
    vis.resize(R, vector<int>(C)); 
    for(int i = 0; i < R; i++) 
    for(int j = 0; j < C; j++) { 
        cin >> g[i][j]; 
    }    
    for(int i = 0; i < R; i++) { 
        for(int j = 0; j < C; j++) if(g[i][j] == 'C') {
            int next_land = false;  
            for(int dir = 0; dir < 4; dir++) { 
                int ni = dx[dir] + i, nj = dy[dir] + j; 
                if(0 <= ni && ni < R && 0 <= nj && nj < C && g[ni][nj] == 'L') { 
                    next_land = true; 
                }
            }
            if(next_land) { 
                g[i][j] = 'W'; 
            }
        }
    }
    int ret = 0; 
    for(int i = 0; i < R; i++)
    for(int j = 0; j < C; j++) if(!vis[i][j] && g[i][j] == 'L') { 
        ret++;
        doit(i, j); 
    }
    
    MaxFlow dinic(R * C + 2);
    int src = R * C, sink = R * C + 1;  
    for(int i = 0; i < R; i++) { 
        for(int j = 0; j < C; j++) { 
            if(g[i][j] == 'C') { 
                ret++; 
                if((i + j) % 2 == 0) { 
                    dinic.addEdge(src, i * C + j, 1); 
                    for(int dir = 0; dir < 4; dir++) { 
                        int ni = dx[dir] + i, nj = dy[dir] + j; 
                        if(0 <= ni && ni < R && 0 <= nj && nj < C && g[ni][nj] == 'C') { 
                            dinic.addEdge(i * C + j, ni * C + nj, 1); 
                        }
                    }
                }
                else { 
                    dinic.addEdge(i * C + j, sink, 1); 
                }
            } 
        }
    }
    ret -= dinic.getMaxFlow(src, sink); 
    cout << ret << '\n'; 
    return 0; 
}