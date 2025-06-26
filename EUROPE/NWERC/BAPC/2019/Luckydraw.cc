#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define double long double
const int M = 1001;
signed main(void)
{
    int N, K;
    double p;
    while (cin >> N >> K >> p)
    {
        vector<double> P(M);
        vector<vector<double>> C(M, vector<double>(M));
        C[0][0] = 1.0;
        for (int i = 1; i < M; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                C[i][j] = C[i - 1][j] + (j ? C[i - 1][j - 1] : j);
            }
        }
        double tot = 0;
        double ret = 0;
        for (int i = K; i < M; i++)
        {
            ret += C[i - 1][K - 1] * powl(p, i - K) * powl(1.0 - p, K) * powl(tot, N - 1);
            tot += C[i - 1][K - 1] * powl(p, i - K) * powl(1.0 - p, K);
        }
        cout << fixed << setprecision(10) << 1 - ret * N << '\n';
    }
    return 0;
}