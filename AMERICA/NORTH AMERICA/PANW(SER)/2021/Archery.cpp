#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)250;
const int N = 18;
int n, m;
double p[N];
int s[N];
struct matrix
{
    double arr[MAXN][MAXN];
    void init(int L)
    {
        for (int i = 0; i < L; i++)
        {
            fill(arr[i], arr[i] + L, 0);
        }
    }
    void rref(int L)
    {
        for (int i = 0; i < L; i++)
        {
            for (int j = i + 1; j < L; j++)
            {
                assert(arr[i][i] != 0);
                double ratio = arr[j][i] / arr[i][i];
                for (int k = 0; k < L + 1; k++)
                {
                    arr[j][k] = arr[j][k] - ratio * arr[i][k];
                }
            }
        }
        arr[L - 1][L - 1] = arr[L - 1][L] / arr[L - 1][L];
        for (int i = L - 2; i >= 0; i--)
        {
            for (int j = i + 1; j < L; j++)
            {
                arr[i][L] = arr[i][L] - arr[j][L] * arr[i][j];
            }
            arr[i][L] = arr[i][L] / arr[i][i];
        }
    }
    void print(int L)
    {
        for (int i = 0; i < L; i++)
        {
            for (int j = 0; j < L + 1; j++)
            {
                cout << arr[i][j] << " ";
            }
            cout << '\n';
        }
    }
};
double f[N][N][2];
double dp[(1 << N)];
signed main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix c;
            int L = 2 * s[i] + 1;
            c.init(L + 1);
            c.arr[0][L] = 0;
            c.arr[L - 1][L] = 1;
            for (int k = 0; k < L; k++)
            {
                c.arr[k][k] = 1;
            }
            for (int k = 1; k + 1 < L; k++)
            {
                c.arr[k][k - 1] = -(1.0 - p[j]);
                c.arr[k][k + 1] = -p[j];
            }
            c.rref(L);
            int dist = (s[i] - (i == 0 ? 0 : s[i - 1]));
            f[i][j][0] = c.arr[dist][L];
            f[i][j][1] = c.arr[L - 1 - dist][L];
        }
    }
    dp[0] = 1.0;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        int curr = __builtin_popcount(mask) - 1; 
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                dp[mask] = max(dp[mask], f[curr][i][1] * dp[mask xor (1 << i)] + f[curr][i][0] * (1.0 - dp[mask xor (1 << i)]));
            }
        }
    }
    cout << setprecision(12) << dp[(1 << n) - 1] << '\n';
    return 0;
}