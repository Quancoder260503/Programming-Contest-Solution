#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e4 + 10; 

int marked[maxf], dist[maxf]; 
int grid[maxf][maxf]; 
pair<int, int>mp[maxf]; 

const int dx[6] = {0, 0, -1, 1, 1, -1}; 
const int dy[6] = {-1, 1, 0, 0, 1, -1}; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int R, N, A, B, X; 
    cin >> R >> N >> A >> B >> X;
    int id = 0; 
    memset(grid, -1, sizeof(grid)); 
    for(int i = 0, pos; i < X; i++) {
        cin >> pos; 
        marked[pos] = true; 
    }
    for(int i = 0; i < R; i++) { 
        for(int j = 0; j < R + i; j++) { 
            grid[i][j] = ++id; 
            mp[id] = {i, j}; 
        }
    }
    for(int i = 1; i < R; i++) { 
        for(int j = i; j < 2 * R - 1; j++) { 
            grid[R + i - 1][j] = ++id;
            mp[id] = {R + i - 1, j}; 
        }
    }
    memset(dist, -1, sizeof(dist));  
    queue<pair<int, int>>q; 
    dist[A] = 0; 
    q.push(mp[A]); 
    while(q.size()) { 
        auto [x, y] = q.front(); 
        q.pop(); 
        int u = grid[x][y]; 
        for(int dir = 0; dir < 6; dir++) { 
            int px = dx[dir] + x; 
            int py = dy[dir] + y; 
            if(px < 0 || py < 0 || px >= 2 * R - 1 || py >= 2 * R - 1 || grid[px][py] == -1) continue; 
            int v = grid[px][py]; 
            if(marked[v]) continue; 
            if(dist[v] == -1) { 
            //    cout << px << " " << py << " " << x << " " << y << '\n'; 
                dist[v] = dist[u] + 1;
                q.push(mp[v]);  
            }
        }
    } 
    if(dist[B] == -1 || dist[B] > N) { 
        cout << "No\n"; 
    }
    else { 
        cout << dist[B] << '\n'; 
    }
    return 0;
}