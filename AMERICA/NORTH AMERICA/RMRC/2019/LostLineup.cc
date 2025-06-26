#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int N; 
    cin >> N; 
    vector<int>arr(N);
    --N;  
    for(int i = 0; i < N; i++) cin >> arr[i]; 
    vector<int>ord(N); 
    iota(ord.begin(), ord.end(), 0); 
    auto cmp = [&](int a, int b)
    {
        return arr[a] < arr[b]; 
    }; 
    sort(ord.begin(), ord.end(), cmp);
    cout << 1 << " "; 
    for(auto v : ord) cout << v + 2 << " "; 
    cout << '\n';  
    return 0; 
}