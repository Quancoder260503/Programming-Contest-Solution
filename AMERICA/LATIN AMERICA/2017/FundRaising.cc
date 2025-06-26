#include "bits/stdc++.h"

using namespace std;

typedef long long int64_t; 
typedef pair<int64_t, int64_t> pii;
typedef vector<pii> vpi;
typedef vector<int64_t> vi;
typedef pair<int64_t, int64_t> pi;
#define f first
#define s second

template <class T, int SZ>
struct OffBIT2D
{
    // Code copied from BenQ template.
    bool mode = 0; // mode = 1 -> initialized
    vpi todo;      // locations of updates to process
    int cnt[SZ], st[SZ];
    vi val;
    vector<T> bit; // store all BITs in single vector
    void init()
    {
        assert(!mode);
        mode = 1;
        int lst[SZ];
        for (int i = 0; i < SZ; i++)
        {
            lst[i] = cnt[i] = 0;
        }
        sort(todo.begin(), todo.end(), [](const pi &a, const pi &b)
             { return a.s < b.s; });
        for (auto &t : todo)
        {
            for (int x = t.f; x < SZ; x += x & -x)
            {
                if (lst[x] != t.s)
                {
                    lst[x] = t.s, cnt[x]++;
                }
            }
        }
        int sum = 0;
        for (int i = 0; i < SZ; i++)
        {
            lst[i] = 0, st[i] = (sum += cnt[i]);
        }
        val.resize(sum);
        bit.resize(sum);
        reverse(todo.begin(), todo.end());
        for (auto &t : todo)
        {
            for (int x = t.f; x < SZ; x += x & -x)
            {
                if (lst[x] != t.s)
                {
                    lst[x] = t.s, val[--st[x]] = t.s;
                }
            }
        }
    }
    int rank(int y, int l, int r)
    {
        return upper_bound(begin(val) + l, begin(val) + r, y) - begin(val) - l;
    }
    void UPD(int x, int y, T t)
    {
        for (y = rank(y, st[x], st[x] + cnt[x]); y <= cnt[x]; y += y & -y)
        {
            bit[st[x] + y - 1] = max(bit[st[x] + y - 1], t);
        }
    }
    void upd(int x, int y, T t)
    {
        if (!mode)
            todo.push_back({x, y});
        else
            for (; x < SZ; x += x & -x)
                UPD(x, y, t);
    }
    T QUERY(int x, int y)
    {
        T res = 0;
        for (y = rank(y, st[x], st[x] + cnt[x]); y; y -= y & -y)
            res = max(res, bit[st[x] + y - 1]);
        return res;
    }
    T query(int x, int y)
    {
        assert(mode);
        T res = 0;
        for (; x; x -= x & -x)
            res = max(res, QUERY(x, y));
        return res;
    }
};

const int maxf = 5e5 + 2;

int main(void) {
    int64_t n; 
    cin >> n; 
    OffBIT2D<int64_t, maxf>fenw; 
    vector<int64_t>x(n), y(n), d(n), coord; 
    vector<array<int64_t, 3>>guess, arr; 
    for(int64_t i = 0; i < n; i++) { 
        cin >> x[i] >> y[i] >> d[i]; 
        coord.push_back(x[i]);
        coord.push_back(y[i]); 
    }
    sort(coord.begin(), coord.end()); 
    coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
    for(int64_t i = 0; i < n; i++) { 
        x[i] = lower_bound(coord.begin(), coord.end(), x[i]) - coord.begin() + 1; 
        y[i] = lower_bound(coord.begin(), coord.end(), y[i]) - coord.begin() + 1; 
        guess.push_back({x[i], y[i], d[i]}); 
    } 
    sort(guess.begin(), guess.end()); 
    for(int64_t i = 0; i < guess.size(); i++) { 
        int64_t acc = guess[i][2];
        int64_t j = i + 1; 
        while(j < guess.size() && guess[j][0] == guess[j - 1][0] && guess[j][1] == guess[j - 1][1]) {
            acc += guess[j][2];
            j++;  
        }
        arr.push_back({guess[i][0], guess[i][1], acc});
        i = j - 1;
    }
    for(auto [dx, dy, _] : arr) fenw.upd(dx, dy, 0); 
    fenw.init(); 
    int64_t ret = 0; 
    for(auto [dx, dy, w] : arr) { 
        int64_t c = w + fenw.query(dx - 1, dy - 1); 
        fenw.upd(dx, dy, c);
        ret = max(ret, c); 
    }
    cout << ret << '\n'; 
    return 0;
}