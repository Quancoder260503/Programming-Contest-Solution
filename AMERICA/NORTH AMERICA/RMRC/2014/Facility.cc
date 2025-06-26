#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int n, m, k; 
    cin >> n >> m >> k; 
    vector<vector<int>>a(n, vector<int>(m)); 
    for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) { 
        cin >> a[i][j]; 
    }
    int ret = 0; 
    vector<int>visited(m); 
    for(int i = 0; i < m; i++) { 
        if(visited[i]) continue; 
        for(int j = 0; j < n; j++) if(!a[j][i]) { 
            for(int k = 0; k < m; k++) if(!a[j][k]) { 
                visited[k] = true; 
            }
            ret++;
            break; 
        }
        if(!visited[i] || ret > k) { 
            cout << "no\n"; 
            return 0; 
        }
    }
    cout << "yes\n"; 
    return 0; 
}