#include "bits/stdc++.h"
using namespace std;
const int M = 31;
const int L = 62 * 200;
int64_t dyn[M][M][L];
int A[M][M];
int R, C;
int64_t K;
int64_t doit(int r, int c, int sum)
{
    if (r > R || c > C || sum < 0)
        return 0;
    if (r == R && c == C && sum == A[r][c])
        return 1;
    if (dyn[r][c][sum] != -1)
        return dyn[r][c][sum];
    int64_t &ret = dyn[r][c][sum];
    ret = doit(r + 1, c, sum - A[r][c]) + doit(r, c + 1, sum - A[r][c]);
    return ret;
};
void backtrack(int r, int c, int sum, int64_t ord)
{
    if (r == R && c == C)
        return;
    if (doit(r + 1, c, sum - A[r][c]) >= ord)
    {
        cout << "D";
        backtrack(r + 1, c, sum - A[r][c], ord);
    }
    else if (doit(r, c + 1, sum - A[r][c]) > 0)
    {
        cout << "R";
        backtrack(r, c + 1, sum - A[r][c], ord - doit(r + 1, c, sum - A[r][c]));
    }
    return;
}
signed main(void)
{
    while (cin >> R >> C >> K)
    {
        memset(dyn, -1, sizeof(dyn));
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
            {
                cin >> A[i][j];
            }
        for (int tot = L - 1; tot >= 0; tot--)
            doit(1, 1, tot);
        int tot;
        for (tot = L - 1; tot >= 0; tot--)
        {
            if (K <= dyn[1][1][tot])
                break;
            K = K - dyn[1][1][tot];
        }
        backtrack(1, 1, tot, K);
    }
    return 0;
}
/*
2 3 3
1 2 3
2 2 3
*/