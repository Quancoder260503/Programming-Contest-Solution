#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define MAXN 1500000
#define x first
#define y second
typedef pair<long long, long long> Vec;
typedef long double ldb;
const int mod = 1e9 + 7;
int n, k;
using Point = Vec; 
bool vis[MAXN]; 
struct fenwick
{
     int bit[MAXN];
     int sum(int i)
     {
          int c = 0;
          for (++i; i > 0; i -= (i & -i))
          {
               c = c + bit[i];
          }
          return c;
     }
     int query(int l, int r)
     {
          return sum(r) - sum(l - 1);
     }
     void upd(int i, int dif)
     {
          for (++i; i < MAXN; i += (i & -i))
          {
               bit[i] = dif + bit[i];
          }
          return;
     }
     void resize()
     {
          memset(bit, 0, sizeof(bit));
          return;
     }
} fenw;
struct event
{
     int px, py;
     char type;
     event(int _px, int _py, char _type): px(_px), py(_py), type(_type){};
};
vector<event>cord[MAXN];  
void rotate45(int *x, int *y)
{
     int dx = 2 * (*x) + (*y); 
     int dy = -2 * (*x) + (*y);
     *x = dx; 
     *y = dy;
    return;
}
bool cmp(const event &a, const event &b)
{
     return a.px == b.px ? a.py > b.py : a.px > b.px;  
}
signed main(void)
{
      scanf("%d", &n);
      vector<event>events;  
      vector<int>corr;
      for(int i = 0; i < n; i++)
      {
           char c; int dx; int dy; 
           scanf("%d%d %c", &dx, &dy, &c); 
           rotate45(&dx, &dy);  
           events.push_back(event(dx, dy, c)); 
           corr.push_back(dy); 
      }
      sort(events.begin(), events.end(), cmp);
      sort(corr.begin(), corr.end()); 
      corr.erase(unique(corr.begin(), corr.end()),corr.end()); 
      int N = corr.size();
      for(int i = 0; i < n; i++)
      { 
           int pos = lower_bound(corr.begin(), corr.end(), events[i].py) - corr.begin();
           if(events[i].type == 'N')
           {
               if(fenw.query(pos, N) > 0)
               {
                    puts("impossible");
                    return 0; 
               }    
           } 
           else if(events[i].type == 'P')
           {
                 fenw.upd(pos, 1); 
           }
      }
      fenw.resize(); 
      for(int i = n - 1; i >= 0; i--)
      {
           int pos = lower_bound(corr.begin(), corr.end(), events[i].py) - corr.begin();
           if(events[i].type == 'N')
           {
                fenw.upd(pos, 1); 
           }
           else if(events[i].type == '-')
           {
                vis[i] = (fenw.sum(pos) > 0);
           }
      }
      int ans = 0; 
      int currmax = INT_MIN; 
      int currpmax = INT_MIN;
      for(int i = 0; i < n; i++)
      {
           if(vis[i]) continue;
           if(events[i].type == 'P')
           {
               if(events[i].py > currmax)
               {
                    ans += 1; 
                    currmax = max(events[i].py , currpmax); 
               }
           }
           else if(events[i].type == '-')
           {  
                currpmax = max(events[i].py, currpmax); 
           }
      }
      printf("%d\n", ans); 
      return 0; 
}
