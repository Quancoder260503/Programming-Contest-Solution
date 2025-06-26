package PRACTICE.ATCODER;
import java.util.*; 

public class vacation {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N = stdin.nextInt();
        int[][] dyn = new int[N + 1][3];
        int a, b, c;
        for (int i = 1; i <= N; i++) {
            a = stdin.nextInt();
            b = stdin.nextInt();
            c = stdin.nextInt();
            dyn[i][0] = Math.max(dyn[i - 1][1], dyn[i - 1][2]) + a;
            dyn[i][1] = Math.max(dyn[i - 1][0], dyn[i - 1][2]) + b;
            dyn[i][2] = Math.max(dyn[i - 1][0], dyn[i - 1][1]) + c;
        }
        int ret = dyn[N][0]; 
        ret = Math.max(ret, dyn[N][1]); 
        ret = Math.max(ret, dyn[N][2]); 
        System.out.println(ret);
        stdin.close(); 
        return; 
    }
}
