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
char s[N]; 

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
      //  cout << u << " " << c << " " << v << '\n'; 
        if(!node[v].ctr) calc(v); 
        node[u].ctr += node[v].ctr; 
    }
    return; 
}
int main(void)
{
    while (scanf("%s", s) == 1)
    {
        n = strlen(s);
        node[0].link = -1;
        node[0].len = 0;
        sz = 1;
        last = 0;
        for (int i = 0; i < n; i++)
        {
            extend(s[i]);
        } 
        calc(); 
        cout << node[0].ctr - 1 << '\n'; 
    }
    return 0; 
}