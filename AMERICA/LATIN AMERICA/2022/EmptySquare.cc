#include "bits/stdc++.h" 

using namespace std;

const int maxf = 2000; 

int dyn[maxf][maxf]; 

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, k, e; 
    cin >> n >> k >> e; 
    int s = n - k - e; 
    dyn[0][0] = 1; 
    for(int i = 1; i <= n; i++) if(i != k) { 
        for(int x = e; x >= 0; x--) for(int y = s; y >= 0; y--) { 
            if(x >= i) dyn[x][y] |= dyn[x - i][y]; 
            if(y >= i) dyn[x][y] |= dyn[x][y - i];
        }
    }
    int ret = 0;
    for(int x = 0; x <= e; x++) for(int y = 0; y <= s; y++) if(dyn[x][y]) { 
        ret = max(ret, x + y + k); 
    }
    cout << n - ret << '\n'; 
    return 0;
}