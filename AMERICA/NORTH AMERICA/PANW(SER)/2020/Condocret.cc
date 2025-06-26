#include "bits/stdc++.h"

using namespace std;
typedef double T; // long double, Rational, double + mod<P>...

const int maxf = 1e6 + 2;
const T EPS = 1e-2;

const T eps = 1e-8, inf = 1 / .0;
#define MP make_pair
#define ltj(X)                                      \
    if (s == -1 || MP(X[j], N[j]) < MP(X[s], N[s])) \
    s = j

struct LPSolver
{
    int m, n;
    vector<int> N, B;
    vector<vector<T>> D;
    LPSolver(const vector<vector<T>> &A, const vector<T> &b, const vector<T> &c) : m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, vector<T>(n + 2))
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                D[i][j] = A[i][j];
        for (int i = 0; i < m; i++)
        {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++)
        {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }
    void pivot(int r, int s)
    {
        T *a = D[r].data(), inv = 1 / a[s];
        for (int i = 0; i < m + 2; i++)
            if (i != r && abs(D[i][s]) > eps)
            {
                T *b = D[i].data(), inv2 = b[s] * inv;
                for (int j = 0; j < n + 2; j++)
                    b[j] -= a[j] * inv2;
                b[s] = a[s] * inv2;
            }
        for (int j = 0; j < n + 2; j++)
            if (j != s)
                D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++)
            if (i != r)
                D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }
    bool simplex(int phase)
    {
        int x = m + phase - 1;
        for (;;)
        {
            int s = -1;
            for (int j = 0; j < n + 1; j++)
                if (N[j] != -phase)
                    ltj(D[x]);
            if (D[x][s] >= -eps)
                return true;
            int r = -1;
            for (int i = 0; i < m; i++)
            {
                if (D[i][s] <= eps)
                    continue;
                if (r == -1 || MP(D[i][n + 1] / D[i][s], B[i]) < MP(D[r][n + 1] / D[r][s], B[r]))
                    r = i;
            }
            if (r == -1)
                return false;
            pivot(r, s);
        }
    }

    T solve(vector<T> &x)
    {
        int r = 0;
        for (int i = 1; i < m; i++)
            if (D[i][n + 1] < D[r][n + 1])
                r = i;
        if (D[r][n + 1] < -eps)
        {
            pivot(r, n);
            if (!simplex(2) || D[m + 1][n + 1] < -eps)
                return -inf;
            for (int i = 0; i < m; i++)
                if (B[i] == -1)
                {
                    int s = 0;
                    for (int j = 1; j < n + 1; j++)
                        ltj(D[i]);
                    pivot(i, s);
                }
        }
        bool ok = simplex(1);
        x = vector<T>(n);
        for (int i = 0; i < m; i++)
            if (B[i] < n)
                x[B[i]] = D[i][n + 1];
        return ok ? D[m][n + 1] : inf;
    }
};

vector<string> perms;
vector<int> fa;
vector<vector<T>> graph, adj;

void find_perm(int n)
{
    string ret = "";
    for (int i = 0; i < n; i++)
        ret += (i + 'A');
    do
    {
        perms.push_back(ret);
    } while (next_permutation(ret.begin(), ret.end()));
}

void find_graph(int n, int curr)
{
    // generate cyclic functional graph
    if (curr == n)
    {
        vector<T> cgraph;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                if (fa[i] == j)
                    cgraph.push_back(1);
                else if (fa[j] == i)
                    cgraph.push_back(-1);
                else
                    cgraph.push_back(0);
            }
        graph.push_back(cgraph);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (i == curr)
                continue;
            if (i < curr && fa[i] == curr)
                continue;
            fa.push_back(i);
            find_graph(n, curr + 1);
            fa.pop_back();
        }
    }
}

void find_adj(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            adj.push_back({});
            for (auto perm : perms)
            {
                if (perm.find('A' + i) < perm.find('A' + j))
                {
                    adj.back().push_back(1);
                }
                else
                {
                    adj.back().push_back(-1);
                }
            }
        }
    }
}
vector<int> fact = {1, 1, 2, 6, 24, 120, 720};
int main(void)
{
    int N, K;
    while (cin >> N >> K)
    {
        find_perm(N);
        find_adj(N);
        find_graph(N, 0);
        int dim = fact[N];
        vector<T> C(dim, -1), din(dim);
        for (int i = 0; i < K; i++)
        {
            string curr;
            T cost;
            cin >> curr >> cost;
            din[find(perms.begin(), perms.end(), curr) - perms.begin()] += cost;
        }
        T ret = 1e8;
        for (int prob = 0; prob <= dim; prob++)
        {
            if (prob < dim)
                din[prob]++;
            for (int i = 0; i < graph.size(); i++)
            {
                vector<vector<T>> A(N);
                vector<T> B(N, -1);
                int ptr = 0;
                for (int j = 0; j < graph[i].size(); j++)
                {
                    if(graph[i][j] == 0) continue; 
                    A[ptr] = adj[j];
                    for (int k = 0; k < dim; k++)
                    {
                        A[ptr][k] = A[ptr][k] * graph[i][j];
                        B[ptr] -= A[ptr][k] * din[k];
                    }
                    ptr++;
                }
                vector<T> x;
                LPSolver lp(A, B, C);
                T res = -lp.solve(x);
                if (prob < dim)
                    res++;
                int flag = 1;
                for (int k = 0; k < dim; k++)
                    flag = flag & ((abs(round(x[i]) - x[i])) <= EPS);
                if (flag)
                    ret = min(ret, res);
            }
            if (prob < dim)
                din[prob]--;
        }
        cout << lround(ret) << '\n';
    }
    return 0;
}
