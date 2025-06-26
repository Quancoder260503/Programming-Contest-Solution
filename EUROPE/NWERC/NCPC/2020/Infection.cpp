#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int N = 1e7; 

double likely[(N >> 1) + 1]; 
double _log[N + 1]; 
int ret = 100; 

double LP(int a, int r, int pos) { 
  if(pos) { 
    double cc = LP(a, r, 0); 
    if(cc < -20) { return 0; }
    return log(1 - exp(cc)); 
  }
  return _log[N - r] - _log[N - r - a] - _log[N] + _log[N - a]; 
}

void tryit(int k) { 
   cout << "test " << k << '\n'; 
   fflush(stdout); 
   int res; 
   cin >> res; 
   double c_log = -1e15; 
   for(int temp = 100; temp <= N / 2; temp = max(temp + 1, int(temp * 1.1))) { 
     likely[temp] += LP(k, temp, res); 
     if(likely[temp] > c_log) { 
        c_log = likely[temp]; 
        ret = temp; 
     }
   }
   return; 
}

int main(void) { 
  for(int i = 1; i <= N; i++) { 
     _log[i] = _log[i - 1] + log(1.0 * i); 
  }
  for(int cc = 0; cc < 50; cc++) { 
     tryit(N / ret);
  }
  cout << "estimate " << ret << '\n'; 
  return 0; 
}