#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
#define K 17
int st[K][MAXN];
int n, q;
int A[MAXN];
map<int, long long> ans;
bool special;
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
void upd()
{
    for (int i = 1; i < K; i++)
    {
        for (int j = 1; j + (1 << i) <= n + 1; j++)
        {
            st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }
    }
}
int query(int l, int r)
{
    if (l == r)
        return st[0][l];
    int k = log2(r - l + 1);
    return gcd(st[k][l], st[k][r - (1 << k) + 1]);
}
signed main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &st[0][i]);
        A[i] = st[0][i];
    }
    upd();
    for (int i = 1; i <= n; i++)
    {
        int currval = A[i];
        int currpos = i;
        while (true)
        {
            int l = 1;
            int r = currpos;
            int lb = currpos;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (query(mid, i) == currval)
                {
                    r = mid - 1;
                    lb = mid;
                }
                else
                {
                    l = mid + 1;
                }
            }
            ans[currval] += 1LL * (currpos - lb + 1);
            currpos = lb - 1;
            if (currpos > 0)
            {
                currval = gcd(currval, A[currpos]);
            }
            else
            {
                break;
            }
        }
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int x;
        scanf("%d", &x);
        if (!ans.count(x))
            printf("0\n");
        else
            printf("%lld\n", ans[x]);
    }
    return 0;
}