#include "bits/stdc++.h"
using namespace std;
#define MAX 10000
#define inf (int)1e9
#define lint long long
#define vi vector<int>
#define vlint vector<lint>
#define mp make_pair
long long A, B;
int n, m;
string X[MAX];
string Y[MAX];
int cntS[26];
int deg[26], ndeg[26], mdeg[26];
set<int> correct[26];
set<int> nadj[MAX];
char ans[MAX];
int vis[MAX];
vector<int> pos[MAX];
struct MinCostFlow
{
    struct Edge
    {
        int from, to;
        lint cap, cost;
        Edge(int _from, int _to, lint _cap, lint _cost) : from(_from), to(_to), cap(_cap), cost(_cost) {}
    };
    int N;
    vector<Edge> edges;
    vector<vi> adj, radj;
    void init(int n)
    {
        N = n;
        adj.assign(N, vector<int>());
    }
    void conn(int u, int v, lint cap, lint cost)
    {
        adj[u].push_back((int)edges.size());
        edges.push_back(Edge(u, v, cap, cost));
        adj[v].push_back(-(int)edges.size());
        edges.push_back(Edge(v, u, 0, -cost));
        return;
    }
    void spfa(int src, vector<lint> &dist, vector<int> &fa)
    {
        vector<bool> inq(N, 0);
        queue<int> q;
        fill(dist.begin(), dist.end(), inf);
        fill(fa.begin(), fa.end(), -1);
        dist[src] = 0;
        q.push(src);
        inq[src] = 1;
        while (q.size())
        {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i];
                const Edge e = (v < 0 ? edges[-v] : edges[v]);
                if (e.cap > 0 && dist[e.to] > dist[e.from] + e.cost)
                {
                    dist[e.to] = dist[e.from] + e.cost;
                    fa[e.to] = v;
                    if (!inq[e.to])
                    {
                        inq[e.to] = 1;
                        q.push(e.to);
                    }
                }
            }
        }
    }
    lint mincost(int K, int src, int sink)
    {
        lint flow = 0;
        lint cost = 0;
        vector<lint> dist(N);
        vector<int> fa(N);
        while (flow < K)
        {
            spfa(src, dist, fa);
            if (dist[sink] == inf)
            {
                break;
            }
          //  cout << flow << endl;
            lint f = K - flow;
            int cur = sink;
            while (cur != src)
            {
                Edge e = (fa[cur] < 0 ? edges[-fa[cur]] : edges[fa[cur]]);
                f = min(f, e.cap);
                cur = e.from;
            }
            cur = sink;
            flow += f;
            cost += f * dist[sink];
            while (cur != src)
            {
                if (fa[cur] < 0)
                {
                    edges[-fa[cur]].cap -= f;
                    edges[-fa[cur] - 1].cap += f;
                }
                else
                {
                    edges[fa[cur]].cap -= f;
                    edges[fa[cur] + 1].cap += f;
                }
                cur = fa[cur] < 0 ? edges[-fa[cur]].from : edges[fa[cur]].from;
            }
        }
        return flow < K ? -1 : cost;
    }
};
MinCostFlow mcf;
signed main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> X[i] >> Y[i];
    }
    memset(deg, -1, sizeof(deg)); 
    for (int i = 0; i < n - 1; i++)
    {
        memset(ndeg, 0, sizeof(ndeg));
        memset(cntS, 0, sizeof(cntS));
        for (int j = 0; j < m; j++)
        {
            if (Y[i][j] == 'G')
            {
                ans[j] = X[i][j];
                correct[X[i][j] - 'a'].insert(j);
                cntS[X[i][j] - 'a'] += 1;
                nadj[X[i][j] - 'a'].insert(j);
            }
            else if (Y[i][j] == 'Y')
            {
                cntS[X[i][j] - 'a'] += 1;
                nadj[X[i][j] - 'a'].insert(j);
            }
            else
            {
                vis[X[i][j] - 'a'] |= 1;
                ndeg[X[i][j] - 'a'] = 1;
                nadj[X[i][j] - 'a'].insert(j);
            }
        }
        for (int j = 0; j < 26; j++)
        {
            if (ndeg[j])
            {
                deg[j] = cntS[j];
            }
            else
            {
                mdeg[j] = max(mdeg[j], cntS[j]);
            }
        }
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (ans[j] != NULL && ans[j] != (char)(i + 'a'))
            {
                nadj[i].insert(j);
            }
        }
    }
    mcf.init(m + 29);
    int src = m + 27;
    int sink = m + 28;
    for (int i = 0; i < 26; i++)
    {
        if (deg[i] > (int)correct[i].size())
        {
            mcf.conn(i, sink, deg[i] - (int)correct[i].size(), 0);
            for (int j = 0; j < m; j++)
            {
                if (nadj[i].count(j))
                    continue;
                mcf.conn(26 + j, i, 1, 0);
            }
        }
        else if (mdeg[i] > (int)correct[i].size())
        {
            mcf.conn(i, sink, mdeg[i] - (int)correct[i].size(), 1);
            for (int j = 0; j < m; j++)
            {
                if (nadj[i].count(j))
                    continue;
                mcf.conn(26 + j, i, 1, 0);
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        mcf.conn(src, i + 26, 1, 0);
    }
    for (int i = 0; i < 26; i++)
    {
        if (deg[i] == -1)
        {
            mcf.conn(i, sink, m, MAX);
        }
    }
    while(true)
    {
        mcf.mincost(inf, src, sink);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < (int)mcf.adj[i + 26].size(); j++)
            {
                 int curr = mcf.adj[i + 26][j];
                 if (curr < 0 || mcf.edges[curr].cap != 0 || mcf.edges[curr].to == src)
                    continue;
                 ans[i] = (char)(mcf.edges[curr].to + 'a');
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if (!vis[i])
            {
                 for (int j = 0; j < m; j++)
                 {
                    if (ans[j] == NULL && !nadj[i].count(j))
                    {
                           ans[j] = (char)(i + 'a');
                    }
                 }
            }
        }
        int good = 1;
        for (int i = 0; i < m; i++)
        {
            good = good & (ans[i] != NULL);
        }
        if(good) break;
        for (int i = 0; i < 26; i++)
        {
            if (deg[i] == -1)
            {
                 for (int j = 0; j < m; j++)
                 {
                    if (!nadj[i].count(j))
                    {
                           mcf.conn(26 + j, i, 1, MAX);
                    }
                 }
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        printf("%c", ans[i]);
    }
    return 0;
}