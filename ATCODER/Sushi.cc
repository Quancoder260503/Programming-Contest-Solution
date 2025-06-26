#include "bits/stdc++.h"

using namespace std;

const int maxf = 350; 

double dyn[maxf][maxf][maxf]; 
int N; 

double memo(int num_one, int num_two, int num_three) { 
  if(num_one < 0 || num_two < 0 || num_three < 0) return 0.; 
  if(num_one + num_two + num_three == 0) return 0.; 
  double &ret = dyn[num_one][num_two][num_three]; 
  if(ret >= 0) return ret; 
  ret = (N +  memo(num_one - 1, num_two, num_three)     * num_one + 
              memo(num_one + 1, num_two - 1, num_three) * num_two + 
              memo(num_one, num_two + 1, num_three - 1) * num_three) / (num_one + num_two + num_three); 
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N; 
  for(int i = 0; i < maxf; i++) 
  for(int j = 0; j < maxf; j++) 
  for(int k = 0; k < maxf; k++) { 
    dyn[i][j][k] = -1.0; 
  }
  vector<int>ctr(3); 
  for(int i = 0, x; i < N; i++) { 
    cin >> x; 
    ctr[x - 1]++; 
  }
  cout << fixed << setprecision(10) << memo(ctr[0], ctr[1], ctr[2]) << '\n'; 
  return 0; 
}

/*
   dyn[i][j][k] = {expected value when there are i 1s, 2s, 3s}
*/