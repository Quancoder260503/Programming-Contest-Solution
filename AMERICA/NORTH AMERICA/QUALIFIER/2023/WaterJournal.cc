#include "bits/stdc++.h"

using namespace std;

const int N = 100; 
int occ[N]; 

int main(void) {
    int n, a, b; 
    cin >> n >> a >> b; 
    for(int i = 1, x; i <= n; i++) { 
        cin >> x;
        occ[x]++; 
    }
    if(occ[a] && occ[b]) for(int i = a; i <= b; i++) cout << i << '\n'; 
    else if(!occ[a] && !occ[b]) cout << -1 << '\n'; 
    else if(!occ[b]) cout << b << '\n'; 
    else cout << a <<'\n'; 
    return 0; 
}