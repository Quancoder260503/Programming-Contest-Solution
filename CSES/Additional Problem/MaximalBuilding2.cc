#include "bits/stdc++.h"

using namespace std;

const int maxf = 7000;

int dyn[maxf][maxf], cc[maxf][maxf];

int main(void)
{

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            char c;
            cin >> c;
            if (c == '.')
                dyn[i][j] = 1 + dyn[i - 1][j];
        }
    for (int i = 1; i <= n; i++)
    {
        int c = -1;
        vector<pair<int, int>> stk;
        for (int j = 0; j <= m + 1; j++)
        {
            int w = 0;
            while (c > 0 && stk[c].second >= dyn[i][j])
            {
                w += stk[c].first;
                int h = max(dyn[i][j], stk[c - 1].second);
                cc[h + 1][w]++;
                cc[stk[c].second + 1][w]--;
                c--; 
                stk.pop_back();
            }
            c++;
            stk.push_back({w + 1, dyn[i][j]});
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cc[i + 1][j] += cc[i][j];
        }
        int acc1= 0, acc2 = 0;
        for(int j = m; j >= 1; j--)
        {
            acc1 += cc[i][j]; 
            acc2 += acc1; 
            cc[i][j] = acc2; 
        }
        for(int j = 1; j <= m; j++) cout << cc[i][j] << " "; 
        cout << '\n'; 
    }
    return 0;
}