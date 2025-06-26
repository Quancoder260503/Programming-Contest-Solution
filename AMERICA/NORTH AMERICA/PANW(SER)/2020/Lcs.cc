#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define N 50
#define M (int) 1e5 + 10
int pos[M][N], n, m, dp[N];
char a[M][N];
int main()
{
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];
            pos[i][a[i][j] - '0'] = j;
        }
    }
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = 1;
        for (int j = 1; j < i; j++)
        {
            int x = a[1][j] - '0';
            int y = a[1][i] - '0';
            bool can = 1;
            for (int k = 1; k <= m; k++)
            {
                if (pos[k][x] > pos[k][y])
                    can = 0;
            }
            if (can)
            {
                dp[i] = max(dp[i], dp[j] + 1);
                ans = max(ans, dp[i]);
            }
        }
    }
    cout << ans << endl;
}