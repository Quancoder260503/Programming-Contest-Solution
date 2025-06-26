import java.util.*;

public class recipes {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int tc = stdin.nextInt();
        int R, P, D;
        for (int iter = 0; iter < tc; iter++) {
            R = stdin.nextInt();
            P = stdin.nextInt();
            D = stdin.nextInt();
            String[] name = new String[R];
            Double[] p = new Double[R];
            Double[] w = new Double[R];
            System.out.printf("Recipe # %d\n", iter + 1);
            double main_w = 0;
            for (int j = 0; j < R; j++) {
                name[j] = stdin.next();
                w[j] = stdin.nextDouble();
                p[j] = stdin.nextDouble() * 0.01;
                if (Math.abs(p[j] - 1) < 1e-6) {
                    main_w = w[j] * D / P;
                }
            }
            for (int j = 0; j < R; j++) {
                System.out.printf("%s %.7f\n", name[j], main_w * p[j]);
            }
            String n_line = "";
            for (int i = 0; i < 40; i++) {
                n_line += '-';
            }
            System.out.println(n_line);
        }
        stdin.close();
        return;
    }
}