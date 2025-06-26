#include "bits/stdc++.h"

using namespace std; 

string C = "wrgb"; 
int n, m; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n >> m; 
    vector<vector<int>>a(m, vector<int>(n)); 
    for(int i = 0; i < n; i++) { 
        string s; 
        cin >> s; 
        for(int j = 0; j < m; j++) { 
            a[j][i] = (1LL << (int) C.find(s[j])); 
        }
    }
    int g = gcd(n, m);
    for(int xa = 0; xa < m; xa++) for(int xb = 0; xb < m; xb++) { 
        vector<vector<int>>c(g, vector<int>((1 << (int)C.size()))); 
        for(int y = 0; y < n; y++) { 
            int xc = a[xa][y] | a[xb][y]; 
            c[y % g][xc] = true; 
            if(c[((y + xb - xa) % g + g) % g][(1 << (int)C.size()) - xc - 1]) { 
                cout << "possible\n"; 
                return 0;
            }
        }
    }
    cout << "impossible\n"; 
    return 0; 
}