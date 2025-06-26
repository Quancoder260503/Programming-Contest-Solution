#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int r, c; 
    cin >> r >> c; 
    vector<vector<char>>G(r, vector<char>(c)), T(r, vector<char>(c));
    for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++) {
        cin >> G[i][j]; 
    } 
    for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++) { 
        cin >> T[i][j]; 
    }
    if(G == T) { cout << 1 << '\n'; return 0; }
    vector<int>row(r), col(c); 
    for(int i = 0; i < r; i++) {
        int ctr = 0;  
        for(int j = 0; j < c; j++) { 
            ctr += (T[i][j] == 'X'); 
        }
        row[i] = (ctr <= 1); 
    }
    for(int i = 0; i < c; i++) { 
        int ctr = 0; 
        for(int j = 0; j < r; j++) { 
            ctr += (T[j][i] == 'X'); 
        }
        col[i] = (ctr <= 1); 
    }
    for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++) if(G[i][j] == 'X' && T[i][j] == 'X') {
        if(!row[i]) col[j] = false; 
        if(!col[j]) row[i] = false; 
    }
    for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++) if(G[i][j] == 'O' && T[i][j] == 'X') {
        if(!row[i] || !col[j]) { 
            cout << "0\n"; 
            return 0; 
        } 
    }
    for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++) if(G[i][j] == 'X' && T[i][j] == 'O') { 
        if(!row[i] && !col[j]) { 
            cout << "0\n"; 
            return 0; 
        }
    }
    int ctra = 0, ctrb = 0; 
    for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++) if(row[i] && col[j]) {
        ctra += (G[i][j] == 'O'); 
        ctrb += (T[i][j] == 'X'); 
    }
    cout << (ctra > 0 && ctrb > 0) << '\n'; 
    return 0; 
}