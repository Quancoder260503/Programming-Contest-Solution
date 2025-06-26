#include "bits/stdc++.h"

using namespace std;

const int N = 5e5 + 10;

struct Node
{
    int len, link, cnt, firstpos;
    map<char, int> nxt;
};

Node node[N];
int n, m, q, sz, last;
string S, Q;

void extend(char c)
{
    int cur = sz++;
    node[cur].len = node[last].len + 1;
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
bool vis[N]; 
void doit(int u = 0)
{
    vis[u] = 1;
    for(auto [c, v] : node[u].nxt)
    {
        cout << u << " " << v << " " << c << '\n';
        if(!vis[v]) doit(v); 
    }
}
int solve(void)
{
    m = Q.length();
    int at = 0;
    int ctr = 0; 
    for (int i = 0; i < m; i++)
    {  
        if(node[at].nxt.count(Q[i])) 
        {
            at = node[at].nxt[Q[i]]; 
            continue; 
        }
        else 
        {
            ctr++; 
            at = 0; 
        }
        if(!node[at].nxt.count(Q[i])) return -1; 
        at = node[at].nxt[Q[i]]; 
    }
    ctr += (at > 0); 
    return ctr;
}
int main(void)
{
    while(cin >> S >> q) 
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
        //doit(); 
        for (int i = 0; i < q; i++)
        {
            cin >> Q;
            cout << solve() << '\n'; 
        }
    }
    return 0;
}