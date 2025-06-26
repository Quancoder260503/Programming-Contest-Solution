#include "bits/stdc++.h"
using namespace std;
const int MAXN = 3000;
#define lint long long
const int N = 1011;
lint c[N][N];
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
int n;
signed main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &c[i][j]);
        }
    }
    auto [cost, match] = Hungarian<lint>(n, n, c); 
    cout << cost << '\n'; 
    return 0;
}