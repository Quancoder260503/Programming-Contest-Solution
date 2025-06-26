#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N, Q; 
    while(cin >> N >> Q)
    {
        vector<int>xc(N), yc(N);
        for(int i = 0; i < N; i++) cin >> xc[i] >> yc[i]; 
        xc.push_back(1e9 + 20); xc.push_back(-1e9 - 20); 
        yc.push_back(1e9 + 20); yc.push_back(-1e9 - 20);
        sort(xc.begin(), xc.end()); 
        sort(yc.begin(), yc.end()); 
        xc.erase(unique(xc.begin(), xc.end()), xc.end());
        yc.erase(unique(yc.begin(), yc.end()), yc.end()); 
        auto get_fa = [&](int sx, int sy, int x, int y)
        {
            if(sx < 0 || sx >= xc.size() - 1 || sy < 0 || sy >= yc.size() - 1)   return -1; 
            if(x <= xc[sx] || x >= xc[sx + 1] || y <= yc[sy] || y >= yc[sy + 1]) return -1; 
            if(xc[sx + 1] - xc[sx] == 2 && yc[sy + 1] - yc[sy] == 2) return -1; 
            if(xc[sx + 1] - xc[sx] == 2 && xc[sx] - xc[sx - 1] == 1 && xc[sx + 2] - xc[sx + 1] == 1) return -1; 
            if(yc[sy + 1] - yc[sy] == 2 && yc[sy] - yc[sy - 1] == 1 && yc[sy + 2] - yc[sy + 1] == 1) return -1;
            if(xc[sx + 1] - xc[sx] == 4 && yc[sy + 1] - yc[sy] == 4 && x - xc[sx] == 2 && y - yc[sy] == 2) return -1; 
            if(xc[sx + 1] - xc[sx] >= 4 && yc[sy + 1] - yc[sy] >= 4) return 0;
            return (((x - xc[sx] - 1) & 1) xor (((y - yc[sy] - 1) / 2) & 1)) + 2 * (((y - yc[sy] - 1) & 1) xor (((x - xc[sx] - 1) / 2) & 1)); 
        };
        vector<vector<vector<int>>>comp(xc.size() - 1, vector<vector<int>>(yc.size() - 1, {-1, -1, -1, -1})); 
        for(int i = 0; i < Q; i++)
        {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2; 
            int sx1 = lower_bound(xc.begin(), xc.end(), x1) - xc.begin() - 1;
            int sy1 = lower_bound(yc.begin(), yc.end(), y1) - yc.begin() - 1;
            int sx2 = lower_bound(xc.begin(), xc.end(), x2) - xc.begin() - 1;
            int sy2 = lower_bound(yc.begin(), yc.end(), y2) - yc.begin() - 1;
            int p = get_fa(sx1, sy1, x1, y1);
            int q = get_fa(sx2, sy2, x2, y2); 
            if(p == -1 || q == -1)
            {
                puts("0");
                continue; 
            }
            vector<tuple<int, int, int, int>>Query;
            Query.push_back({sx1, sy1, x1, y1});
            for(int j = 0; j < Query.size(); j++)
            {
                auto [sx, sy, x, y] = Query[j]; 
                int fp = get_fa(sx, sy, x, y);  
                if(fp == -1 || comp[sx][sy][fp] != -1) continue; 
                comp[sx][sy][fp] = i; 
                for(int fx = 1; fx <= 4; fx++) for(int fy = fx - 1; fy <= fx + 1; fy += 2)
                {
                    if (fp == get_fa(sx, sy, xc[sx] + 1, yc[sy] + fx))         Query.push_back({sx - 1, sy, xc[sx] - 1, yc[sy] + fy});
                    if (fp == get_fa(sx, sy, xc[sx] + fx, yc[sy] + 1))         Query.push_back({sx, sy - 1, xc[sx] + fy, yc[sy] - 1});
                    if (fp == get_fa(sx, sy, xc[sx + 1] - 1, yc[sy + 1] - fx)) Query.push_back({sx + 1, sy, xc[sx + 1] + 1, yc[sy + 1] - fy});
                    if (fp == get_fa(sx, sy, xc[sx + 1] - fx, yc[sy+ 1] - 1))  Query.push_back({sx, sy + 1, xc[sx + 1] - fy, yc[sy + 1] + 1});
                }
            } 
            cout << (comp[sx1][sy1][p] == comp[sx2][sy2][q]) << '\n'; 
        }
    }
    return 0;
}