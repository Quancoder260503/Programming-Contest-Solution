#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    while (cin >> n)
    {
        int N = (1 << n);
        int M = (N * N - 1) / 3 + 1;
        vector<vector<int>> g(N, vector<int>(N));
        vector<int> cnt(M);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> g[i][j];
                cnt[g[i][j]]++;
            }
        }
        if (cnt[0] > 1) goto done;
        for (int i = 1; i < M; i++)
        {
            if (cnt[i] == 3) continue; 
            goto done; 
        }
        vector<int>vis(M); 
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if(i + 1 < N && 0 < j && g[i][j] == g[i + 1][j] && g[i][j] == g[i][j - 1]) vis[g[i][j]] = 1; 
                if(i + 1 < N && j < N && g[i][j] == g[i + 1][j] && g[i][j] == g[i][j + 1]) vis[g[i][j]] = 1; 
                if(j + 1 < N && 0 < i && g[i][j] == g[i - 1][j] && g[i][j] == g[i][j + 1]) vis[g[i][j]] = 1; 
                if(0 < j     && 0 < i && g[i][j] == g[i - 1][j] && g[i][j] == g[i][j - 1]) vis[g[i][j]] = 1; 
            }
        }
        vis[0] = 1; 
        if(*min_element(vis.begin(), vis.end()) == 0) goto done; 
        cout << 1 << '\n';
        exit(0); 
    }
done:
    cout << 0 << '\n';
    return 0;
}