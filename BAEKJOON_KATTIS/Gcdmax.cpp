#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
#define K 20
#define mp make_pair
int st[K][MAXN];
int n, q;
int A[MAXN];
int lf[MAXN]; 
int rg[MAXN]; 
bool special;
const int mod = (int) 1e9 + 7;
vector<pair<int,long long> >divis[MAXN], divis1[MAXN]; 
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
    stack<int>stk; 
    for(int i = 1; i <= n; i++)
    {
        while(stk.size() && A[i] >= A[stk.top()])
        {
            stk.pop(); 
        } 
        lf[i] = stk.size() ?  stk.top() + 1 : 1; 
        stk.push(i); 
    }
    while(stk.size()) stk.pop();
    for(int i = n; i > 0; i--)
    {
        while(stk.size() && A[i] > A[stk.top()])
        {
            stk.pop(); 
        }
        rg[i] = stk.size() ? stk.top() - 1 : n; 
        stk.push(i); 
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int currval = A[i];
        int currpos = i;
        while (true)
        {
            int l = lf[i];
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
            divis[i].push_back(mp(currval,currpos - lb + 1)); 
            currpos = lb - 1;
            if (currpos > lf[i] - 1)
            {
                currval = gcd(currval, A[currpos]);
            }
            else
            {
                break;
            }
        }
        currval = A[i];
        currpos = i;
        while (true)
        {
            int l = currpos;
            int r = rg[i];
            int rb = currpos;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (query(i, mid) == currval)
                {
                    l = mid + 1;
                    rb = mid;
                }
                else
                {
                    r = mid - 1;
                }
            }
            divis1[i].push_back(mp(currval, rb - currpos + 1));
            currpos = rb + 1;
            if (currpos < rg[i] + 1)
            {
                currval = gcd(currval, A[currpos]);
            }
            else
            {
                break;
            }
        } 
    }
    for(int i = 1; i <= n; i++)
    {
         for(int j = 0; j < divis[i].size(); j++)
         {
             for(int k = 0; k < divis1[i].size(); k++)
             {
                 int u = divis[i][j].first;
                 int wu = divis[i][j].second; 
                 int v = divis1[i][k].first; 
                 int wv = divis1[i][k].second;
                 ans = (ans + 1LL * gcd(u,v) % mod * A[i] % mod * wu % mod * wv % mod + mod) % mod;
             }
         }
    }
    ans = ans % mod; 
    printf("%lld\n",ans);
    return 0;
}