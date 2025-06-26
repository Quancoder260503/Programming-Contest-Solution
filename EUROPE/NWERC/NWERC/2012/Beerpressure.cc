#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N, K;
    while (cin >> N >> K)
    {
        vector<int> arr(N);
        int M = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> arr[i], M += arr[i];
        }
        vector<int64_t> H = {1, 1000, 1000000, 1000000000, 1000000000000}; 
        map<int64_t, double> dyn[2];
        int64_t H_value = 0; 
        for(int i = 0; i < arr.size(); i++) H_value += 1LL * arr[i] * H[i]; 
        dyn[0][H_value] = 1.0;
        for (int i = 0; i < K - M; i++)
        {
            for (auto it : dyn[0])
            {
                vector<int> pcurr(N);
                H_value = it.first;
                for(int j = N - 1; j >= 0; j--)
                {
                    pcurr[j] = H_value / H[j]; 
                    H_value = H_value - (H_value / H[j]) * H[j]; 
                }
                for (int j = 0; j < N; j++)
                {
                    dyn[1][it.first + H[j]] += (pcurr[j] / (1.0 * (M + i))) * it.second;
                }
            }
            dyn[0] = dyn[1];
            dyn[1].clear();
        }
        vector<double> ret(N);
        for (auto it : dyn[0])
        {
            int ans = 0;
            vector<int> pcurr(N);
            H_value = it.first;
            for (int j = N - 1; j >= 0; j--)
            {
                pcurr[j] = H_value / H[j];
                H_value = H_value - (H_value / H[j]) * H[j];
            }
            for (auto v : pcurr) ans = max(ans, v);
            int ctr = 0;
            for (int i = 0; i < N; i++) ctr += (pcurr[i] == ans);
            for (int i = 0; i < N; i++)
                if (pcurr[i] == ans)
                {
                    ret[i] += it.second / ctr * 100.0;
                }
        }
        cout << fixed << setprecision(2);
        for (int i = 0; i < N; i++)
        {
            cout << "pub " << i + 1 << ": " << ret[i] << " %" << '\n';
        }
    }
    return 0;
}