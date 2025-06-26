#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
const int MAX = 50;
int adj[MAX][MAX];
int main(void)
{
    int N, M;
    while (cin >> N >> M)
    {
        vector<int64_t> dyn(1 << N, INF);
        vector<int> a(N);
        for (int i = 0; i < M; i++)
        {
            int U, V, C;
            cin >> U >> V >> C;
            a[U] += C;
            a[V] -= C;
        }
        dyn[0] = 0;
        for (int mask = 0; mask < (1 << N); mask++)
        {
            int acc = 0; 
            for (int i = 0; i < N; i++)
            {
                if (mask & (1 << i))
                {
                    dyn[mask] = min(dyn[mask], dyn[mask xor (1 << i)]);
                    acc += a[i];
                }
            }
            dyn[mask] += (acc != 0); 
        }
        cout << dyn[(1 << N) - 1] << '\n';
    }
    return 0;
}