#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int K;
    string S, T;
    cin >> K >> S >> T;
    int N = S.length();
    int same = 0;
    for (int i = 0; i < N; i++)
    {
        same += (S[i] == T[i]);
    }
    cout << min(same, K) + min(N - same, N - K) << '\n'; 
    return 0;
}