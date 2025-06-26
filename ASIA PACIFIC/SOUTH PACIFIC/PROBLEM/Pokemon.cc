#include "bits/stdc++.h"

using namespace std; 

const int maxf = 10010; 

int N, B; 
double dyn[42][maxf]; 
double Prob[42];
int cost[42]; 

double memo(int pos, int budget) {
  if(pos == 0) return (budget == 0) * 1.0; 
  double &ret = dyn[pos][budget];   
  if(ret >= 0) return ret;
  ret = 0; 
  double acc = 1; 
  for(int k = 0; k * cost[pos] <= budget; k++) { 
    ret = max(ret, memo(pos - 1, budget - k * cost[pos]) * (1.0 - acc)); 
    acc = acc * (1.0 - Prob[pos]); 
  }
  return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  while(cin >> B >> N && N) { 
    for(int i = 1; i <= N; i++) { 
      cin >> cost[i] >> Prob[i]; 
    }
    for(int i = 0; i < maxf; i++) { 
      for(int j = 0; j < 32; j++) { 
        dyn[j][i] = -1.0; 
      }
    }
    double ret = 0; 
    int pos; 
    for(int w = 0; w <= B; w++) { 
      if(ret < memo(N, w)) { 
        ret = memo(N, w); 
        pos = w; 
      }
    }
    cout << pos << " " << fixed << setprecision(4) << ret << '\n'; 
  } 
  return 0; 
}

