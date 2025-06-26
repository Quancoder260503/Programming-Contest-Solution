#include "bits/stdc++.h"

using namespace std;

int n, m; 

int main(void)
{
    while(cin >> n >> m)
    {
        int ret = 0; 
        vector<vector<char>>g(n, vector<char>(m));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> g[i][j];
        vector<vector<int>> rg(n, vector<int>(m));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        {
            rg[i][j] = (j ? rg[i][j - 1] : 0) + (g[i][j] == 'G'); 
        }
        auto chk_rec = [&](int d)
        {
            for (int j = 0; j + d <= m; j++)
            { 
                int ctr = 0; 
                for (int i = 0; i < n; i++)
                {
                   int ng = rg[i][j + d - 1] - (j ? rg[i][j - 1] : 0); 
                   if(ng == d || ng == 0) ctr++; 
                   else ctr = 0; 
                   if(ctr == d) return 1;  
                }
            }
            return 0;
        };
        int L = 0;
        int R = max(n, m) + 2;
        while (L < R)
        {
            int mid = (L + R + 1) / 2;
            if (chk_rec(mid)) L = mid;
            else R = mid - 1;
        }
        cout << L * L << '\n'; 
    }
    return 0; 
}