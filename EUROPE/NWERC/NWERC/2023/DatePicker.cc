#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(0);   
    cin.tie(0);
    vector<vector<char>>g(7, vector<char>(24));
    for(int i = 0; i < 7; i++) for(int j = 0; j < 24; j++) {
        cin >> g[i][j];
    }
    int a, b; 
    cin >> a >> b; 
    double ret = 0; 
    for(int mask = 0; mask < (1 << 7); mask++) if(__builtin_popcount(mask) == a) {
        vector<int>col(24);
        for(int j = 0; j < 24; j++) for(int i = 0; i < 7; i++) if(mask & (1 << i)) { 
            col[j] += (g[i][j] == '.'); 
        }
        sort(col.rbegin(), col.rend());
        int sum = 0;  
        for(int i = 0; i < b; i++) { 
            sum += col[i]; 
        } 
        ret = max(ret, 1.0 * sum / (a * b)); 
    } 
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}