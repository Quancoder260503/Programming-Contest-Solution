#include "bits/stdc++.h"

using namespace std; 

const double INF = 1e14; 

#define x first
#define y second 

// Minimumer diameter spanning tree

int main(void) {
    int n;
    cin >> n;
    vector<pair<int, int>>p(n); 
    for(int i = 0; i < n; i++) cin >> p[i].x >> p[i].y; 
    vector<vector<double>>d(n, vector<double>(n)); 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        d[i][j] = hypot(p[i].x - p[j].x, p[i].y - p[j].y); 
    }
    for(int k = 0; k < n; k++) for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        d[i][j] = min(d[i][j], d[i][j] + d[j][k]); 
    }
    double dim = INF;
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    vector<vector<int>>cc; 
    for(int i = 0; i < n; i++) { 
        sort(ord.begin(), ord.end(), [&](int j, int k){ return d[i][j] < d[i][k]; }); 
        dim = min(dim, 2.0 * d[i][ord.back()]);
        cc.push_back(ord);  
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) {
        if(i == j) continue; 
        for(int pp = n - 1, k = n - 2; k >= 0; k--) { 
            if(d[j][cc[i][k]] > d[j][cc[i][pp]]) { 
                dim = min(dim, d[i][cc[i][k]] + d[j][cc[i][pp]] + hypot(p[i].x - p[j].x, p[i].y - p[j].y));
                pp = k;  
            }
        }
    }
    cout << fixed << setprecision(10) << dim << '\n'; 
    return 0; 
}