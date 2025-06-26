#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int N = 400; 
const int dx[4] = {0, 0, -1, 1}; 
const int dy[4] = {-1, 1, 0, 0}; 

int cache[N][N]; 

int 
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0); 
    int n; 
    cin >> n;
    int dist, check; 
    for(dist = 0; dist < n; dist++) { 
        int x, y, r; 
        cin >> x >> y >> r;
        deque<pair<int, int>>q; 
        for(int i = 0; i <= 200; i++) { 
           q.push_back({i, 0}); 
        }
        check = false; 
        while(q.size()) { 
            auto [rx, ry] = q.front();
            q.pop_front(); 
            int64_t d = 1LL * (x - rx) * (x - rx) + 1LL * (y - ry) * (y - ry); 
            if(cache[rx][ry] != dist || d <= 1LL * r * r) continue; 
            check |= (ry == 300); 
            cache[rx][ry] = dist + 1; 
            for(int dir = 0; dir < 4; dir++) {
                int px = dx[dir] + rx, py = dy[dir] + ry; 
                if(0 <= px && px <= 200 && 0 <= py && py <= 300) { 
                    q.push_back({px, py}); 
                }
            }
        }
        if(!check) break; 
    }
    cout << dist << '\n'; 
    return 0; 
}