#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n; 
    if(n > 2) cout << n - 2 << '\n';
    else
        cout << 1 << '\n'; 
    return 0;
}