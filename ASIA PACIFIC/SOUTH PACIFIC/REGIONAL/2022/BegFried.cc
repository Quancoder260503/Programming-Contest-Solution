#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int n; 
    cin >> n; 
    vector<int>a(n); 
    for(int i = 0; i < n; i++) cin >> a[i]; 
    int cc = *min_element(a.begin(), a.end()); 
    int cm = *max_element(a.begin(), a.end()); 
    if(cc >= 0)
    {
        cout << accumulate(a.begin(), a.end(), 0LL) - 2 * cc << '\n'; 
    }
    else if(cm <= 0)
    {
        cout << 2 * cm - accumulate(a.begin(), a.end(), 0LL) << '\n'; 
    }
    else 
    {
        int64_t ret = 0; 
        for(int i = 0; i < n; i++) ret += abs(a[i]); 
        cout << ret << '\n'; 
    }
    return 0; 
}