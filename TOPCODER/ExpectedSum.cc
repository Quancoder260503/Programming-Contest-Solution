#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 2502; 

double dyn[maxf][maxf], ndyn[maxf][maxf]; 

class ExpectedSum {
public:
    double solve(vector <int> sequence, vector <int> probMinus) { 
        int n = sz(sequence); 
        dyn[0][0] = 1.0;
        int total = 0; 
        for(int i = 0; i < n; i++) {
            for(int sum = 0; sum <= total + sequence[i]; sum++)
            for(int sumc = 0; sumc <= total + sequence[i]; sumc++) { 
                ndyn[sum][sumc] = 0; 
            }  
            for(int sum = 0; sum <= total; sum++) { 
                for(int sumc = 0; sumc <= total; sumc++) { 
                    ndyn[max(sum, sumc - sequence[i])][max(0, sumc - sequence[i])] += (double(probMinus[i]) / 100) * dyn[sum][sumc]; 
                    ndyn[max(sum, sumc + sequence[i])][sumc + sequence[i]]         += (1.0 - double(probMinus[i]) / 100) * dyn[sum][sumc];  
                }
            }
            total += sequence[i]; 
            for(int sum = 0; sum <= total; sum++)
            for(int sumc = 0; sumc <= total; sumc++) { 
                dyn[sum][sumc]  = ndyn[sum][sumc]; 
                ndyn[sum][sumc] = 0; 
            }  
        }
        double ret = 0; 
        for(int i = 0; i <= total; i++) { 
            for(int j = 0; j <= total; j++) { 
                ret += dyn[i][j] * double(i);
            }
        }
        return ret; 
   }; 
};