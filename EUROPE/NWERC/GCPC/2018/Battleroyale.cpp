#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
#define mp make_pair 
double xr,yr,xb,yb,xs,ys,xe,ye,rr,rb; 
signed main(void)
{
    scanf("%lf %lf",&xs,&ys);
    scanf("%lf %lf",&xe,&ye); 
    scanf("%lf %lf %lf",&xr,&yr,&rr);
    scanf("%lf %lf %lf", &xb, &yb, &rb);
    double p = (fabs((ys - ye) * xb + (xe - xs) * yb + xs * ye - ys * xe)) / hypot(xe - xs, ys - ye); 
    double d1 = hypot(xe - xb, ye - yb); 
    double d2 = hypot(xs - xb, ys - yb); 
    double t1 = sqrt(d1 * d1 - rb * rb); 
    double t2 = sqrt(d2 * d2 - rb * rb);
    double angle = acos(p / d1) + acos(p / d2) - acos(rb/ d1) - acos(rb / d2);
    printf("%0.15lf\n", t1 + t2 + angle * rb);     
    return 0;
}