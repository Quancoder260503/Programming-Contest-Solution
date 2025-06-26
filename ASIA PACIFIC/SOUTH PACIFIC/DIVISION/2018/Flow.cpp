#include "bits/stdc++.h"
using namespace std;
const int MAXN = 3e5 + 10;
int n, m;
int arr[MAXN];
signed main(void)
{
  cin >> n >> m;
  int acc = 0;
  for (int i = 1; i <= n; i++)
  {
    int x;
    cin >> x;
    acc += x;
  }
  acc = ceil(1.0 * acc / (1.0 * m));
  cout << acc << endl;
  return 0;
}
/*
  Binary search
*/