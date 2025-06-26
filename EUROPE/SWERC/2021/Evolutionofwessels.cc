#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int T;
    cin >> T;
    while (T--)
    {
        string U, V;
        cin >> U >> V;
        vector<int> ctrA = {0, 0, 0};
        vector<int> ctrB = {0, 0, 0};
        for (int i = 0; i < U.length(); i++) ctrA[U[i] - 'A']++;
        for (int i = 0; i < V.length(); i++) ctrB[V[i] - 'A']++;
        int ret = 1;
        for (int i = 0; i < 3; i++)
        {
            ret = ret & (abs(ctrA[i] - ctrB[i]) % 2 == 0);
        }
        if (!ret)
        {
            cout << "NO" << '\n';
            continue;
        }
        int N;
        N = U.length();
        string U2, V2;
        for (int i = 0; i < N; i++)
            if (U[i] != 'B')
                U2 += U[i];
        N = V.length();
        for (int i = 0; i < N; i++)
            if (V[i] != 'B')
                V2 += V[i];
        while (true)
        {
            string U3, V3;
            int ret = 0;
            N = U2.length();
            for (int i = 0; i < N; i++)
            {
                if (i + 1 < N && (U2.substr(i, 2) == "AA" || U2.substr(i, 2) == "CC"))
                {
                    ret = 1;
                    i++;
                }
                else
                {
                    U3 += U2[i];
                }
            }
            N = V2.length();
            for (int i = 0; i < N; i++)
            {
                if (i + 1 < N && (V2.substr(i, 2) == "AA" || V2.substr(i, 2) == "CC"))
                {
                    ret = 1;
                    i++;
                }
                else
                {
                    V3 += V2[i];
                }
            }
            if (!ret) break;
            V2 = V3;
            U2 = U3;
        }
        cout << (U2 == V2 ? "YES" : "NO") << '\n';
    }
    return 0;
}