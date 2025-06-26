#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    int n, d; 
    cin >> n >> d; 
    vector<int>arr(n); 
    for(int i = 0; i < n; i++) cin >> arr[i];
    sort(arr.begin(), arr.end()); 
    int ret = 0; 
    for(int ptr = 0; ptr < n; ptr++) { 
        ptr = upper_bound(arr.begin(), arr.end(), arr[ptr] + d) - arr.begin() - 1;
        ret++; 
    } 
    cout << ret << '\n'; 
    return 0; 
}