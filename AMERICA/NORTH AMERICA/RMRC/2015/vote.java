import java.util.*; 

public class vote {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int tc = stdin.nextInt();
        for (int iter = 0; iter < tc; iter++) {
            int N = stdin.nextInt();
            int sum = 0, winner = 0, max_point = 0, num_win = 0;
            for (int i = 0; i < N; i++) {
                int score = stdin.nextInt();
                sum += score;
                if (score == max_point) {
                    num_win++;
                } else if (score > max_point) {
                    max_point = score;
                    num_win = 1;
                    winner = i + 1;
                }
            }
            if (num_win == 1) {
                if (2 * max_point > sum) {
                    System.out.printf("majority winner %d\n", winner);
                } else {
                    System.out.printf("minority winner %d\n", winner);
                }
            } else {
                System.out.println("no winner");
            }
        }
        stdin.close(); 
        return; 
    }
}
