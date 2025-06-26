#include "bits/stdc++.h"

using namespace std;

const int MAXN = 5e5 + 2;
const int INF = 1e8 + 5;


bool vis[MAXN]; 
int n, m, where[MAXN], match[MAXN], dist[MAXN], arr[MAXN];
vector<int> g[MAXN], h[MAXN], paths[MAXN], ord;
map<string, int> mp;
map<vector<int>, int> str;

bool bfs()
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (!match[i])
            dist[i] = 0, q.emplace(i);
        else
            dist[i] = INF;
    }
    dist[0] = INF;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (!u)
            continue;
        for (int v : g[u])
        {
            if (dist[match[v]] == INF)
            {
                dist[match[v]] = dist[u] + 1,
                q.emplace(match[v]);
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int u)
{
    if (!u)
        return 1;
    for (int v : g[u])
    {
        if (dist[match[v]] == dist[u] + 1 and dfs(match[v]))
        {
            match[u] = v, match[v] = u;
            return 1;
        }
    }
    dist[u] = INF;
    return 0;
}

int hopcroftKarp()
{
    int ret = 0;
    while (bfs())
    {
        for (int i = 1; i <= n; ++i)
        {
            ret += !match[i] and dfs(i);
        }
    }
    return ret;
}
int main(void)
{
    int N; 
    while(cin >> N)
    {
        int nodes = 0; 
        int node2 = 0;
        for(int i = 0; i < N; i++)
        {
            int M; 
            cin >> M; 
            vector<string>arr; 
            for(int j = 0; j < M; j++)
            {
                string S; 
                cin >> S; 
                if(!mp.count(S)) mp[S] = nodes++; 
                arr.push_back(S); 
            }
            for(int mask = 0; mask < (1 << (int) arr.size()); mask++)
            {
                vector<int>curr;
                for(int j = 0; j < arr.size(); j++) if(mask & (1 << j))
                {
                    curr.push_back(mp[arr[j]]); 
                } 
                sort(curr.begin(), curr.end()); 
                if(!str.count(curr)) str[curr] = node2++; 
            }
        } 
        for(auto it : str)
        {
            vector<int>curr = it.first; 
            int n = curr.size(); 
            for(int i = 0; i < curr.size(); i++)
            {
                vector<int> acc;
                for(int j = 0; j < curr.size(); j++) if(i != j) 
                {
                    acc.push_back(curr[j]); 
                }
                if (str.count(acc))
                {
                    g[str[acc] + 1].push_back(it.second + node2 + 1);
                }
            }
        }
        n = node2;
        cout << n - hopcroftKarp() << '\n'; 
    }
    return 0;
}