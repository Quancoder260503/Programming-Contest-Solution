#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n; 
    cin >> n;
    vector<int>a(n), ord(n), ret(n); 
    for(int i = 0; i < n; i++) cin >> a[i]; 
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j){ return a[i] < a[j]; });
    sort(a.rbegin(), a.rend());  
    for(int i = 0; i < n; i++)
    {
        ret[ord[i]] = a[i]; 
    }
    for(int i = 0; i < n; i++) cout << ret[i] << " "; 
    cout << '\n'; 
    return 0;
}