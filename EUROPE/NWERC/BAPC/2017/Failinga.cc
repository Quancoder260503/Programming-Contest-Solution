#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N;
    cin >> N; 
    vector<int>a(N); 
    for(int i = 0; i < N; i++) cin >> a[i]; 
    sort(a.rbegin(), a.rend()); 
    int odd = 0, even = 0; 
    for(int i = 0; i < N; i++)
    {
        if(i & 1) odd += a[i];
        else even += a[i]; 
    }
    cout << even << " " << odd << '\n'; 
    return 0;
}