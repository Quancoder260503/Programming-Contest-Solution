#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int tc, ProbNum, n; 
    cin >> tc; 
    while(tc--) { 
        cin >> ProbNum >> n; 
        cout << ProbNum << " " << 1LL * n * (n + 1) / 2 << " " << n * (n - 1) + n << " " << 1LL * n * (n + 1) << '\n'; 
    }
    return 0; 
}