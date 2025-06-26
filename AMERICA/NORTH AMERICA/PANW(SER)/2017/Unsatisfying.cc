#include "bits/stdc++.h"

using namespace std;
const int maxf = 7000;
struct DirectedDfs
{
    vector<vector<int>> g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector<vector<int>> scc;

    DirectedDfs(const vector<vector<int>> &_g) : g(_g), n(g.size()),
                                                 num(n, -1), low(n, 0), current(n, 0), counter(0), comp_ids(n, -1)
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
    std::vector<std::vector<int>> build_scc_dag()
    {
        std::vector<std::vector<int>> dag(scc.size());
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

bitset<maxf> reach[maxf], rreach[maxf];
int n_vars;
vector<vector<int>> g, dag;

void init(int _n_vars)
{
    n_vars = _n_vars;
    g.resize(2 * n_vars);
}

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
    return;
}

void doit(int u)
{
    reach[u][u] = 1;
    for (auto v : dag[u])
    {
        if (!reach[v][v]) doit(v);
        reach[u] |= reach[v];
    }
}
int min_clause()
{
    DirectedDfs tree(g);
    dag = tree.build_scc_dag();
    int N = dag.size();
    for (int i = 0; i < N; i++) if (!reach[i][i]) doit(i);
    for (int i = 0; i < N; i++) for(int j = 0; j < N; j++) rreach[j][i] = reach[i][j]; 
    int ret = 3;
    for (int i = 0; i < n_vars; i++)
    {
        int U = tree.comp_ids[i];
        int V = tree.comp_ids[i + n_vars];
        if (reach[U][V] && reach[V][U]) return 0;
        int chka = 0, chkb = 0, chkc = 0, chkd = 0;
        int fa = 0, fb = 0;
        for (int j = 0; j < n_vars; j++)
        {
            fa |= (reach[U][tree.comp_ids[j + n_vars]] && reach[V][tree.comp_ids[j + n_vars]]);
            fb |= (rreach[U][tree.comp_ids[j]] && rreach[V][tree.comp_ids[j]]);
            chka |= (reach[U][tree.comp_ids[j + n_vars]]);
            chkb |= (reach[V][tree.comp_ids[j + n_vars]]);
            chkc |= (rreach[U][tree.comp_ids[j]]);
            chkd |= (rreach[V][tree.comp_ids[j]]);
        }
        if(fa && fb) ret = min(ret, 1);
        if (chka && chkb && chkc && chkd) ret = min(ret, 2);
    }
    return (ret == 3 ? -1 : ret);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M;
    while (cin >> N >> M)
    {
        init(N);
        for (int i = 0; i < M; i++)
        {
            int U, V;
            cin >> U >> V;
            x_or_y_constraint((U > 0), abs(U) - 1, (V > 0), abs(V) - 1);
        }
        cout << min_clause() << '\n';
    }
    return 0;
}