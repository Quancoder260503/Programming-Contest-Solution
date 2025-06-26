import java.util.*;

public class PF {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        int C = stdin.nextInt();
        int[] a = new int[N];
        for (int i = 0; i < N; i++) {
            a[i] = stdin.nextInt();
        }
        long len = 0;
        long best = Integer.MAX_VALUE;
        int pos = N + 1;
        for (int i = 0; i < N; i++) {
            len += a[i];
            len = Math.max(len, (long) i * C);
            long cc = len / C;
            if (cc < N) {
                if (best == cc - i) {
                    pos = Math.min(pos, i);
                } else if (best > cc - i) {
                    best = cc - i;
                    pos = i;
                }
            }
        }
        if (best < N) {
            System.out.printf("%d\n", pos);
        }
        else {
            System.out.println("impossible"); 
        }
        stdin.close(); 
        return; 
    }
}
