#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int n, m, k; 
    cin >> n >> m >> k; 
    vector<int>a(n); 
    int64_t num = 0, den = 0; 
    for(int i = 0; i < n; i++) cin >> a[i];
    sort(a.rbegin(), a.rend());
    num = accumulate(a.begin(), a.begin() + min(n, m + k), 0LL);
    den = accumulate(a.begin(), a.end(), 0LL); 
    cout << fixed << setprecision(10) << 100.0 * num / den << '\n'; 
    return 0;
}