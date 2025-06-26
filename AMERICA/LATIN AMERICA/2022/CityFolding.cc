#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int64_t n, p, h; 
    cin >> n >> p >> h; 
    --p, --h;
    vector<int64_t>arr;
    for(int i = n - 1; i >= 0; i--) { 
        arr.push_back(h >= (1LL << i)); 
        if(arr.back()) h = (1LL << (i + 1)) - h - 1; 
    }
    for(int i = n - 1; i >= 0; i--) { 
        if(arr[i]) {
            if(p < (1LL << i)) { 
                cout << 'L'; 
                p = (1LL << i) - p - 1;
            }
            else { 
                cout << 'R'; 
                p = (1LL << (i + 1)) - p - 1; 
            }
        }
        else { 
            if(p >= (1LL << i)) { 
                p = p - (1LL << i); 
                cout << 'L'; 
            }
            else { 
                cout << 'R'; 
            }
        }
    }
    cout << '\n'; 
    return 0; 
}