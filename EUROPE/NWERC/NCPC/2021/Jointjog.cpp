#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
int vis[MAXN];
const double eps = 3e-14;
long long ax, ay, bx, by, cx, cy, dx, dy;
signed main(void)
{
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &ax, &ay, &bx, &by, &cx, &cy, &dx, &dy);
    double x0 = bx - ax;
    double y0 = by - ay;
    double x1 = dx - cx;
    double y1 = dy - cy;
    double ans = max(sqrt(x0 * x0 + y0 * y0), sqrt(x1 * x1 + y1 * y1)); 
    printf("%.7lf\n", ans); 
    return 0;
}