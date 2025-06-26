#include "bits/stdc++.h"
using namespace std;
int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>a(N);
        for(int i = 0; i < N; i++) cin >> a[i]; 
        cout << (is_sorted(a.begin(), a.end()) ? "yes" : "no") << '\n'; 
    }
    return 0;
}