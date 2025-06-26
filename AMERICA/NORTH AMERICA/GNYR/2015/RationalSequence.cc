#include "bits/stdc++.h"

using namespace std;

int main(void) {
    int tc; 
    cin >> tc; 
    for(int iter = 0; iter < tc; iter++) { 
        int Prob;
        int64_t den, num;
        scanf("%d %lld/%lld", &Prob, &num, &den); 
        int height;
        int64_t ret = 0, mask = 1; 
        for(height = 0; den != num; height++) {
            if(den > num) { 
                den = den - num; 
            }
            else { 
                num = num - den;
                ret |= mask; 
            }
            mask = mask * 2; 
        }
        ret |= mask; 
        printf("%d %lld\n", Prob, ret); 
    }
    return 0;
}