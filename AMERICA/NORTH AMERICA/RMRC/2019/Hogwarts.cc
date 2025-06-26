#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2000;

int g[2][maxf][4]; 
int vis[maxf][maxf]; 
int N, ret; 

void doit(pair<int, int>u)
{
    if(vis[u.first][u.second]) return; 
    vis[u.first][u.second] = 1; 
    if(u.first == N && u.second < N)
    {
        cout << "No" << '\n'; 
        exit(0); 
    }
    ret |= (u.first == N); 
    for(int k = 0; k < 4; k++)
    {
        doit({g[0][u.first][k], g[1][u.second][k]}); 
    }
    return; 
}

int main(void)
{
    cin >> N; 
    for(int i = 0; i < 2; i++) for(int j = 1; j <= N; j++) for(int k = 0; k < 4; k++)
    {
        cin >> g[i][j][k]; 
    }
    ret = 0; 
    doit({1, 1}); 
    cout << (ret ? "Yes" : "Impossible") << '\n'; 
    return 0; 
}