#include "bits/stdc++.h"
using namespace std;
const int L = 100;
signed main(void)
{
    int N, M, K;
    while (cin >> N >> M >> K)
    {
        vector<vector<int>> dyn(L, vector<int>(L));
        vector<int64_t> area;
        int64_t ret = 0;
        for (int i = 0; i < N; i++)
        {
            string S;
            cin >> S;
            for (int j = 0; j < M; j++)
            {
                assert(i + L / 2 < L && j + L / 2 < L); 
                dyn[i + L / 2][j + L / 2] = (S[j] == '#');
                ret += (S[j] == '#');
            }
        }
        area.push_back(ret);
        int brute = 12;
        const int dx[8] = {1, -1, 0, 0, 1, -1, 1, -1};
        const int dy[8] = {0, 0, -1, 1, -1, 1, 1, -1};
        for (int _ = 0; _ < brute; _++)
        {
            vector<vector<int>> ndyn(L, vector<int>(L));
            for (int i = 0; i < L; i++)
            {
                for (int j = 0; j < L; j++)
                {
                    for (int k = 0; k < 8; k++)
                    {
                        int px = i + dx[k];
                        int py = j + dy[k];
                        if (0 <= px && px < L && 0 <= py && py < L)
                        {
                            ndyn[px][py] |= (dyn[i][j] | dyn[px][py]);
                        }
                    }
                }
            }
            dyn.swap(ndyn);
            ret = 0;
            for (int i = 0; i < L; i++)
            {
                for (int j = 0; j < L; j++)
                {
                    ret += dyn[i][j];
                }
            }
            area.push_back(ret);
        }
        /*
        for (int i = 0; i < L; i++)
        {
            for (int j = 0; j < L; j++)
            {
               cout << (dyn[i][j] ? '#' : '.') << " ";
            }
            cout << '\n';
        }
        */
        int64_t added1 = area.back() - area[area.size() - 2];
        int64_t added2 = area[area.size() - 2] - area[area.size() - 3];
        int64_t sum = added1;
        while (area.size() <= K)
        {
            sum += (added1 - added2);
            area.push_back(area.back() + sum);
        }
        cout << area[K] << '\n';
    }
    return 0;
}