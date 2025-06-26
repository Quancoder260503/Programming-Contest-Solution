#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int inf = 1e8;
const int N = 2500;
template <typename T>
pair<T, vector<int>> Hungarian(int n, int m, T c[][N])
{
    vector<T> v(m), dist(m);
    vector<int> L(n, -1), R(m, -1);
    vector<int> index(m), prev(m);
    auto getc = [&](int i, int j)
    { return c[i][j] - v[j]; };

    iota(index.begin(), index.end(), 0);
    for (int f = 0; f < n; ++f)
    {
        for (int j = 0; j < m; ++j)
        {
            dist[j] = getc(f, j), prev[j] = f;
        }
        T w = 0;
        int j, l = 0, s = 0, t = 0;
        while (true)
        {
            if (s == t)
            {
                l = s, w = dist[index[t++]];
                for (int k = t; k < m; ++k)
                {
                    j = index[k];
                    T h = dist[j];
                    if (h <= w)
                    {
                        if (h < w)
                            t = s, w = h;
                        index[k] = index[t], index[t++] = j;
                    }
                }
                for (int k = s; k < t; ++k)
                {
                    j = index[k];
                    if (R[j] < 0)
                        goto augment;
                }
            }
            int q = index[s++], i = R[q];
            for (int k = t; k < m; ++k)
            {
                j = index[k];
                T h = getc(i, j) - getc(i, q) + w;
                if (h < dist[j])
                {
                    dist[j] = h, prev[j] = i;
                    if (h == w)
                    {
                        if (R[j] < 0)
                            goto augment;
                        index[k] = index[t], index[t++] = j;
                    }
                }
            }
        }
    augment:
        for (int k = 0; k < l; ++k)
            v[index[k]] += dist[index[k]] - w;
        int i;
        do
        {
            i = R[j] = prev[j];
            swap(j, L[i]);
        } while (i != f);
    }
    T ret = 0;
    for (int i = 0; i < n; ++i)
        ret += c[i][L[i]];
    return {ret, L};
}
int c[N][N];
int n, m;
signed main(void)
{
    cin >> n >> m;
    memset(c, 63, sizeof(c)); 
    for (int i = 0; i < m; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        --u, --v; 
        c[u][v] = -cost;
    }
    for (int i = 0; i < n; i++)
    {
        c[i][i] = 0; 
    }
    auto [ans, _] = Hungarian<int>(n, n, c); 
    cout << fixed << setprecision(10) << (-ans * 5.0 / 100.0) << '\n';
    return 0;
}