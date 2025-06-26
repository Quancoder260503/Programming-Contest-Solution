#include "bits/stdc++.h"

using namespace std;

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    int N, K, R; 
    cin >> N >> K >> R; 
    vector<int>vis(N + 1); 
    int sum = 0; 
    for(int i = 0, x; i < K; i++) { 
        cin >> x; 
        vis[x] = true; 
    }
    for(int i = 1; i <= R - 1; i++) { 
        sum += vis[i]; 
    }
    int ret = 0; 
    for(int i = 1; i + R - 1 <= N; i++) { 
        sum += vis[i + R - 1]; 
        if(sum < 2) { 
            for(int j = i + R - 1; j > 0 && sum < 2; j--) if(!vis[j]) {
                vis[j] = true;
                ret++;
                sum++;  
            }
        }
        sum = sum - vis[i]; 
    }
    cout << ret << '\n'; 
    return 0; 
}