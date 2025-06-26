#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e3 + 10
#define pii pair<int,int> 
#define mp make_pair
#define lint long long
int a[MAXN][MAXN];
int dp2[MAXN][MAXN] ;
int dp5[MAXN][MAXN];  
pii fa[MAXN][MAXN][2]; 
int n;
signed main(void)
{
    cin >> n;
    bool haszero = 0;
    int px, py;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            haszero = haszero | (a[i][j] == 0); 
            if(a[i][j] == 0)
            {
                px = i, py = j;
            }
        }
    }
    memset(dp2, 63, sizeof(dp2));
    memset(dp5, 63, sizeof(dp5));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int cur = a[i][j];
            int cnt2 = 0, cnt5 = 0;
            if(cur == 0) continue;
            while(cur % 2 == 0) cur = cur / 2, cnt2++; 
            while(cur % 5 == 0) cur = cur / 5, cnt5++;
            if(i == 0 && j == 0)
            {
                 dp2[i][j] = cnt2; 
                 dp5[i][j] = cnt5; 
            }
            if(i)
            {
                if(dp2[i][j] > dp2[i - 1][j] + cnt2)
                {
                     dp2[i][j] = dp2[i - 1][j] + cnt2; 
                     fa[i][j][0] = mp(i - 1, j); 
                }
                if (dp5[i][j] > dp5[i - 1][j] + cnt5)
                {
                     dp5[i][j] = dp5[i - 1][j] + cnt5;
                     fa[i][j][1] = mp(i - 1, j);
                }
            }
            if(j)
            {
                if (dp2[i][j] > dp2[i][j - 1] + cnt2)
                {
                     dp2[i][j] = dp2[i][j - 1] + cnt2;
                     fa[i][j][0] = mp(i, j - 1);
                }
                if (dp5[i][j] > dp5[i][j - 1] + cnt5)
                {
                     dp5[i][j] = dp5[i][j - 1] + cnt5;
                     fa[i][j][1] = mp(i, j - 1);
                }
            }
        }
    }
    int res = min(dp2[n - 1][n - 1], dp5[n - 1][n - 1]); 
    if(res > 0 && haszero)
    {
        puts("1"); 
        for(int i = 0; i < px; i++)
        {
            cout << "D"; 
        }
        for (int i = 0; i < py; i++)
        {
            cout << "R";
        }
        for(int i = px + 1; i < n; i++)
        {
            cout << "D";
        }
        for (int i = py + 1; i < n; i++)
        {
            cout << "R";
        }
        return 0;
    }
    cout << res << '\n'; 
    vector<char>ans; 
    fa[0][0][1] = fa[0][0][0] = mp(-1, -1); 
    int ku = n - 1, kv = n - 1;
    int opt = dp2[n - 1][n - 1] < dp5[n - 1][n - 1] ? 0 : 1; 
    while(fa[ku][kv][opt] != mp(-1, -1))
    {
         int u = fa[ku][kv][opt].first; 
         int v = fa[ku][kv][opt].second; 
         if(u + 1 == ku)
         {
             ans.push_back('D'); 
         }
         if(v + 1 == kv)
         {
             ans.push_back('R'); 
         }
         ku = u, kv = v; 
    }
    reverse(ans.begin(), ans.end()); 
    for(int i = 0; i < ans.size(); i++)
    {
         cout << ans[i];
    }
    return 0;
}
// Let DP2[i][j] = exponential of 2 in DP[i][j]
//     DP5[i][j] = exponential of 5 in DP[i][j]
//     --> solve extensively for 2 case and find out the minimum between DP2[n][n] && DP5[n][n]
// 
