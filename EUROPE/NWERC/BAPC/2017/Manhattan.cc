#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N;
    int rx, ry, sx, sy;
    while (cin >> N)
    {
        cin >> rx >> ry >> sx >> sy;
        vector<pair<int, int>> points, P; 
        if (rx > sx)
        {
            swap(rx, sx);
            swap(ry, sy);
        }
        for (int i = 0; i < N; i++)
        {
            int x, y;
            cin >> x >> y;
            points.push_back({x, y});
        }
        if (ry <= sy)
        {
            sort(points.begin(), points.end());
            for (int i = 0; i < N; i++)
            {
                auto [x, y] = points[i];
                if (rx <= x && x <= sx && ry <= y && y <= sy)
                {
                    P.push_back({x, y});
                }
            }
        }
        else
        {
            auto cmp = [&](pair<int, int> a, pair<int, int> b)
            {
                return a.first != b.first ? a.first > b.first : a.second < b.second;
            };
            sort(points.begin(), points.end(), cmp);
            for (int i = 0; i < N; i++)
            {
                auto [x, y] = points[i]; 
                if (rx <= x && x <= sx && sy <= y && y <= ry)
                {
                    P.push_back({x, y});
                }
            }
        }
        vector<int> lis;
        for (int i = 0; i < P.size(); i++)
        {
            int pos = upper_bound(lis.begin(), lis.end(), P[i].second) - lis.begin();
            if (pos == lis.size())
            {
                lis.push_back(P[i].second);
            }
            else
            {
                lis[pos] = P[i].second;
            }
        }
        cout << lis.size() << '\n';
    }
    return 0;
}