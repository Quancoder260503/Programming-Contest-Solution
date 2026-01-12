import java.util.*;
import java.math.*; 

public class CurveSpeed { 
  public static void main(String args[]) { 
    Scanner stdin = new Scanner(System.in); 
    while(stdin.hasNextDouble()) { 
      double R = stdin.nextDouble(); 
      double S = stdin.nextDouble(); 
      double V = Math.sqrt(R * (S + 0.16) / 0.067);
      System.out.printf("%d\n", Math.round(V)); 
    }
    return; 
  }  
}