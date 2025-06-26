#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)5e3 + 10
#define vs vector<string>
int n, w;
string a[MAXN];
int dp[MAXN], dp2[MAXN][MAXN];
int to[MAXN];
vector<string> res[MAXN];
bool check(int h)
{
    memset(dp, 63, sizeof(dp));
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; i - j < h && j > 0; j--)
        {
            if (dp[i] > dp[j - 1] + (int)dp2[j][i])
            {
                dp[i] = dp[j - 1] + dp2[j][i];
                to[i] = j;
            }
        }
    }
    int curr = n;
    int space = 0;
    while (curr)
    {
        space++;
        curr = to[curr] - 1;
    }
    return dp[n] + space - 1 <= w;
}
signed main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> w;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        dp2[i][i] = (int)a[i].length();
        for (int j = i + 1; j <= n; j++)
        {
            dp2[i][j] = max(dp2[i][j - 1], (int)a[j].length());
        }
    }
    int lo = 1;
    int hi = n;
    while (lo < hi)
    {
        int mid = (lo + hi) / 2;
        if (check(mid))
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    check(lo);
    int curr = n;
    vector<int> width;
    curr = n;
    while (curr)
    {
        string temp;
        width.push_back(dp2[to[curr]][curr]);
        for (int i = to[curr]; i <= curr; i++)
        {
            if(curr != n) while (a[i].length() < dp2[to[curr]][curr]) a[i] = a[i] + " ";
            res[i - to[curr]].push_back(a[i]);
        }
        if(curr != n)
        {
            while (temp.length() < dp2[to[curr]][curr])
                temp = temp + " ";
            for (int i = curr - to[curr] + 1; i <= lo; i++)
            {
                res[i].push_back(temp);
            }
        }
        curr = to[curr] - 1;
    }
    cout << lo << " " << (int)width.size() << '\n';
    for (int i = width.size() - 1; i >= 0; i--)
    {
        cout << width[i] << " ";
    }
    cout << endl;
    for (int i = 0; i <= lo; i++)
    {
        for (int j = res[i].size() - 1; j >= 0; j--)
        {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}