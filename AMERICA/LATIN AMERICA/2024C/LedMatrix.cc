#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int r, c1, c2;
    cin >> r >> c1 >> c2;
    vector<vector<char>> ca(r, vector<char>(c1)), cb(r, vector<char>(c2));
    for (int i = 0; i < r; i++) { 
        for (int j = 0; j < c1; j++) {
            cin >> ca[i][j];
        }
        for (int j = 0; j < c2; j++) {
            cin >> cb[i][j];
        }
    }
    vector<int> vis(r, true);
    for (int j = 0; j < c1; j++) for (int i = 0; i < r; i++) {
        vis[i] &= (ca[i][j] == '*');
    }
    for (int j = 0; j < c2; j++) for (int i = 0; i < r; i++) if(cb[i][j] == '*' && !vis[i]) {
        cout << "N\n";
        return 0; 
    }
    cout << "Y\n";
    return 0;
}