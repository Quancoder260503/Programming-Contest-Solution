#include "bits/stdc++.h"

using namespace std;

struct DirectedDfs {
    vector<vector<int>> g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector<vector<int>> scc;

    DirectedDfs(const vector<vector<int>> &_g) : g(_g), n(g.size()), num(n, -1), low(n, 0), current(n, 0), counter(0), comp_ids(n, -1) {
        for (int i = 0; i < n; i++) {
            if (num[i] == -1) dfs(i);
        }
    }

    void dfs(int u) {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (auto v : g[u]) {
            if (num[v] == -1) dfs(v);
            if (current[v]) low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            scc.push_back(vector<int>());
            while (1) {
                int v = S.back();
                S.pop_back();
                current[v] = 0;
                scc.back().push_back(v);
                comp_ids[v] = ((int) scc.size()) - 1;
                if (u == v) break;
            }
        }
    }

    // build DAG of strongly connected components
    // Returns: adjacency list of DAG
    std::vector<std::vector<int>> build_scc_dag() {
        std::vector<std::vector<int>> dag(scc.size());
        for (int u = 0; u < n; u++) {
            int x = comp_ids[u];
            for (int v : g[u]) {
                int y = comp_ids[v];
                if (x != y) {
                    dag[x].push_back(y);
                }
            }
        }
        return dag;
    }
};

struct TwoSatSolver {
    TwoSatSolver(int _n_vars) : n_vars(_n_vars), g(2 * n_vars) {}

    void x_or_y_constraint(bool is_x_true, int x, bool is_y_true, int y) {
        assert(x >= 0 && x < n_vars);
        assert(y >= 0 && y < n_vars);
        if (!is_x_true) x += n_vars;
        if (!is_y_true) y += n_vars;
        // x || y
        // !x -> y
        // !y -> x
        g[(x + n_vars) % (2 * n_vars)].push_back(y);
        g[(y + n_vars) % (2 * n_vars)].push_back(x);
    }

    // Returns:
    // If no solution -> returns {false, {}}
    // If has solution -> returns {true, solution}
    //    where |solution| = n_vars, solution = true / false
    int solve() {
        DirectedDfs tree(g);
        vector<bool> solution(n_vars);
        for (int i = 0; i < n_vars; i++) {
            if (tree.comp_ids[i] == tree.comp_ids[i + n_vars]) {
                return false; 
            }
            // Note that reverse(tree.scc) is topo sorted
            solution[i] = tree.comp_ids[i] < tree.comp_ids[i + n_vars];
        }
        return true; 
    }

    // number of variables
    int n_vars;
    // vertex 0 -> n_vars - 1: Ai is true
    // vertex n_vars -> 2*n_vars - 1: Ai is false
    vector<vector<int>> g;
};


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; 
    cin >> n;
    vector<int> a(7);
    vector<vector<int>> cc(7);
    int sum = 0; 
    for (int i = 0; i < 7; i++) {
        cin >> a[i];
        cc[i].resize(a[i]);
        for (int j = 0; j < a[i]; j++) cc[i][j] = sum++; 
    }
    TwoSatSolver tsat(sum);
    for (int i = 0; i < n; i++) {
        vector<int> c(7);
        for (int j = 0; j < 7; j++) {
            cin >> c[j];
        }
        for (int j = 0; j < 7; j++) for (int k = j + 1; k < 7; k++) {
            int u = cc[j][abs(c[j]) - 1];
            int v = cc[k][abs(c[k]) - 1]; 
            tsat.x_or_y_constraint(c[j] < 0, u, c[k] < 0, v);
        }
    }
    int xa, xb;
    cin >> xa >> xb;
    int u = cc[5][abs(xa) - 1];
    int v = cc[6][abs(xb) - 1];
    tsat.x_or_y_constraint(xa > 0, u, xa > 0, u);
    tsat.x_or_y_constraint(xb > 0, v, xb > 0, v);
    cout << (tsat.solve() ? "possible" : "impossible") << '\n'; 
    return 0;
}