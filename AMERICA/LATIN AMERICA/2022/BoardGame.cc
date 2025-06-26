#include "bits/stdc++.h"

using namespace std;

#define pii pair<int, int> 

const long long INF = 1e18 + 11;
struct Line
{
    long long a, b;
    long long f(long long x)
    {
        return a * x + b;
    }
};
bool operator<(const Line &f, const Line &g)
{
    if (f.a != g.a)
        return f.a < g.a;
    return f.b > g.b;
}

struct Hull
{
    vector<double> x;
    vector<Line> segs;

    void insert(Line l)
    {
        if (segs.empty())
        {
            x.push_back(-INF);
            segs.push_back(l);
            return;
        }
        double xNew = -INF;
        while (!segs.empty())
        {
            if (segs.back().a == l.a)
            {
                assert(segs.back().b >= l.b);
                return;
            }
            xNew = intersection(segs.back(), l);
            if (xNew < x.back())
            {
                remove();
            }
            else
                break;
        }

        segs.push_back(l);
        x.push_back(xNew);
    }

    long long get(long long x0)
    {
        if (segs.empty())
        {
            return -INF;
        }
        auto i = upper_bound(x.begin(), x.end(), x0) - x.begin() - 1;
        return segs[i].f(x0);
    }

private:
    void remove()
    {
        segs.pop_back();
        x.pop_back();
    }
    double intersection(const Line &f, const Line &g)
    {
        return 1.0 * (f.b - g.b) / (g.a - f.a);
    }
};

const int maxf = 1e5 + 10; 

Hull tree[maxf << 2]; 

vector<int>res[maxf]; 
int n, m; 

void update(int pos, pair<int, int>val, int l = 1, int r = m, int p = 1) { 
    tree[p].insert(Line{val.first, val.second}); 
    if(l == r) return;
    int mid = (l + r) / 2;  
    if(pos <= mid) update(pos, val, l, mid, 2 * p);
    else  update(pos, val, mid + 1, r, 2 * p + 1); 
    return; 
}

int query(pair<int, int>val, int l = 1, int r = m, int p = 1) { 
    if(tree[p].get(val.first) <= val.second) return -1; 
    if(l == r) return l; 
    int mid = (l + r) / 2; 
    int ret = query(val, l, mid, 2 * p);
    if (ret < 0) ret = query(val, mid + 1, r, 2 * p + 1);
    return ret; 
}

int main(void) {    
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n; 
    vector<pair<pii, int>>pts(n);
    for(int i = 0; i < n; i++) { 
        cin >> pts[i].first.first >> pts[i].first.second;
        pts[i].second = i; 
    }
    sort(pts.begin(), pts.end());
    cin >> m;  
    vector<pair<pii, int>>qs(m);
    for(int i = 0; i < m; i++) { 
        cin >> qs[i].first.first >> qs[i].first.second;
        qs[i].second = i;
    }
    sort(qs.begin(), qs.end(), [&](pair<pii, int> a, pair<pii, int> b) { 
        return a.first.first == b.first.first ? a.first.second > b.first.second : a.first.first < b.first.first; 
    });
    for (int i = 0; i < qs.size(); i++) {
        update(qs[i].second + 1, {qs[i].first.first, qs[i].first.second});   
    }
    for(int i = 0; i < n; i++) {
        int x = pts[i].second + 1; 
        int pos = query({pts[i].first.first, pts[i].first.second});
        if(pos != -1) res[pos].push_back(x); 
    }
    for(int i = 1; i <= m; i++) { 
        sort(res[i].begin(), res[i].end()); 
        res[i].erase(unique(res[i].begin(), res[i].end()), res[i].end()); 
        cout << res[i].size() << " "; 
        for(auto r : res[i]) cout << r << " "; 
        cout << '\n'; 
    }
    return 0; 
}