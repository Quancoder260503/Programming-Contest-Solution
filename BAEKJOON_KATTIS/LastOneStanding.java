package PRACTICE.BAEKJOON_KATTIS;

import java.util.*;

public class LastOneStanding {
    public static void main(String[] args) {
        Scanner stdin = new Scanner(System.in);
        int h1 = stdin.nextInt(), d1 = stdin.nextInt(), t1 = stdin.nextInt();
        int h2 = stdin.nextInt(), d2 = stdin.nextInt(), t2 = stdin.nextInt();
        int a1 = ((h2 + d1 - 1) / d1 - 1) * t1;
        int a2 = ((h1 + d2 - 1) / d2 - 1) * t2;
        if(a1 > a2) {
            System.out.println("player two");
        }
        else if(a1 < a2) {
            System.out.println("player one");
        }
        else {
            System.out.println("draw");
        }
        stdin.close();
        return;
    }
}
