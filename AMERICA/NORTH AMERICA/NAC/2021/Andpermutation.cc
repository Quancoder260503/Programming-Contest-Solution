#include "bits/stdc++.h"
using namespace std;
const int64_t INF = 1e18; 
struct Node
{
  Node *c[2];
  int ctr;
};
Node *root = new Node();
void insert(Node *node, int64_t x, int bit, int add)
{
  if (bit < 0)
  {
    return;
  }
  if (x & (1LL << bit))
  {
    if (!node->c[1]) node->c[1] = new Node();
    node->c[1]->ctr += add; 
    insert(node->c[1], x, bit - 1, add);
  }
  else
  {
    if (!node->c[0]) node->c[0] = new Node();
    node->c[0]->ctr += add;  
    insert(node->c[0], x, bit - 1, add); 
    //if(bit == 1) cout << (node->c[0]->ctr) << " " << bit << '\n'; 
  }
}
int64_t query(Node *node, int64_t x, int bit)
{
  if(bit < 0) return 0; 
  if(x & (1LL << bit))
  {
    if(node->c[0] && node -> c[0] -> ctr > 0) return query(node->c[0], x, bit - 1);
    return INF; 
  }
  else
  {
    if(node->c[1] && node->c[1]->ctr > 0)
    {
      int64_t ret = (1LL << bit) + query(node->c[1], x, bit - 1); 
      if(ret < INF) return ret; 
    }
    return query(node->c[0], x, bit - 1); 
  }
}
int main(void)
{
  int N;
  while (cin >> N)
  {
    vector<int64_t> a(N);
    for (int i = 0; i < N; i++) 
    {
      cin >> a[i]; 
      insert(root, a[i], 60, 1);
    }
    vector<int> ord(N);
    iota(ord.begin(), ord.end(), 0);
    auto cmp = [&](int i, int j)
    { return a[i] < a[j]; };
    sort(ord.rbegin(), ord.rend(), cmp);
    vector<int64_t> ret(N);
    for (int i = 0; i < N; i++) 
    {
      ret[ord[i]] = query(root, a[ord[i]], 60);
      //cout << a[ord[i]] << " " << ret[ord[i]] << '\n';
      insert(root, ret[ord[i]], 60, -1); 
    }
    for (int i = 0; i < N; i++) cout << ret[i] << '\n';
  }
  return 0;
}
/*        0
         / \
        /   \
       /     \
      /       \
     0         1
    / \       /   \
   0   1      0     1
 /  \    \    / \   /
 0    1   0   0  1  0

   0, 1, 2, 4, 5, 6
*/
