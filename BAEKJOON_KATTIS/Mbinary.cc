#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 34;

int64_t n, m, c[maxf][maxf]; 
vector<int>d; 

int64_t f(int x, int y) { 
    if(y < 0) return 0;
    if(x == 0) return (y == 0); 
    int64_t ret = 0; 
    if(d[x]) { 
        ret += (y ? c[x - 1][y - 1] : 0) + f(x - 1, y); 
    }
    else { 
        ret += f(x - 1, y - 1); 
    }
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    c[0][0] = 1; 
    for(int i = 1; i < maxf; i++) for(int j = 0; j <= i; j++) { 
        c[i][j] = c[i - 1][j] + (j ? c[i - 1][j - 1] : 0); 
    }
    while(cin >> n >> m) { 
        if(n == 0) { 
            cout << (m == 1) << '\n'; 
            continue; 
        }
        if(m > 31) { 
            cout << 0 << '\n'; 
            continue; 
        }
        d.clear(); 
        d.push_back(0); 
        while(n) { 
            d.push_back(n & 1);
            n = n / 2; 
        }
        int64_t ret = f(sz(d) - 2, m) + (m == 1);
        for(int i = 2; i < sz(d) - 1; i++) { 
            ret += c[i - 1][m]; 
        } 
        cout << ret << '\n'; 
    }
    return 0;
}