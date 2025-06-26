#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int n, l, w;
    cin >> l >> w >> n;
    if((l * w) % n == 0) {
        vector<vector<char>> g(l, vector<char>(w)); 
        for (int i = 1; i <= n  ; i++) for (int j = 1; j <= n; j++) {
            if(i * j == n && l % i == 0 && w % j == 0) {
                int kx = l / i, ky = w / j;
                int c = 0; 
                for (int ii = 0; ii < i; ii++) for (int jj = 0; jj < j; jj++) { 
                    for (int x = 0; x < kx; x++) for (int y = 0; y < ky; y++) {
                        g[kx * ii + x][ky * jj + y] = c + 'A';
                    }
                    c++; 
                }
                for (int i = 0; i < l; i++) {
                    for (int j = 0; j < w; j++) {
                        cout << g[i][j]; 
                    }
                    cout << '\n'; 
                }
                return 0;
            }
        }
    }
    else {
        cout << "impossible\n"; 
    }
    return 0;
}