import java.util.*; 

public class Triangle {
    public static void main(String args[]) {
        Scanner stdin = new Scanner(System.in);
        int[] a = new int[3];
        int[] b = new int[3];
        for (int i = 0; i < 3; i++) {
            a[i] = stdin.nextInt();
        }
        for (int i = 0; i < 3; i++) {
            b[i] = stdin.nextInt();
        }
        Arrays.sort(a);
        Arrays.sort(b); 
        if ( a[0] * a[0] + a[1] * a[1] == a[2] * a[2] &&
             a[0] == b[0] && a[1] == b[1] && a[2] == b[2]) {
            System.out.println("YES");
        }
        else {
            System.out.println("NO"); 
        }
        stdin.close(); 
        return; 
    }
}