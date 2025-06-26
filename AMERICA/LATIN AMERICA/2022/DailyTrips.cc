#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int n, h, w;
    cin >> n >> h >> w; 
    for(int i = 0; i < n; i++) { 
        char ca, cb;
        cin >> ca >> cb;
        if(ca == 'N') { 
            if(w){ 
                cout << 'N'; 
            }
            else { 
                h--; w++; 
                cout << 'Y'; 
            }
        }
        else if(ca == 'Y') { 
            h--; w++; 
            cout << 'Y'; 
        }
        cout << " "; 
        if (cb == 'N') {
            if (h) {
                cout << 'N' << '\n';
            }
            else {
                h++; w--;
                cout << 'Y' << '\n';
            }
        }
        else if (cb == 'Y') {
            h++; w--;
            cout << 'Y' << '\n';
        }
    }
    return 0; 
}