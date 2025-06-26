#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n, m; 
    cin >> n >> m; 
    vector<vector<int>>ctr(2, vector<int>(n + 1, 0)); 
    for(int j = 0; j < 2; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            int x;
            cin >> x;
            ctr[j][i] = ctr[j][i - 1] + (x & 1);
        }
    }
    for(int i = 0; i < m; i++)
    {
        int ra, rb, ca, cb;
        cin >> ra >> ca >> rb >> cb; 
        int r = ctr[0][max(ra, rb)] - ctr[0][min(ra, rb) - 1]; 
        int c = ctr[1][max(ca, cb)] - ctr[1][min(ca, cb) - 1]; 
        int ro = (r == max(ra, rb) - min(ra, rb) + 1); 
        int co = (c == max(ca, cb) - min(ca, cb) + 1); 
        cout << ((ro & co) || (r == 0 && c == 0) ? "YES" : "NO") << '\n'; 
    }
    return 0;
}