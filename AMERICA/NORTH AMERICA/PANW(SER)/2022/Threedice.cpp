#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)27
const int M = 1 << 18 + 1;
int adj[MAXN][MAXN];
int n;
int cc;
vector<int> cset(26, 0);
vector<int> grp[M];
bool valid[M];
int to[M];
int bitcnt(int x)
{
    return x == 0 ? 0 : (x & 1) + bitcnt(x / 2);
}
signed main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        vector<int> chk(26, 0);
        for (int j = 0; j < s.length(); j++)
        {
            cset[s[j] - 'a']++;
            chk[s[j] - 'a']++;
        }
        bool good = 1;
        for (int j = 0; j < 26; j++)
        {
            good = good & (chk[j] <= 1);
        }
        if (!good)
        {
            puts("0");
            return 0;
        }
        for (int j = 0; j < 26; j++)
        {
            if (!chk[j])
                continue;
            for (int k = j + 1; k < 26; k++)
            {
                if (!chk[k])
                    continue;
                adj[j][k] = adj[k][j] = 1;
            }
        }
    }
    int cc = 0;
    int cnt = 0;
    vector<int> ch;
    for (int i = 0; i < 26; i++)
    {
        if (cset[i] >= 1)
        {
            ch.push_back(i);
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (ch.size() < 18 && cset[i] == 0)
        {
            ch.push_back(i);
        }
    }
    if (ch.size() > 18)
    {
        puts("0");
        return 0;
    }
    memset(to, -1, sizeof(to));
    for (int mask = 0; mask < (1 << 18); mask++)
    {
        if (bitcnt(mask) == 6)
        {
            for (int i = 0; i < 18; i++)
            {
                if (mask & (1 << i))
                {
                    grp[mask].push_back(ch[i]);
                }
            }
            valid[mask] = 1;
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    int u = grp[mask][i];
                    int v = grp[mask][j];
                    valid[mask] = valid[mask] & (!adj[u][v]);
                }
            }
        }
        if (bitcnt(mask) == 12)
        {
            for (int smask = mask; smask; smask = (smask - 1) & mask)
            {
                int nmask = mask xor smask;
                if (valid[smask] && valid[nmask])
                {
                    valid[mask] = 1;
                    to[mask] = smask;
                }
            }
        }
        if (bitcnt(mask) == 18)
        {
            for (int smask = mask; smask; smask = (smask - 1) & mask)
            {
                int nmask = mask xor smask;
                if (valid[smask] && valid[nmask])
                {
                    if (smask < nmask)
                        swap(smask, nmask);
                    int pmask = to[smask] xor smask;
                    assert(to[smask] != -1);
                    for (int i = 0; i < grp[to[smask]].size(); i++)
                    {
                        cout << (char)('a' + grp[to[smask]][i]);
                    }
                    cout << " ";
                    for (int i = 0; i < grp[nmask].size(); i++)
                    {
                        cout << (char)('a' + grp[nmask][i]);
                    }
                    cout << " ";
                    for (int i = 0; i < grp[pmask].size(); i++)
                    {
                        cout << (char)('a' + grp[pmask][i]);
                    }
                    cout << endl;
                    return 0;
                }
            }
        }
    }
    puts("0"); 
    return 0;
}