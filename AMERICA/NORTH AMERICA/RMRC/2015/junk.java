import java.util.*;

public class junk {
  public static void main(String args[]) {
    Scanner stdin = new Scanner(System.in);
    Double xa, ya, za, vxa, vya, vza, ra;
    Double xb, yb, zb, vxb, vyb, vzb, rb;
    int tc = stdin.nextInt();
    for (int iter = 0; iter < tc; iter++) {
      xa = stdin.nextDouble(); ya = stdin.nextDouble(); za = stdin.nextDouble(); ra = stdin.nextDouble();
      vxa = stdin.nextDouble(); vya = stdin.nextDouble(); vza = stdin.nextDouble();
      xb = stdin.nextDouble(); yb = stdin.nextDouble(); zb = stdin.nextDouble(); rb = stdin.nextDouble();
      vxb = stdin.nextDouble(); vyb = stdin.nextDouble(); vzb = stdin.nextDouble();
      Double c = (xa - xb) * (xa - xb) + (ya - yb) * (ya - yb) + (za - zb) * (za - zb) - (ra + rb) * (ra + rb);
      Double b = 2 * (xa - xb) * (vxa - vxb) + 2 * (ya - yb) * (vya - vyb) + 2 * (za - zb) * (vza - vzb);
      Double a = (vxa - vxb) * (vxa - vxb) + (vya - vyb) * (vya - vyb) + (vza - vzb) * (vza - vzb);
      if (Math.abs(a) < 1e-6) {
        System.out.println("No collision");
        continue; 
      }
      if (b * b - 4 * a * c < 0) {
        System.out.println("No collision");
        continue; 
      }
      if (b >= 0 && 4 * a * c > 0) {
        System.out.println("No collision");
        continue;
      }
      Double x1 = (-b -  Math.sqrt(b * b - 4 * a * c)) / (2 * a);
      System.out.printf("%.3f\n", x1); 
    }
    stdin.close(); 
    return; 
  }
}; 