#include "bits/stdc++.h"

using namespace std; 

struct pts { 
    int x, y, z; 
}; 

struct rot { 
    char op; 
    int ang, r; 
}; 

int main(void) {
    int n, m; 
    cin >> n >> m;
    vector<rot>cc;
    rot curr;
    for(int i = 0; i < m; i++) { 
        cin >> curr.op >> curr.ang >> curr.r; 
        if(curr.op == 'q') { 
            pts pos = {curr.ang, curr.r, 0};
            cin >> pos.z; 
            for(int j = cc.size() - 1; j >= 0; j--) { 
                auto c = cc[j];
                for(int deg = c.ang; deg > 0; deg -= 90) {
                    if(c.op == 'x' && c.r < pos.x) { 
                        pos = {pos.x, n + 1 - pos.z, pos.y}; 
                    }
                    if(c.op == 'y' && c.r < pos.y) {
                        pos = {pos.z, pos.y, n + 1 - pos.x};  
                    }
                    if(c.op == 'z' && c.r < pos.z) {
                        pos = {n + 1 - pos.y, pos.x, pos.z}; 
                    }
                }
            }
            cout << pos.x + n * (pos.y - 1 + n * (pos.z - 1))  << '\n'; 
        }
        else { 
            cc.push_back(curr); 
        }
    } 
    return 0; 
}