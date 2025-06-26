#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
#define lint long long
const int block = 350;
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
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
};
int n, q; 
int arr[MAXN];
vector<int>corr;
struct query
{
     int L, R, pos;
     query(int _L, int _R, int _pos): L(_L), R(_R), pos(_pos) {}; 
};
bool cmp(const query a, const query b)
{
     return a.L / block == b.L / block ? a.R < b.R : a.L < b.L;
}
fenwick fenw;
lint res[MAXN]; 
signed main(void)
{
     cin >> n >> q; 
     for(int i = 1; i <= n; i++)
     {
         cin >> arr[i]; 
         corr.push_back(arr[i]); 
     }
     sort(corr.begin(), corr.end()); 
     corr.erase(unique(corr.begin(), corr.end()), corr.end());
     for (int i = 1; i <= n; i++)
     {
         arr[i] = lower_bound(corr.begin(), corr.end(), arr[i]) - corr.begin() + 1; 
     }
     vector<query>qry; 
     for(int i = 0; i < q; i++)
     {
          int l, r; cin >> l >> r; 
          qry.push_back(query(++l, r, i)); 
     }
     sort(qry.begin(), qry.end(), cmp); 
     fenw.init(MAXN); 
     int l = 1, r = 0; 
     lint ans = 0;
     lint tot = 0;
     for(int i = 0; i < qry.size(); i++)
     {
        while(l > qry[i].L)
        {
            ans += fenw.sum(arr[--l] - 1); 
            fenw.upd(arr[l], 1);
            tot++; 
        }
        while(r < qry[i].R)
        { 
             ans += tot - fenw.sum(arr[++r]);
             fenw.upd(arr[r], 1); 
             tot++;
        }
        while(l < qry[i].L)
        {
            ans -= fenw.sum(arr[l] - 1); 
            fenw.upd(arr[l++], -1); 
            tot--;
        }
        while(r > qry[i].R)
        {
            ans -= tot - fenw.sum(arr[r]);
            fenw.upd(arr[r--], -1);
            tot--;   
        }
        res[qry[i].pos] = ans; 
     }
     for(int i = 0; i < q; i++)
     {
        printf("%lld\n", res[i]); 
     }
     return 0;
}