#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n, c;
    cin >> n >> c; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) 
    {
        cin >> a[i];
    }
    int64_t len = 0;
    pair<int64_t, int> mn = {INT64_MAX, n + 1}; 
    for(int i = 0; i < n; i++)
    {
        len += a[i];
        len = max(len, (int64_t) i * c); 
        int64_t cc = len / c; 
        if(cc < n) mn = min(mn, {cc - i, i});
    }
    if(mn.first < n)
    {
        cout << mn.second << '\n'; 
    }
    else cout << "impossible\n"; 
    return 0;
}