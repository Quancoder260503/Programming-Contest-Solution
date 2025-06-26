#include "bits/stdc++.h"

using namespace std; 

const int N = 5000; 

int dyn[N][N][2]; 

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    int tc, b, d;
    string s; 
    memset(dyn, -1, sizeof(dyn)); 
    for(cin >> tc; tc--; ) {
        cin >> b >> d >> s; 
        function<int(int, int, int)> func = [&](int row, int col, int turn) { 
            if(row == 1 && turn == 0) return 0; 
            if(col == 1 && turn == 1) return 0;
            int &ret = dyn[row][col][turn]; 
            if(ret != -1) return ret; 
            ret = 0; 
            if(!turn) { 
                for(int k = 1; k < row; k++) { ret |= true ^ (func(k, col, turn ^ 1) | func(row - k, col, turn ^ 1)) ; }
            }
            else { 
                for(int k = 1; k < col; k++) { ret |= true ^ (func(row, k, turn ^ 1) | func(row, col - k, turn ^ 1)) ; }
            }
            return ret;  
        };
        cout << s << " " << (func(d, b, (s == "Vicky")) ? "can" : "cannot") << " " << "win\n";  
    }
    return 0; 
}