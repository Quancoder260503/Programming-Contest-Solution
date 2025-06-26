#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e6 + 500'000; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int X1, X2, N, M; 
  cin >> X1 >> X2;
  cin >> N; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) {
    cin >> a[i]; 
  }
  cin >> M; 
  vector<int>b(M); 
  for(int i = 0; i < M; i++) { 
    cin >> b[i]; 
  }
  int ptr1 = 0, ptr2 = 0, dst1 = 0, dst2 = 0; 
  for(int i = 1; i <= maxf; i++) { 
    X1 += dst1; 
    X2 += dst2; 
    if(X1 + 4 == X2 || X2 + 4 == X1) {
      cout << "bumper tap at time " << i << '\n'; 
      return 0; 
    }
    if(ptr1 < N && a[ptr1] == i) { 
      dst1 = 1 - dst1; 
      ptr1++; 
    }
    if(ptr2 < M && b[ptr2] == i) { 
      dst2 = 1 - dst2; 
      ptr2++; 
    }
  }
  cout << "safe and sound\n"; 
  return 0; 
}