#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e3 + 10;
#define mp make_pair
// Library Code from RR 
struct DirectedDfs
{
    vector<vector<int> > g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector<vector<int> > scc;

    DirectedDfs(const vector<vector<int> > &_g) : g(_g), n(g.size()), num(n, -1), low(n, 0), current(n, 0), counter(0), comp_ids(n, -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (num[i] == -1)
                dfs(i);
        }
    }
    void dfs(int u)
    {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (auto v : g[u])
        {
            if (num[v] == -1)
                dfs(v);
            if (current[v])
                low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u])
        {
            scc.push_back(vector<int>());
            while (1)
            {
                int v = S.back();
                S.pop_back();
                current[v] = 0;
                scc.back().push_back(v);
                comp_ids[v] = ((int)scc.size()) - 1;
                if (u == v)
                    break;
            }
        }
    }

    // build DAG of strongly connected components
    // Returns: adjacency list of DAG
    std::vector<std::vector<int> > build_scc_dag()
    {
        std::vector<std::vector<int> > dag(scc.size());
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    dag[x].push_back(y);
                }
            }
        }
        return dag;
    }
};
struct TwoSatSolver
{
    TwoSatSolver(int _n_vars) : n_vars(_n_vars), g(2 * n_vars) {}

    void x_or_y_constraint(bool is_x_true, int x, bool is_y_true, int y)
    {
        assert(x >= 0 && x < n_vars);
        assert(y >= 0 && y < n_vars);
        if (!is_x_true)
            x += n_vars;
        if (!is_y_true)
            y += n_vars;
        g[(x + n_vars) % (2 * n_vars)].push_back(y);
        g[(y + n_vars) % (2 * n_vars)].push_back(x);
    }
    pair<bool, vector<bool> > solve()
    {
        DirectedDfs tree(g);
        vector<bool> solution(n_vars);
        for (int i = 0; i < n_vars; i++)
        {
            if (tree.comp_ids[i] == tree.comp_ids[i + n_vars])
            {
                return {false, {}};
            }
            solution[i] = tree.comp_ids[i] < tree.comp_ids[i + n_vars];
        }
        return {true, solution};
    }
    int n_vars;
    vector<vector<int> > g;
};
int n, m;
char g[MAXN][MAXN]; 
signed main(void)
{ 
    cin >> n >> m; 
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
             cin >> g[i][j]; 
        }
    }
    string res = " "; 
    for(int p = 1; p <= m; p++)
    { 
        TwoSatSolver tsat(m + 2);
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                if(g[i][j] == 'X') continue;
                for(int k = j + 1; k <= m; k++)
                {
                     if(g[i][k] == 'X') continue; 
                     tsat.x_or_y_constraint(g[i][j] == 'T' ? false : true, j, g[i][k] == 'T' ? false : true, k);
                }
            }
        }
        for(int i = 1; i < p; i++)
        {
            if(res[i] == 'T') tsat.x_or_y_constraint(true, i, true, i); 
            else tsat.x_or_y_constraint(false, i, false, i); 
        }
        tsat.x_or_y_constraint(false, p, false, p); 
        if(tsat.solve().first) res += "F"; 
        else res += "T"; 
    }
    int get = 0;
    for(int i = 1; i <= n; i++)
    {
        int now = 0; 
        for(int j = 1; j <= m; j++)
        {
             now += (g[i][j] == res[j]); 
        }
        if(now > 1)
        {
           puts("-1");
           return 0;
        }
    }
    for(int i = 1; i <= m; i++) cout << res[i]; 
    cout << '\n'; 
    return 0;
}