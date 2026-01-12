#include "bits/stdc++.h"

using namespace std;

inline double deg_to_rad(double deg) {
  return deg / 180.0 * M_PI;
}

inline double rad_to_deg(double rad) {
  return rad * 180.0 / M_PI;
}

pair<double, double> rotate_point(double x, double y, double cos_theta, double sin_theta) {
  return {x * cos_theta - y * sin_theta, x * sin_theta + y * cos_theta};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(10);
  pair<double, double> pa = {2.0, 0.0};
  pair<double, double> pb = {-1.0, 0.0};
  double R, X, Y;
  cin >> R >> X >> Y;

  pair<double, double> ca = {pa.first + X, pa.second + Y};
  pair<double, double> cb = {pb.first + X, pb.second + Y};

  double rad = deg_to_rad(R);
  double cos_theta = cos(rad);
  double sin_theta = sin(rad);

  ca = rotate_point(ca.first, ca.second, cos_theta, sin_theta);
  cb = rotate_point(cb.first, cb.second, cos_theta, sin_theta);

  double a = ca.first - cb.first; 
  double b = ca.second - cb.second; 
  double c = pa.first - pb.first; 
  double d = pa.second - pb.second; 

  double theta_rad = asin((a * d - b * c) / 
                          (b * b + a * a));
  double theta_deg = rad_to_deg(theta_rad);

  theta_rad = deg_to_rad(R);

  double row_a = ca.first - pa.first * cos(theta_rad) + pa.second * sin(theta_rad); 
  double row_b = ca.second - pa.first * sin(theta_rad) - pa.second * cos(theta_rad); 
  double coef_a1 = 1 - cos(theta_rad), coef_a2 = sin(theta_rad); 
  double coef_b1 = -sin(theta_rad), coef_b2 = 1 - cos(theta_rad); 
  double x0 = (row_a * coef_a1 + row_b * coef_b1) / (coef_a1 * coef_a1 + coef_b1 * coef_b1); 
  double y0 = (row_a * coef_a2 + row_b * coef_b2) / (coef_a2 * coef_a2 + coef_b2 * coef_b2); 
  cout << R << " " << x0 << " " << y0 << '\n';   
  return 0;
}