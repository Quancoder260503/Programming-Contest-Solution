#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n;
    cin >> n; 
    vector<int64_t>arr(n); 
    for(int i = 0; i < n; i++) cin >> arr[i]; 
    double ret = 0.0; 
    double sum = 0; 
    for(int i = 0; i < n; i++) 
    {
        sum += arr[i]; 
        ret = max(ret, sum / (i + 1));
    }
    sum = 0; 
    for(int i = n - 1; i >= 0; i--) 
    {
        sum += arr[i]; 
        ret = max(ret, 1.0 * sum / (n - i)); 
    }
    cout << fixed << setprecision(10) << ret << '\n';  
    return 0; 
}