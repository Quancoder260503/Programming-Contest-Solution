#include "bits/stdc++.h"

using namespace std;

const int maxf = 10002; 
const int maxn = 102; 

int main(void)
{
    int tc; 
    cin >> tc; 
    for(int _ = 0; _ < tc; _++)
    {
        int n; double p; 
        cin >> p >> n;
        vector<vector<double>>dyn(maxn, vector<double>(maxf, 0.0)); 
        dyn[0][0] = 1;
        vector<pair<int, double>>arr(n + 1); 
        int sum = 0; 
        for(int i = 1; i <= n; i++) 
        { 
            cin >> arr[i].first >> arr[i].second; 
            sum += arr[i].first; 
        }
        for(int i = 1; i <= n; i++) for(int j = 0; j <= sum; j++)
        {
            dyn[i][j] = max(dyn[i][j], dyn[i - 1][j]);
            if(j >= arr[i].first) dyn[i][j] = max(dyn[i][j], (1.0 - arr[i].second) * dyn[i - 1][j - arr[i].first]); 
        }
        for(int i = sum; i >= 0; i--) if(1.0 - dyn[n][i] <= p)
        {
            cout << i << '\n'; 
            break; 
        }
    }
    return 0;
}