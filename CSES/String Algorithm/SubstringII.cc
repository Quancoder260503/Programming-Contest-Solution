#include "bits/stdc++.h"

using namespace std;

const int N = 5e5 + 10;

struct Node
{
    int len, link, firstpos;
    int64_t ctr, dyn;
    map<char, int> nxt;
};

Node node[N];
int n, m, q, sz, last;
string S, Q;

void extend(char c)
{
    int cur = sz++;
    node[cur].len = node[last].len + 1;
    node[cur].ctr = 1; 
    int p = last;
    while (p != -1 && !node[p].nxt.count(c))
    {
        node[p].nxt[c] = cur;
        p = node[p].link;
    }
    if (p == -1)
    {
        node[cur].link = 0;
    }
    else
    {
        int at = node[p].nxt[c];
        if (node[p].len + 1 == node[at].len)
        {
            node[cur].link = at;
        }
        else
        {
            int ncur = sz++;
            node[ncur].len = node[p].len + 1;
            node[ncur].nxt = node[at].nxt;
            node[ncur].link = node[at].link;
            while (p != -1 && node[p].nxt[c] == at)
            {
                node[p].nxt[c] = ncur;
                p = node[p].link;
            }
            node[at].link = node[cur].link = ncur;
        }
    }
    last = cur;
    return;
}

void calc()
{
    vector<vector<int>> adj(sz, vector<int>());
    for (int i = 0; i < sz; i++)
    {
        adj[node[i].len].push_back(i);
    }
    for (int i = sz - 1; i >= 0; i--)
    {
        for (auto u : adj[i])
        {
            if (node[u].link == -1) continue;
            node[node[u].link].ctr += node[u].ctr;
        }
    }
    return;
}

void calc2(int u = 0)
{
    node[u].dyn = node[u].ctr;
    for (auto [c, v] : node[u].nxt)
    {
        if (!node[v].dyn) calc2(v);
        node[u].dyn += node[v].dyn;
    }
    return;
}

void doit(string &ret, int64_t K, int u = 0)
{
    if (K < 0) return;
    for (auto [c, v] : node[u].nxt)
    {
        if (node[v].dyn > K)
        {
            ret += c;
            doit(ret, K - node[v].ctr, v);
            return;
        }
        else
        {
            K = K - node[v].dyn;
        }
    } 
    return;
}

int main(void)
{
    int64_t K;
    while (cin >> S >> K)
    {
        n = S.length();
        node[0].link = -1;
        node[0].len = 0;
        sz = 1;
        last = 0;
        for (int i = 0; i < n; i++)
        {
            extend(S[i]);
        }
        calc();
        calc2(); 
        string ret = "";
        doit(ret, K - 1);
        cout << ret << '\n';
    }
    return 0;
}