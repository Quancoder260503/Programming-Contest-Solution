#include "bits/stdc++.h" 

using namespace std;

#define int64_t long long


const int64_t INF = 1e12; 

struct Line
{
    int64_t a, b;
    Line(int64_t _a, int64_t _b) : a(_a), b(_b){};
    int64_t f(int64_t x)
    {
        return 1LL * a * x + b;
    }
};
bool operator<(const Line &f, const Line &g)
{
    if (f.a != g.a)
        return f.a < g.a;
    return f.b > g.b;
}

struct HULL
{
    vector<double> x;
    vector<Line> segs;

    void add(Line l)
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

    int64_t get(int64_t x0)
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

int n, m; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n >> m;
    vector<HULL>cht(n); 
    vector<array<int, 4>>edge;
    vector<array<int, 3>>events; 
    for(int i = 0, a, b, s, e; i < m; i++) { 
        cin >> a >> b >> s >> e; 
        edge.push_back({--a, --b, s, e});
    }
    for(int i = 0; i < m; i++) { 
        events.push_back({i, edge[i][2], 1});
        events.push_back({i, edge[i][3], -1}); 
    }
    sort(events.begin(), events.end(), [&](array<int, 3>a, array<int, 3>b) { return a[1] < b[1]; });
    vector<int64_t>cost(m, INF); 
    vector<int>vis(n); 
    vis[0] = true; 
    for(int i = 0; i < (int) events.size(); i++) {
        int idx = events[i][0], time = events[i][1], type = events[i][2]; 
        int src = edge[idx][0], dst = edge[idx][1]; 
        if(type == 1) { 
            if(vis[src]) { 
                cost[idx] = min(cost[idx], 1LL * time * time - (cht[src].segs.size() ? cht[src].get(time) : 0)); 
            }
        } 
        else { 
            if(cost[idx] != INF) { 
                cht[dst].add(Line{2 * time, -cost[idx] - 1LL * time * time}); 
                vis[dst] = true; 
            }
        }
    } 
    int64_t ret = INF; 
    for(int i = 0; i < m; i++) if(edge[i][1] == n - 1) { 
        ret = min(ret, cost[i]); 
    }
    cout << ret << '\n'; 
    return 0;
}