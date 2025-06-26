#include "bits/stdc++.h"
using namespace std;
const int MAXN = 5000; 
int M, N, Q, S, T;
vector<int> adj[MAXN];
int64_t cap[MAXN][MAXN];
vector<int> path;
int fa[MAXN], vis[MAXN];
int64_t bfs(int src = S, int tar = T)
{
    queue<pair<int, int64_t>> q;
    fill(fa + 1, fa + M + 2, 0);
    q.push({src, INT32_MAX});
    while (q.size())
    {
        int node;
        int64_t aug;
        tie(node, aug) = q.front();
        q.pop();
        for (int i = 0; i < adj[node].size(); i++)
        {
            int u = adj[node][i];
            if (!fa[u] && cap[node][u] > 0)
            {
                aug = min(aug, cap[node][u]);
                fa[u] = node;
                if (u == tar) return aug;
                q.push({u, aug});
            }
        }
    }
    return 0;
}
int64_t max_flow()
{
    int64_t flow = 0;
    int64_t aug = 0;
    int ctr = 0; 
    while (aug = bfs())
    {
        int g = T;
        flow += aug;
        while (S != g)
        {
            cap[fa[g]][g] -= aug;
            cap[g][fa[g]] += aug;
            g = fa[g];
        }
    }
    return flow;
}
void add_edge(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u); 
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> Q)
    { 
        vector<vector<int>> str(N, vector<int>(26));
        string inp;
        getline(cin, inp);
        for (int i = 0; i < N; i++)
        {
            getline(cin, inp);
            for (int j = 0; j < inp.length(); j++)
            {
                string curr;
                int at;
                for (at = j; at < inp.length() && inp[at] != ' '; at++) curr += inp[at];
                str[i][curr[0] - 'A']++; 
                j = at;
            }
        }
        M = N + 26; 
        S = 0; 
        T = M + 1; 
        for(int i = 0; i < N; i++)  add_edge(S, i + 1); 
        for(int i = 0; i < 26; i++) add_edge(N + i + 1, T); 
        for(int i = 0; i < N; i++) for(int j = 0; j < 26; j++) add_edge(i + 1, N + j + 1);
        for (int i = 0; i < Q; i++)
        {
            string q;
            cin >> q;
            if(q.length() > N) 
            {
                puts("NO"); 
                continue; 
            }
            vector<int>ctr(26, 0); 
            for(int j = 0; j < T; j++) for(int k = 0; k < T; k++) cap[j][k] = 0; 
            for(int j = 0; j < q.length(); j++) ctr[q[j] - 'A']++; 
            for(int j = 0; j < 26; j++) cap[N + j + 1][T] = ctr[j]; 
            for(int j = 0; j < N;  j++) cap[S][j + 1] = 1; 
            for(int j = 0; j < N;  j++) for(int k = 0; k < 26; k++) 
            {
                cap[j + 1][N + k + 1] = 0; 
                if (str[j][k] > 0)
                {
                    cap[j + 1][N + k + 1] = 1;
                }
            }
            puts(max_flow() == q.length() ? "YES" : "NO");  
        }
    }
    return 0;
}