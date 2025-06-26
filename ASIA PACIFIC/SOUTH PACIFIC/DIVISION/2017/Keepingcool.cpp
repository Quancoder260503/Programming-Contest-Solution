#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)200;
typedef pair<double, double> Point;
const double EPS = 1e-8;
double dist[MAXN][MAXN];
#define x first
#define y second
double dp[MAXN][MAXN];
int n;
double K;
Point P[MAXN];
double R[MAXN];
signed main(void)
{
    P[0].x = P[0].y = 0;
    cin >> n >> K;
    int N = n + 1;
    cin >> P[N].x >> P[N].y;
    R[0] = R[N] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> P[i].x >> P[i].y >> R[i];
    }
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            dp[i][j] = 1e9;
        }
    }
    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            dist[i][j] = max(0.0, hypot(P[i].x - P[j].x, P[i].y - P[j].y) - R[i] - R[j]);
            if (dist[i][j] < K + EPS) dp[i][j] = dist[i][j];
        }
    }
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    double ans = 1e9;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dist[i][N] + dist[N][j] <= K)
            {
                ans = min(ans, dp[0][i] + dist[i][N] + dist[N][j] + dp[j][0]);
            }
        }
    }
    if (ans >= 1e9)
    {
        puts("-1");
        return 0;
    }
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}