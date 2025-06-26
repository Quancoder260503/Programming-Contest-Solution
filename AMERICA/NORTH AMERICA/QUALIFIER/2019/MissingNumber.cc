#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n; 
    cin >> n; 
    vector<int>b(n); 
    for(int i = 0; i < n; i++) cin >> b[i]; 
    int N = b[n - 1]; 
    vector<int>a(N);
    iota(a.begin(), a.end(), 1);
    if(a == b) cout << "good job\n"; 
    else 
    {
        for(int i = 0; i < N; i++) if(find(b.begin(), b.end(), a[i]) == b.end())
        {
            cout << a[i] << '\n'; 
        }
    } 
    return 0;
}