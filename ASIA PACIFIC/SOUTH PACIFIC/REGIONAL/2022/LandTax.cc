#include "bits/stdc++.h"
using namespace std;
#define mp make_pair
#define N 300005
#define inf 1000000000000
long long DP[N];
long long W[N];
long long H[N];
long long PF[N];
int n, L;
multiset<long long> ms;
using pii = pair<int, int>;
using T = pair<long long, pair<long long, pii>>;
deque<T> stk;
signed main(void)
{
    scanf("%d%d", &n, &L);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &H[i], &W[i]);
    for (int i = 1; i <= n; i++)
        PF[i] = PF[i - 1] + W[i];
    int curr = 0;
    for (int i = 1; i <= n; i++)
    {
        T tup = mp(DP[i - 1] + H[i], mp(H[i], mp(i - 1, i - 1)));
        while (stk.size() && stk.back().second.first <= H[i])
        {
            T tupj = stk.back();
            tup.second.second.first = tupj.second.second.first;
            ms.erase(ms.find(tupj.first));
            tup.first = DP[tup.second.second.first] + H[i];
            stk.pop_back();
        }
        stk.push_back(tup);
        ms.insert(tup.first);
        while (PF[i] - PF[curr] > L)
            curr++;
        while (stk.front().second.second.first < curr)
        {
            ms.erase(ms.find(stk.front().first));
            stk.front().second.second.first = curr;
            if (stk.front().second.second.first > stk.front().second.second.second)
                stk.pop_front();
            else
            {
                stk.front().first = DP[curr] + stk.front().second.first;
                ms.insert(stk.front().first);
            }
        }
        DP[i] = *ms.begin();
    }
    printf("%lld\n", DP[n]);
    return 0;
}