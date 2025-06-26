#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int64_t x, pw2 = 1; 
    while(true) {
        cout << "? " << pw2 << '\n';
        cin >> x;
        if(x != pw2) {
            cout << "! " << -x + pw2 << '\n';
            return 0; 
        }
        pw2 = pw2 * 2; 
    }
    return 0; 
}