#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
#define mp make_pair
#define pii pair<int, int>
int arr[MAXN];
signed main(void)
{
    int n;
    scanf("%d ", &n);
    priority_queue<pii, vector<pii> > pq;
    vector<pii> arr;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        if(x)
        {
            pq.push(mp(x, i));
        }
    }
    vector<pii> ans;
    while (pq.size())
    {
        if (pq.size() == 1)
        {
            puts("no");
            return 0;
        }
        pii f = pq.top();
        pq.pop();
        pii s = pq.top();
        pq.pop();
        ans.push_back(mp(f.second, s.second));
        f.first = f.first - 1;
        s.first = s.first - 1;
        if (f.first > 0)
        {
            pq.push(f);
        }
        if (s.first > 0)
        {
            pq.push(s);
        }
    }
    puts("yes");
    for (int i = 0; i < (int)ans.size(); i++)
    {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}