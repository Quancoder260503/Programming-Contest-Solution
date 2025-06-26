#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1e6 + 2;
const int mod = 1e9 + 7;
mt19937_64 rng(2333333);
int64_t P2[MAXN];
int64_t P[MAXN];
void init(void)
{
    P2[0] = 1;
    for (int i = 1; i < MAXN; i++)
        P2[i] = P2[i - 1] * 2 % mod;
    return;
}
int main(void)
{
    int N;
    init();
    while (cin >> N)
    {
        vector<int> a(N), b(N);
        vector<int> coord;
        for (int i = 0; i < N; i++)
        {
            cin >> a[i];
            coord.push_back(a[i]);
        }
        for (int i = 0; i < N; i++)
        {
            cin >> b[i];
            coord.push_back(b[i]);
        }
        sort(coord.begin(), coord.end());
        coord.erase(unique(coord.begin(), coord.end()), coord.end());
        int64_t pA = 0, pB = 0, pA2 = 0, pB2 = 0;
        for (int i = 0; i < coord.size(); i++)
            P[i] = rng();
        vector<int64_t> diff;
        for (int i = 0; i < N; i++)
        {
            pA = (pA + P[lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin()]);
            pB = (pB + P[lower_bound(coord.begin(), coord.end(), b[i]) - coord.begin()]);
            diff.push_back(pA - pB);
        }
        map<int64_t, int> ctr;
        int64_t ret = 0;
        for (auto it : diff)
            ctr[it]++;
        for (auto it : ctr)
        {
            ret = (ret + P2[it.second] - it.second + mod - 1) % mod;
        }
        cout << ret << '\n';
    }
    return 0;
}