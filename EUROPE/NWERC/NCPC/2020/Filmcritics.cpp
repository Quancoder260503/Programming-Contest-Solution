#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define pii pair<int,int>
#define inf (int) 1e9
#define mp make_pair
int n, m, k;
int ans[MAXN]; 
signed main(void)
{
    scanf("%d %d %d", &n, &m, &k); 
    if(k % m != 0 || k == 0)
    {
        puts("impossible");
        return 0; 
    }
    int p = k / m;
    vector<pii>arr; 
    for(int i = 1; i <= n; i++)
    {
         int x; scanf("%d", &x); 
         arr.push_back(mp(x, i)); 
    } 
    sort(arr.begin(), arr.end()); 
    set<pii>s;
    int l = n - p - 1;
    int r = n - p;
    int curr = 0;
    for(int i = 1; i <= n; i++)
    {
         if(r <= n && curr <= arr[r].first * (i - 1))
         {
            curr += m; 
            ans[i] = arr[r].second; 
            r += 1;
         }
         else
         {
             if(l == -1 || curr <= arr[l].first * (i - 1))
             {
                puts("impossible");
                return 0; 
             }
             ans[i] = arr[l].second; 
             l -= 1; 
         }
    }
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", ans[i]); 
    }
    return 0; 
}