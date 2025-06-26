#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N, C, S; 
    cin >> N >> C >> S; 
    vector<int>h(N); 
    int robot = 0; 
    h[robot]++; 
    for(int i = 0, dir; i < C; i++) { 
        cin >> dir; 
        robot = (robot + dir + N) % N; 
        h[robot]++; 
    }
    --S; 
    cout << h[S] << '\n'; 
    return 0; 
}