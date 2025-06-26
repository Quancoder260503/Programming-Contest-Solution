#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

const int N = 100; 
int64_t dyn[N][N][N][N]; 


int64_t Comb(int a, int b) { 
    #define COMB_MAXA 5000
    #define COMB_MAXB 5000
    static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1]; 
    if(a < b || b < 0) return 0; 
    if(!a) return 1;
    int64_t &ret = combmemo[a][b]; 
    if(!ret) ret = Comb(a - 1, b - 1) + Comb(a - 1, b); 
    return ret; 
}


class ChristmasTree{
public:
    int64_t memo(int N, int H, int red, int green, int blue) { 
        if(N < H) return 1; 
        int64_t &ret = dyn[H][red][green][blue]; 
        if(ret != -1) return ret;
        ret = 0; 
        if(red   >= H) ret += memo(N, H + 1, red - H, green, blue); 
        if(green >= H) ret += memo(N, H + 1, red, green - H, blue); 
        if(blue  >= H) ret += memo(N, H + 1, red, green, blue - H);  
        if(H % 2 == 0) { 
            if(red  >= H / 2 && green >= H / 2) ret += memo(N, H + 1, red - H / 2, green - H / 2, blue) * Comb(H, H / 2); 
            if(red  >= H / 2 && blue  >= H / 2) ret += memo(N, H + 1, red - H / 2, green, blue - H / 2) * Comb(H, H / 2); 
            if(blue >= H / 2 && green >= H / 2) ret += memo(N, H + 1, red, green - H / 2, blue - H / 2) * Comb(H, H / 2); 
        }
        if(H % 3 == 0) { 
            if(red >= H / 3 && green >= H / 3 && blue >= H / 3) { 
                ret += memo(N, H + 1, red - H / 3, green - H / 3, blue - H / 3) * Comb(H, H / 3) * Comb(2 * H / 3, H / 3); 
            }
        }
        return ret;    
    }
    int64_t decorationWays(int N, int red, int green, int blue) { 
        memset(dyn, -1, sizeof(dyn));
        return memo(N, 1, red, green, blue); 
    }
};


int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    ChristmasTree c; 
    cout << c.decorationWays(8,1,15,20) << '\n'; 
    return 0; 
}