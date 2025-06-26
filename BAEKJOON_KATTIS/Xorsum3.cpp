#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int)1e6 + 5
#define BASE 63
struct linear_basis
{
    lint A[BASE + 1], B[BASE + 1];
    lint count;
    bool flag;
    void init()
    {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        count = 0;
        flag = false;
    }
    void add(lint val)
    {
        for (int mask = BASE; mask >= 0; mask--)
        {
            if (val & (1LL << mask))
            {
                if (A[mask])
                {
                    val = val xor A[mask];
                }
                else
                {
                    A[mask] = val;
                    return;
                }
            }
        }
        flag = true;
    }
    lint findmax()
    {
        lint ans = 0;
        for (int mask = BASE; mask >= 0; mask--)
        {
            ans = max(ans, ans xor A[mask]);
        }
        return ans;
    }
    lint findmin()
    {
        lint ans = 0;
        for (int mask = 0; mask <= BASE; mask++)
        {
            if (A[mask])
            {
                ans = A[mask];
                break;
            }
        }
        return ans;
    }
};
lint arr[MAXN]; 
signed main(void)
{
    int n;
    scanf("%d", &n);
    linear_basis linb;
    linb.init();
    lint tot = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
        tot = tot xor arr[i]; 
    }
    for(int i = 1; i <= n; i++)
    {
        arr[i] = arr[i] & (~tot); 
        linb.add(arr[i]); 
    }
    printf("%lld\n", 1LL * linb.findmax()  + (tot xor linb.findmax()));
    return 0;
}
