#include "bits/stdc++.h"

using namespace std;

const int N = 5e5 + 10;

struct Node
{
    int len, link, firstpos;
    int64_t ctr; 
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

void calc(int u = 0)
{
    node[u].ctr = 1; 
    for(auto [c, v] : node[u].nxt)
    {
        if(!node[v].ctr) calc(v); 
        node[u].ctr += node[v].ctr; 
    }
    return; 
}

void doit(string &ret, int64_t K, int u = 0)
{
    if(K == 0) return; 
    for(auto [c, v] : node[u].nxt)
    {
        if(node[v].ctr > K)
        { 
            ret += c; 
            doit(ret, K - 1, v);
            return; 
        }
        else 
        {
            K = K - node[v].ctr; 
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
        string ret = ""; 
        doit(ret, K); 
        cout << ret << '\n'; 
    }
    return 0;
}