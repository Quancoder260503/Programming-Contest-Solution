#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2000;
struct Matching
{
    int n;
    vector<vector<int>> ke;
    vector<int> seen;
    vector<int> matchL, matchR;
    int iteration;

    Matching(int _n) : n(_n), ke(_n), seen(_n, false), matchL(_n, -1), matchR(_n, -1), iteration{0}
    {
    }

    void addEdge(int u, int v)
    {
        ke[u].push_back(v);
    }
    void reset()
    {
        for (int i = 0; i < n; i++)
        {
            matchL[i] = matchR[i] = -1;
            seen[i] = false;
        }
        iteration = 0;
    }
    bool dfs(int u)
    {
        seen[u] = iteration;
        for (int v : ke[u])
        {
            if (matchR[v] < 0)
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        for (int v : ke[u])
        {
            if (seen[matchR[v]] != iteration && dfs(matchR[v]))
            {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    int match()
    {
        int res = 0;
        int newMatches = 0;
        do
        {
            iteration++;
            newMatches = 0;
            for (int u = 0; u < n; u++)
            {
                if (matchL[u] < 0 && dfs(u))
                    ++newMatches;
            }
            res += newMatches;
        } while (newMatches > 0);
        return res;
    }
};
int n, m;
string a[MAXN];
string b[MAXN];
string p;
signed main(void)
{
    cin >> n >> m;
    int N = 0, M = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }
    Matching mcbm(MAXN);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i][0] == b[j][0] || a[i][1] == b[j][1])
            {
                mcbm.addEdge(i, j);
            }
        }
    }
    int old_match = mcbm.match();
    cin >> p;
    for (int i = 1; i <= n; i++)
    {
        if (a[i][0] == p[0] || a[i][1] == p[1])
        {
            mcbm.addEdge(i, m + 1);
        }
    }
    mcbm.reset();
    int new_match = mcbm.match();
    //cout << new_match << " " << old_match << endl;
    cout << (new_match == old_match ? "Richard" : "Malcolm") << '\n';
    return 0;
}
// To check if a vertex is contained in every maximum matching 
// Remove that vertice and compare the maximum matching 