#include "bits/stdc++.h"

using namespace std; 

double Comb(int a, int b) { 
    #define COMB_MAXA 5000
    #define COMB_MAXB 5000
    static double combmemo[COMB_MAXA + 1][COMB_MAXB + 1]; 
    if(a < b || b < 0) return 0; 
    if(!a) return 1;
    double &ret = combmemo[a][b]; 
    if(ret > 0) return ret;
    ret = Comb(a - 1, b - 1) + Comb(a - 1, b); 
    return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int tc, N, W, V1, V2;
  cin >> tc; 
  for(int iter = 0; iter < tc; iter++) { 
    cin >> N >> V1 >> V2 >> W;
    int rem_votes = N - V1 - V2; 
    double ret = 0; 
    for(int vote = 0; vote <= rem_votes; vote++) { 
        if(V1 + vote > V2 + rem_votes - vote) { 
            ret += Comb(rem_votes, vote); 
        }
    }
    for(int vote = 1; vote <= rem_votes; vote++) { 
        ret = ret / 2; 
    }
    ret = ret * 100; 
    if(ret > W) {
      cout << "GET A CRATE OF CHAMPAGNE FROM THE BASEMENT!\n"; 
    }
    else if(ret == 0) { 
      cout << "RECOUNT!\n"; 
    }
    else { 
      cout << "PATIENCE, EVERYONE!\n"; 
    }
  }
  return 0; 
}
