#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int)1e6 + 5
#define BASE 63
#define mp make_pair
const int mod = 1e9 + 7;
#define pii pair<int,lint>
int n, q;
lint ans[MAXN];
lint cnt[MAXN];
lint arr[MAXN];
vector<pii> query[MAXN];
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
    int add(lint val)
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
                    return 1;
                }
            }
        }
        return 0;
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
} linb;
lint binpow(lint a, lint pow)
{
     lint ans = 1; 
     while(pow)
     {
         if(pow & 1) ans = ans % mod * a % mod; 
         a = 1LL * a % mod * a % mod; 
         pow = pow / 2; 
     }
     return ans;
}
signed main(void)
{
     scanf("%d %d", &n, &q);
     for(int i = 1; i <= n; i++)
     {
         scanf("%lld", &arr[i]);
     }
     for(int i = 0; i < q; i++)
     {
        int pos; lint val;
        scanf("%d %lld", &pos, &val); 
        query[pos].push_back(mp(i, val)); 
     }
     for(int i = 1; i <= n; i++)
     {
        cnt[i] += cnt[i - 1] + linb.add(arr[i]);
        for (int j = 0; j < (int) query[i].size(); j++)
        {
            lint curr = query[i][j].first;
            lint tot = query[i][j].second;
            for(int mask = BASE; mask >= 0; mask--)
            {
                 if(tot & (1LL << mask))
                 {
                    tot = tot xor linb.A[mask];
                 }
            }
            if(!tot)
            {
                 ans[curr] = binpow(2, i - cnt[i]); 
            }
         }
     }
     for(int i = 0; i < q; i++)
     {
         printf("%lld\n", ans[i]); 
     }
     return 0;
}