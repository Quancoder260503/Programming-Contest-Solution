#include <vector> 
#include <iostream> 

using namespace std; 

struct Fenwick { 
 vector<int>bit;
 int n;  
 Fenwick(int _n) : n(_n), bit(_n) {}; 
 void update(int pos, int v) { 
  for(pos++; pos < n; pos += pos & -pos) { 
   bit[pos] += v; 
  }
 }
 int query(int pos) { 
  int ret = 0; 
  for(pos++; pos > 0; pos -= pos & -pos) { 
   ret += bit[pos]; 
  }
  return ret; 
 }
 int query(int L, int R) { 
  return query(R) - query(L - 1); 
 }
}; 

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0);
 int n; 
 cin >> n; 
 vector<int>pos(n + 1); 
 for(int i = 1, x; i <= n; i++) { 
  cin >> x; 
  pos[x] = i; 
 }
 Fenwick fenw(n + 10);
 vector<int>ret(n + 1);
 for(int i = 1; i <= n; i++) { 
  fenw.update(i, 1);   
 }
 ret[n] = n - pos[n] + 1;  
 fenw.update(pos[n], -1); 
 for(int i = n - 1; i > 0; i--) { 
  if(pos[i] < pos[i + 1]) { 
   ret[i] = fenw.query(pos[i], pos[i + 1]);   
  } else { 
   ret[i] = fenw.query(1, pos[i + 1]) + fenw.query(pos[i], n); 
  }
  fenw.update(pos[i], -1); 
 }
 for(int i = 1; i <= n; i++) cout << ret[i] << " "; 
 cout << '\n'; 
 return 0; 
}