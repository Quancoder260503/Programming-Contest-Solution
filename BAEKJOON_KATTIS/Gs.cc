#include "bits/stdc++.h"
using namespace std;
const int N = 17;
#define double long double
struct matrix
{
    double mat[N][N];
    void init()
    {
        memset(mat, 0.0, sizeof(mat));
    }
    void print(int n = N)
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                cout << mat[i][j] << ' '; 
            }
            cout << '\n'; 
        }
    }
};
matrix operator*(const matrix a, const matrix b)
{
    matrix c;
    c.init();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                c.mat[i][j] += a.mat[i][k] * b.mat[k][j]; 
            }
        }
    }
    return c; 
}
signed main(void)
{
    int T;
    cin >> T;
    while (T--)
    {
        int n, s, t;
        cin >> n >> s >> t;
        --s, --t; 
        vector<int> sums(n);
        matrix adj;
        adj.init(); 
        for (int i = 0; i < n - 1; i++)
        {
            int u, v, c;
            cin >> u >> v >> c;
            --u, --v;
            adj.mat[u][v] = adj.mat[v][u] = c;
            sums[u] += c;
            sums[v] += c;
        }
        for (int i = 0; i < n; i++)
        {
            if (sums[i] == 0) continue;
            for (int j = 0; j < n; j++)
            {
                adj.mat[i][j] = adj.mat[i][j] / (double) sums[i];
            }
        }
        matrix coef;
        coef.init(); 
        for(int i = 0; i < n; i++) coef.mat[i][i] = 1.0; 
        int M = 10000; 
        double ret = 0; 
        for(int i = 1; i < M; i++)
        { 
            coef = coef * adj; 
            ret += i * coef.mat[s][t];
            coef.mat[s][t] = 0;
        }
        cout << fixed << setprecision(5) << ret << '\n'; 
    }
    return 0;
}