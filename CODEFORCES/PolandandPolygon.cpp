#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 2e6 + 10  
#define lint long long
int arr[MAXN]; 
int n, k;
struct fenwick
{
    int N;
    vector<lint> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    lint sum(int i)
    {
        lint c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    lint query(int l, int r)
    {
        return sum(r) - sum(l - 1); 
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};
signed main(void)
{ 
    cin >> n >> k; 
    fenwick fenw;
    k = min(k, n - k); 
    fenw.init(MAXN);
    int u = 1; 
    lint res = 1; 
    for(int i = 1; i <= n; i++)
    {
        int v = u + k;  
        res += 1 + fenw.query(u + 1, v - 1);
        if(v > n) v = v - n; 
        fenw.upd(u, 1);
        fenw.upd(v, 1);
        fenw.upd(u + n, 1);
        fenw.upd(v + n, 1);
        u = v;
        cout << res << ' ';    
    }
    return 0; 
}