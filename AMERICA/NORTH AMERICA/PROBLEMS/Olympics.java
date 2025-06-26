import java.util.*;

public class Olympics {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int E = stdin.nextInt();
        int E_succ = stdin.nextInt();
        int E_fail = stdin.nextInt();
        long[] dyn = new long[E + 1];
        long oo = Integer.MAX_VALUE / 2; 
        for (int i = 1; i <= E; i++) {
            dyn[i] = 1;
            if (i > E_succ) {
                dyn[i] += dyn[i - E_succ];
            }
            if (i > E_fail) {
                dyn[i] += dyn[i - E_fail];
            }
            if (dyn[i] > oo) {
                dyn[i] = oo;
            }
        }
        Double ret = Math.min(200.0 / dyn[E], 225.0 / (dyn[E] + 1.0));
        System.out.format("%.6f\n", ret); 
        stdin.close();
        return;
    }
}