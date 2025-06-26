#include "bits/stdc++.h"

using namespace std;

const int maxf = 7000;

int dyn[maxf][maxf], cc[maxf][maxf], g[maxf][maxf];

int main(void)
{

    int n, m, d, q;
    cin >> n >> m >> d >> q;
    for(int i = 0; i < d; i++) { 
        int x1, y1, x2, y2; 
        cin >> x1 >> x2 >> y1 >> y2; 
        for(int x = x1 + 1; x <= x2; x++) for(int y = y1 + 1; y <= y2; y++){
            g[y][x] = 1; 
        }
    }
    for (int i = 1; i <= m; i++) for (int j = 1; j <= n; j++) { 
        if(!g[i][j]) dyn[i][j] = 1 + dyn[i - 1][j];
    }
    for (int i = 1; i <= m; i++)
    {
        int c = -1;
        vector<pair<int, int>> stk;
        for (int j = 0; j <= n + 1; j++)
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
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cc[i + 1][j] += cc[i][j];
        }
        int acc1 = 0, acc2 = 0;
        for (int j = n; j >= 1; j--)
        {
            acc1 += cc[i][j];
            acc2 += acc1;
            cc[i][j] = acc2;
        }
    }
    for(int i = 0; i < q; i++) { 
        int x, y; 
        cin >> x >> y; 
        cout << cc[y][x] << '\n'; 
    }
    return 0;
}