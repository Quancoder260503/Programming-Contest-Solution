import java.util.*;

public class everywhere {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int N, tc;
        tc = stdin.nextInt();
        for (int iter = 0; iter < tc; iter++) {
            HashSet<String> cities = new HashSet<String>();
            String S;
            N = stdin.nextInt();
            for (int i = 0; i < N; i++) {
                S = stdin.next();
                cities.add(S);
            }
            System.out.printf("%d\n", cities.size());
        }
        stdin.close();
        return;
    }
}