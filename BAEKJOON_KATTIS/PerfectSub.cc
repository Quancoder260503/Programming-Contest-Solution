#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e7 + 10; 

int ctr[maxf]; 

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int t; 
    cin >> t;
    for(int tc = 0; tc < t; tc++) { 
        int n; 
        cin >> n; 
        vector<int>a(n);
        vector<int>sum(n + 1, 0); 
        sum[0] = 1e7 + 5; 
        int cc = 0;
        ctr[sum[0]] = 1; 
        for(int i = 0; i < n; i++) 
        {
            cin >> a[i];
            cc = max(cc, a[i]); 
            sum[i + 1] = sum[i] + a[i];
            ctr[sum[i + 1]]++; 
        }
        int64_t ret = 0;
        cc = cc * n + sum[0];   
        for(int i = 0; i <= n; i++) {
            ctr[sum[i]]--;
            for (int j = 0; j * j + sum[i] <= cc; j++) {
                ret += ctr[sum[i] + j * j];
            }
        }
        cout << "Case #" << tc + 1 << ": " << ret << '\n'; 
    }
    return 0; 
}