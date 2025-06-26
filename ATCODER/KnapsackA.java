package PRACTICE.ATCODER;
import java.util.*;

public class KnapsackA {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        int W = stdin.nextInt();
        long[] dyn = new long[W + 1];
        for (int i = 0; i < N; i++) {
            int cap = stdin.nextInt();
            int val = stdin.nextInt();
            for (int j = W; j >= cap; j--) {
                dyn[j] = Math.max(dyn[j], dyn[j - cap] + val);
            }
        }
        long ret = 0;
        for (int i = 0; i <= W; i++) {
            ret = Math.max(ret, dyn[i]); 
        }
        System.out.println(ret); 
        stdin.close(); 
        return; 
    } 
}
