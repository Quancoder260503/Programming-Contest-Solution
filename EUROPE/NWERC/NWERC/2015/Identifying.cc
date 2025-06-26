#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    string S;
    while (cin >> S)
    {
        int N = S.length();
        int64_t x = 0, y = 0;
        for (int i = 0; i < N; i++)
        {
            x = x * 2;
            y = y * 2;
            x = x + (S[i] == '1' || S[i] == '3');
            y = y + (S[i] == '2' || S[i] == '3');
        }
        cout << N << " " << x << " " << y << '\n';
    }
    return 0;
}