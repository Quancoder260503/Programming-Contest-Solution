#include "bits/stdc++.h"

using namespace std;
typedef double T; // long double, Rational, double + mod<P>...

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
int main(void)
{
    int N;
    cout << fixed << setprecision(10);
    while (cin >> N)
    {
        vector<T> rx(N), ry(N);
        for (int i = 0; i < N; i++) cin >> rx[i] >> ry[i];
        int ptr = 0;
        vector<vector<T>> a(N * N, vector<T>(N));
        vector<T> b(N * N);
        vector<T> c(N, 1.0);
        for (int i = 0; i < N; i++) for (int j = 0; j < i; j++)
        {
                a[ptr][i] = 1;
                a[ptr][j] = 1;
                b[ptr++] = sqrt((rx[i] - rx[j]) * (rx[i] - rx[j]) + (ry[i] - ry[j]) * (ry[i] - ry[j]));
        }
        LPSolver lp(a, b, c);
        vector<T> ret;
        cout << lp.solve(ret) * 2 * acos(-1) << '\n';
    }
    return 0;
}
