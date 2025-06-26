#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 1000;
const int offset = 500;
const int oo = 1e9; 

int N, M; 

int dyn[maxf][22][maxf]; 

int main(void) {
  int T = 0; 
  while (~scanf("%d%d", &N, &M) && N && M) { 
    vector<int> P(N), D(N);
    for (int i = 0; i < N; i++) { 
        scanf("%d%d", &D[i], &P[i]); 
    } 
    memset(dyn, -1, sizeof(dyn)); 
    dyn[N][0][offset] = 0;
    for (int pos = N - 1; pos >= 0; pos--) {
      for (int k = 0; k <= M; k++) {
        for (int weight = 0; weight < maxf; weight++) {
          dyn[pos][k][weight] = dyn[pos + 1][k][weight]; 
          if(weight >= D[pos] - P[pos] && k && dyn[pos + 1][k - 1][weight - (D[pos] - P[pos])] != -1) {
            if(dyn[pos][k][weight] < dyn[pos + 1][k - 1][weight - (D[pos] - P[pos])]   + D[pos] + P[pos]) { 
              dyn[pos][k][weight]  = dyn[pos + 1][k - 1][weight  - (D[pos] - P[pos])]  + D[pos] + P[pos]; 
            }
          }
        }
      } 
    }
    pair<int, int>ret = {oo, oo};
    int rem; 
    for(int weight = 0; weight < maxf; weight++) { 
      if(dyn[0][M][weight] == -1) continue; 
      if(ret.first > abs(weight - offset)) { 
        ret = {abs(weight - offset), dyn[0][M][weight]}; 
        rem = weight; 
      }
      else if(ret.first == abs(weight - offset) && ret.second < dyn[0][M][weight]) { 
        ret = {abs(weight - offset), dyn[0][M][weight]}; 
        rem = weight; 
      }
    } 
    T++;
    printf("Jury #%d\nBest jury has value %d for prosecution and value %d for defence:\n", T, (rem - offset + ret.second) / 2, (ret.second - (rem - offset)) / 2); 
    vector<int> res;
    int pos = 0, amt = M; 
    int ctr = 0; 
    while(pos < N) {
      if(rem >= (D[pos] - P[pos]) && dyn[pos][amt][rem] == D[pos] + P[pos] + dyn[pos + 1][amt - 1][rem - (D[pos] - P[pos])]) { 
        res.push_back(pos + 1); 
        rem = rem - (D[pos] - P[pos]); 
        amt = amt - 1;
        pos = pos + 1; 
      }
      else if(dyn[pos][amt][rem] == dyn[pos + 1][amt][rem]) { 
        pos = pos + 1; 
      }
    }
    for(int i = 0; i < sz(res); i++) { 
      printf(" %d", res[i]); 
    }
    printf("\n\n"); 
  }
  return 0;
}

/*
  
  should focus on dyn[maxf][num_chosen][sum_diff]
*/

