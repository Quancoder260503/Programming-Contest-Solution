#include "bits/stdc++.h"

using namespace std;

#define int64_t unsigned long long

const int64_t INF = 1e16;
const int maxf = 2500;
template <typename T>
pair<T, vector<int>> Hungarian(int n, int m, T c[][maxf])
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
        } 
        while (i != f);
    }
    T ret = 0;
    for (int i = 0; i < n; ++i)
        ret += c[i][L[i]];
    return {ret, L};
}

int64_t cost[maxf][maxf], c[maxf][maxf], o[maxf], e[maxf]; 

int main(void)
{
    int N; 
    cin >> N; 
    for(int i = 0; i < maxf; i++) for(int j = 0; j < maxf; j++) 
    {
        cost[i][j] = INF; 
    }
    for(int i = 1; i <= N; i++) for(int j = 1; j <= N; j++)
    {
        cin >> c[i][j]; 
    }
    int octr = 0, ectr = 0;
    for(int i = 0; i <= N; i++) 
    {
        if(i & 1) o[i] = octr++; 
        else      e[i] = ectr++; 
    }
    if(N % 2 == 0) N = N - 1; 
    for(int i = 0; i <= N; i++) if(i % 2 > 0)
    {
        for(int j = 0; j <= N; j++) if(j % 2 == 0)
        {
            cost[o[i]][e[j]] = c[i][j] + c[i][j + 2];  
        }
    } 
    auto ret = Hungarian<int64_t>(octr, ectr, cost); 
    cout << ret.first << '\n'; 
    return 0; 
}