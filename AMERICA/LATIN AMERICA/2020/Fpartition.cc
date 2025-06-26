#include "bits/stdc++.h"
using namespace std;
const int64_t INF = 1e14;
signed main(void)
{
    int N;
    while (cin >> N)
    {
        vector<int64_t> arr(N);
        vector<vector<int64_t>> dyn(2, vector<int64_t>(N));
        vector<int64_t> ret1(N), ret2(N);
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i];
        }
        for (int i = 0; i < N; i++)
        {
            stack<pair<int, int64_t>> stk;
            for (int j = 0; j < N; j++)
            {
                int64_t curr = 0;
                if (j) curr = max(curr, dyn[~i & 1][j - 1]);
                while (stk.size() && arr[stk.top().first] < arr[j])
                {
                    curr = max(curr, stk.top().second);
                    stk.pop();
                }
                dyn[i & 1][j] = curr + arr[j];
                if (stk.size())
                {
                    dyn[i & 1][j] = max(dyn[i & 1][j], dyn[i & 1][stk.top().first]);
                }
                stk.push({j, curr});
            }
            ret1[i] = dyn[i & 1][N - 1];
        }
        for (int i = 0; i < N; i++)
        {
            dyn[1][i] = INF;
        }
        for (int i = 0; i < N; i++)
        {
            stack<pair<int, int64_t>> stk;
            for (int j = 0; j < N; j++)
            {
                int64_t curr = INF;
                if (j) curr = min(curr, dyn[~i & 1][j - 1]);
                while (stk.size() && arr[stk.top().first] < arr[j])
                {
                    curr = min(curr, stk.top().second);
                    stk.pop();
                }
                dyn[i & 1][j] = curr + arr[j];
                if (stk.size())
                {
                    dyn[i & 1][j] = min(dyn[i & 1][j], dyn[i & 1][stk.top().first]);
                }
                else if (i == 0)
                {
                    dyn[i & 1][j] = arr[j];
                }
                stk.push({j, curr});
            }
            ret2[i] = dyn[i & 1][N - 1];
            cout << ret2[i] << " " << ret1[i] << '\n';
        }
    }
    return 0;
}