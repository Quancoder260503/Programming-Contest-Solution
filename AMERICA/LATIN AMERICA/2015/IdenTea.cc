#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    int N; 
    cin >> N; 
    int ret = 0; 
    for(int i = 0, x; i < 5; i++) { 
        cin >> x; 
        ret += (x == N); 
    }
    cout << ret << '\n'; 
    return 0; 
}