#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAX 11
int n, m;
lint k;
int L, R;
lint g[MAX << 1][MAX << 1];
using T = vector<vector<map<lint, lint> > >;
T dp(MAX << 1, vector<map<lint, lint> >(MAX));
lint ans = 0; 
void dfs(int x, int y, lint tot)
{
     if(x + y == L)
     {
         dp[x][y][tot] += 1;
         return; 
     }
     if(x + 1 < n) dfs(x + 1, y, tot xor g[x + 1][y]);
     if(y + 1 < m) dfs(x, y + 1, tot xor g[x][y + 1]); 
}
void dfs2(int x, int y, lint tot)
{
     if ((n + m - 2) - (x + y) == R)
     {
        if(x > 0) ans += dp[x - 1][y][k xor tot];
        if(y > 0) ans += dp[x][y - 1][k xor tot];
        return;
     }
     if (x > 0) dfs2(x - 1, y, tot xor g[x - 1][y]);
     if (y > 0) dfs2(x, y - 1, tot xor g[x][y - 1]);
}
signed main(void)
{
    cin >> n >> m >> k;
    lint xors = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
            xors = xors xor g[i][j];
        }
    }
    if (m == 1 || n == 1)
    {
        cout << (xors == k) << '\n';
    }
    else
    {
        int N = n + m - 2;
        L = N / 2;
        R = N - L - 1; 
        dfs(0, 0, g[0][0]); 
        dfs2(n - 1, m - 1, g[n - 1][m - 1]); 
        cout << ans << '\n';
    }
    return 0;
}