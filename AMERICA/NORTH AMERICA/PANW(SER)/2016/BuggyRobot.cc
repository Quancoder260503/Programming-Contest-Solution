#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int N = 60; 
const int oo = 1e6; 

int dyn[N][N][N]; 
char g[N][N]; 
int R, C, Rx, Ry, Ex, Ey;
string S;  

const int dy[4] = {0, 0, -1, 1}; 
const int dx[4] = {-1, 1, 0, 0}; 
string cdir = "UDLR"; 

void bfs(void) { 
    deque<tuple<int, int, int>>q; 
    dyn[Rx][Ry][0] = 0; 
    q.push_back({Rx, Ry, 0}); 
    while(q.size()) { 
        auto [sx, sy, command] = q.front(); 
        q.pop_front(); 
        for(int dir = 0; dir < 4; dir++) { 
            int kx = sx + dx[dir], ky = sy + dy[dir]; 
            if(0 <= kx && kx < R && 0 <= ky && ky < C && g[kx][ky] != '#') { 
                if(dyn[kx][ky][command] > dyn[sx][sy][command] + 1) { 
                    dyn[kx][ky][command] = dyn[sx][sy][command] + 1;
                    q.push_back({kx, ky, command}); 
                }
            }
        }
        if(command < sz(S)) { 
            if(dyn[sx][sy][command + 1] > dyn[sx][sy][command] + 1) { 
                dyn[sx][sy][command + 1] = dyn[sx][sy][command] + 1; 
                q.push_back({sx, sy, command + 1}); 
            }
            for(int dir = 0; dir < 4; dir++) { 
                if(cdir[dir] != S[command]) continue; 
                int kx = sx + dx[dir], ky = sy + dy[dir]; 
                if(0 <= kx && kx < R && 0 <= ky && ky < C && g[kx][ky] != '#') { 
                    if(dyn[kx][ky][command + 1] > dyn[sx][sy][command]) { 
                      dyn[kx][ky][command + 1] = dyn[sx][sy][command];
                      q.push_front({kx, ky, command + 1}); 
                    }
                } 
                else if(dyn[sx][sy][command + 1] > dyn[sx][sy][command]) {
                   // if(sx == 0 && sy == 0) cout << sx << " " << sy << " " << command << " " << dyn[sx][sy][command] << '\n'; 
                    dyn[sx][sy][command + 1] = dyn[sx][sy][command];
                    q.push_front({sx, sy, command + 1}); 
                }
            }
        }
    }
    return; 
}

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    memset(dyn, 63, sizeof(dyn)); 
    cin >> R >> C; 
    for(int i = 0; i < R; i++) { 
        for(int j = 0; j < C; j++) { 
            cin >> g[i][j]; 
            if(g[i][j] == 'E') { 
                Ex = i, Ey = j; 
            }
            if(g[i][j] == 'R') { 
                Rx = i, Ry = j; 
            }
        }
    }
    cin >> S; 
    bfs(); 
    int ret = oo; 
    for(int i = 0; i <= sz(S); i++) { 
        ret = min(ret, dyn[Ex][Ey][i]); 
    }
    cout << ret << '\n'; 
    return 0; 
}