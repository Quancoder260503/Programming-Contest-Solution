package PRACTICE.ATCODER;
import java.util.*;

public class Grid {
   static final int mod = 1000000007;
   public static void main(String args[]) {
      Scanner stdin = new Scanner(System.in);
      int R, C;
      R = stdin.nextInt();
      C = stdin.nextInt();
      char[][] grid = new char[R][C];
      for (int i = 0; i < R; i++) {
         String line = stdin.next();
         for (int j = 0; j < C; j++) {
            grid[i][j] = line.charAt(j);
         }
      }
      long[][] dyn = new long[R][C];
      dyn[0][0] = 1; 
      for (int i = 0; i < R; i++) {
         for (int j = 0; j < C; j++) {
            if (grid[i][j] == '#')
               continue;
            if (i > 0) {
               dyn[i][j] += dyn[i - 1][j];
               dyn[i][j] %= mod;
            }
            if (j > 0) {
               dyn[i][j] += dyn[i][j - 1];
               dyn[i][j] %= mod;
            }
         }
      }
      System.out.printf("%d\n", dyn[R - 1][C - 1]);
      stdin.close(); 
      return; 
   }
}