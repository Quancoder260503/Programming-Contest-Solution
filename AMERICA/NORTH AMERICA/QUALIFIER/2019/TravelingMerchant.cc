#include "bits/stdc++.h"

using namespace std;

const int64_t INF = INT32_MIN; 

struct node
{
    int64_t val, sum, lsum, rsum; 
    node(int64_t _val = 0, int64_t _sum = 0, int64_t _lsum = 0, int64_t _rsum = 0) : val(_val), sum(_sum), lsum(_lsum), rsum(_rsum) {}; 
    node operator + (node b) {
        node ret = node(); 
        ret.val = max({val, b.val, rsum + b.lsum}); 
        ret.rsum = max(b.rsum, b.sum + rsum); 
        ret.lsum = max(lsum,   sum + b.lsum); 
        ret.sum = b.sum + sum; 
        return ret; 
    }
}; 

struct Tree
{
    typedef node T;
    T f(T a, T b) { return a + b ; } // (any associative fn)
    vector<T> s;
    int n;
    Tree(int n = 0, T def = node()) : s(2 * n, def), n(n) {}
    void update(int pos, T val)
    {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e)
    { // query [b, e)
        T ra = node(), rb = node();
        for (b += n, e += n; b < e; b /= 2, e /= 2)
        {
            if (b % 2)
                ra = f(ra, s[b++]);
            if (e % 2)
                rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

typedef vector<Tree> vt; 

int main(void)
{ 
    int n, q; 
    cin >> n; 
    vector<int>c(n), d(n); 
    vector<vt>dyn(2, vt(7, Tree(n))); 
    for(int i = 0; i < n; i++) {
        cin >> c[i] >> d[i]; 
    }
    vector<int>cost = {0, 1, 2, 3, 2, 1, 0}; 
    vector<tuple<int, int, int>>qa, qb; 
    cin >> q; 
    for(int i = 0; i < q; i++)
    {
        int s, t;
        cin >> s >> t;
        --s, --t;  
        if(s < t)
        {
            qa.push_back({s, t, i}); 
        }
        else
        {
            qb.push_back({n - 1 - s, n - 1 - t, i});
        }
    } 
    vector<int64_t>ret(q);
    auto solve = [&](int id, vector<tuple<int, int, int>> qr)
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                int x = (j + i) % 7;
                int y = (j + i + 1) % 7;
                int64_t cc = -(c[j] + d[j] * cost[x]) + (c[j + 1] + d[j + 1] * cost[y]);
                dyn[id][i].update(j, node(cc, cc, cc, cc));
            }
        }
        for(auto [s, t, idx] : qr)
        {
            int at = (7 - s % 7) % 7; 
            ret[idx] = dyn[id][at].query(s, t).val; 
        }
        return; 
    };
    solve(0, qa); 
    reverse(d.begin(), d.end());
    reverse(c.begin(), c.end());
    solve(1, qb); 
    for(int i = 0; i < q; i++)
    {
        cout << ret[i] << '\n'; 
    }
    return 0;
}