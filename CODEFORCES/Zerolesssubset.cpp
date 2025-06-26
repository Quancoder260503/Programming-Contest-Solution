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
    int rank()
    {
        int ans = 0; 
        for(int i = 0; i < BASE; i++)
        {
             ans += (A[i] > 0); 
        }
        return ans;
    }
};
int arr[MAXN]; 
int n; 
linear_basis linb;
signed main(void)
{
     scanf("%d", &n); 
     linb.init(); 
     for(int i = 1; i <= n; i++)
     {
         scanf("%d", &arr[i]);
     }
     int prefix = 0; 
     for(int i = 1; i <= n; i++)
     {
         prefix = prefix xor arr[i]; 
         linb.add(prefix); 
     }
     printf("%d\n", prefix == 0 ? -1 : linb.rank()); 
     return 0; 
}