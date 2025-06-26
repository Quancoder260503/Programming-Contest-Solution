#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10;
struct Node
{
    int len, link, cnt, firstpos;
    map<char, int> nxt;
};
char s[N];
Node node[N];
char q[N];
int n, m, k, sz, last;
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
            node[ncur].firstpos = node[at].firstpos;
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
bool query()
{
    m = strlen(q);
    int at = 0;  
    for(int i = 0; i < m; i++)
    {
        if(!node[at].nxt.count(q[i])) return false; 
        at = node[at].nxt[q[i]];
    }
    return true;
}
signed main(void)
{
    scanf(" %s", s); 
    scanf("%d", &k);
    n = strlen(s);
    node[0].link = -1; 
    node[0].len = 0; 
    sz = 1; 
    last = 0; 
    for(int i = 0; i < n; i++)
    {
        extend(s[i]); 
    }
    for(int i = 0; i < k; i++)
    {
        scanf(" %s", q); 
        puts(query() ? "YES" : "NO"); 
    }
    return 0;
}