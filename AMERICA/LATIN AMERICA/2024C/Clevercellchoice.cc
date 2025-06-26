#include "bits/stdc++.h"

using namespace std;

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

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<char>>g(n, vector<char>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
        }
    const int dx[4] = {0, 0, -1, 1};
    const int dy[4] = {-1, 1, 0, 0};
    int ret = 0;
    Matching mc(n * m);
    for (int rx = 0; rx < n; rx++) for (int ry = 0; ry < m; ry++) if (g[rx][ry] != '#') {
        if ((rx + ry) & 1) {
            for (int k = 0; k < 4; k++) {
                int kx = dx[k] + rx, ky = dy[k] + ry;
                if (0 <= kx && kx < n && 0 <= ky && ky < m && g[kx][ky] != '#') {
                    mc.addEdge(m * rx + ry, m * kx + ky);
                }
            }
        }
    }
    int c = mc.match();
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) if(g[i][j] != '#') {
        Matching mc2(n * m);
        for (int rx = 0; rx < n; rx++) for (int ry = 0; ry < m; ry++) {
            if (g[rx][ry] != '#') {
                if (rx == i && ry == j) continue;
                if ((rx + ry) & 1) {
                    for (int k = 0; k < 4; k++) {
                        int kx = dx[k] + rx, ky = dy[k] + ry;
                        if (0 <= kx && kx < n && 0 <= ky && ky < m && g[kx][ky] != '#') {
                           if (i == kx && j == ky) continue;
                           mc2.addEdge(m * rx + ry, m * kx + ky);
                        }
                    }
                }
            }
        }
        ret += (mc2.match() == c);
    }
    cout << ret << '\n'; 
    return 0;
}