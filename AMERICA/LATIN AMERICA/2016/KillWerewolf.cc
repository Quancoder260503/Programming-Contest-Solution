#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

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
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    int N; 
    cin >> N; 
    vector<array<int, 2>>victim(N); 
    for(int i = 0; i < N; i++) { 
        cin >> victim[i][0] >> victim[i][1]; 
        victim[i][0]--; 
        victim[i][1]--; 
    } 
    int ret = 0; 
    for(int werewolf = 0; werewolf < N; werewolf++) { 
        int votes = 0;
        for(int i = 0; i < N; i++) if(victim[i][0] == werewolf || victim[i][1] == werewolf) {
            votes++;  
        }
        MaxFlow dinic(2 * N + 2); 
        int src = 2 * N; 
        int sink = 2 * N + 1;   
        for(int i = 0; i < N; i++) if(werewolf != i) { 
            dinic.addEdge(src, i, 1);
            if(i == victim[werewolf][0] || i == victim[werewolf][1]) { 
                dinic.addEdge(N + i, sink, max(0, votes - 2)); 
            } 
            else { 
                dinic.addEdge(N + i, sink, max(0, votes - 1)); 
            }
            if(victim[i][0] == werewolf || victim[i][1] == werewolf) continue; 
            dinic.addEdge(i, N + victim[i][0], 1); 
            dinic.addEdge(i, N + victim[i][1], 1); 
        }
        int flow = dinic.getMaxFlow(src, sink); 
//cout << flow << " " << N - 1 - votes << '\n'; 
        ret += (flow <  N - 1 - votes); 
    }
    cout << ret << '\n'; 
    return 0; 
}
/* 
    idea : 
       All people who choose the werewolf can choose to eliminate him directly 
       We fixed the maximum number of votes for other players (note that we should seperate the case for each victim of the werewolf)
       If there is an arrangement (matching) that satisfy the constraint then we stop, if the maximum number of votes doesnt not exceed 
       the number of votes for the werewolf than the werewolf lose. 
*/