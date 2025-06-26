package PRACTICE.ATCODER;
import java.util.*;

public class Knapsack2 {
    final static int maxf = 100002; 

    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        long W = stdin.nextInt();
        int[] weight = new int[N + 1];
        int[] value = new int[N + 1];
        for (int i = 1; i <= N; i++) {
            weight[i] = stdin.nextInt();
            value[i] = stdin.nextInt();
        }
        long[][] dyn = new long[N + 1][maxf]; 
        for (int i = 0; i < N + 1; i++) {
            for (int j = 0; j < maxf; j++) {
                dyn[i][j] = Integer.MAX_VALUE;
            }
        }
        dyn[0][0] = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < maxf; j++) {
                dyn[i][j] = dyn[i - 1][j];
                if (j >= value[i]) {
                    dyn[i][j] = Math.min(dyn[i][j], dyn[i - 1][j - value[i]] + weight[i]);
                }
            }
        }
        int ret = 0;
        for (int i = 0; i < maxf; i++) {
            if (dyn[N][i] <= W) {
                ret = Math.max(ret, i);
            }
        }
        System.out.println(ret); 
        stdin.close();
        return; 
    }
}