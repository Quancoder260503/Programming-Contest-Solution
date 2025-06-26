#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e6 + 1; 
int64_t dyn[maxf], greed[maxf]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int N; 
    cin >> N;  
    vector<int>a(N); 
    for(int i = 0; i < N; i++) { 
        cin >> a[i]; 
    }
    int M = 2 * a[N - 1]; 
    fill(dyn, dyn + M + 1, 1e9); 
    dyn[0] = 0; 
    for(int i = 0; i < N; i++) { 
        for(int j = 1; j <= M; j++) if(j >= a[i]) { 
            dyn[j] = min(dyn[j], dyn[j - a[i]] + 1); 
        }
    }
    for(int weight = 1; weight <= M; weight++) {
        int j; 
        for(j = N - 1; j >= 0; j--) { 
            if(weight >= a[j]) { break; }
        }
        greed[weight] = greed[weight - a[j]] + 1; 
        if(greed[weight] != dyn[weight]) { 
            cout << "non-canonical\n"; 
            return 0; 
        }

    }
    cout << "canonical\n"; 
    return 0;
}